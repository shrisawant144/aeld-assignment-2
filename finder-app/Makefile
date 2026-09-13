TARGET = writer
SOURCE = writer.c
OBJECT = writer.o

CC = $(CROSS_COMPILE)gcc
CFLAGS = -Wall -Wextra -Werror

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECT)
	$(CC) -o $@ $^

$(OBJECT): $(SOURCE)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECT)