#!/bin/bash
set -eu

if [ $# -ne 2 ]; then
    echo "Usage: $0 <file_path> <text_to_write>"
    exit 1
fi


path=$1
writestr=$2


directory=$(dirname "$path")
writefile=$(basename "$path")

if [ ! -d "$directory" ]; then
    echo "Directory $directory does not exist. Creating it."
    mkdir -p "$directory"
fi

if [ -f "$path" ]; then
    echo "File $path already exists. Overwriting $writefile ."
fi

cat > "$path" <<EOF
$writestr
EOF
