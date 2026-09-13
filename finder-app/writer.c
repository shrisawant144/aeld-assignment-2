#include<stdio.h>
#include<errno.h>
#include <syslog.h>

int main(int argc,char *argv[])
{
    openlog("writer", LOG_PID, LOG_USER);
    if(argc != 3)
    {
        printf("Usage: %s <file path> <input text>\n", argv[0]);
        syslog(LOG_ERR, "Invalid number of arguments. Usage: %s <file path> <input text>", argv[0]);
        closelog();
        return 1;
    }

    FILE *fp = fopen(argv[1], "w");
    if(fp == NULL)
    {
        printf("Error opening file %s Error Code: %d\n", argv[1], errno); 
        perror("Error");
        syslog(LOG_ERR, "Error opening file %s Error Code: %d", argv[1], errno);
        closelog();
        return 1;
    }
    
    int bytes_written = fprintf(fp, "%s", argv[2]);
    if(bytes_written < 0)
    {
        printf("Error writing to file %s Error Code: %d\n", argv[1], errno);
        perror("Error");
        syslog(LOG_ERR, "Error writing to file %s Error Code: %d", argv[1], errno);
        fclose(fp);
        closelog();
        return 1;
    }
    else
    {
        printf("Successfully written %d bytes to file %s\n", bytes_written, argv[1]);
        syslog(LOG_DEBUG, "Writing %s to %s", argv[2], argv[1]);
    }

    if (fclose(fp) == EOF)
    {
        printf("Error closing file %s Error Code: %d\n", argv[1], errno);
        perror("Error");
        syslog(LOG_ERR, "Error closing file %s Error Code: %d", argv[1], errno);
        closelog();
        return 1;
    }

    closelog();
    return 0;
}