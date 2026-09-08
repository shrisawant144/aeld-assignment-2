#!/bin/bash
set -euo pipefail

if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <filesdir> <searchstr>" >&2
    exit 1
fi

filesdir=$1
searchstr=$2

if [ ! -d "$filesdir" ]; then
    printf 'Error: %s is not a directory\n' "$filesdir" >&2
    exit 1
fi

cd -- "$filesdir" || exit 1

# Emit one character per regular file, even for filenames containing newlines.
file_count=$(find . -type f -printf '.' | wc -c)

# Count matching lines per file; grep returns 1 when no lines match.
grep_status=0
line_counts=$(grep -rFhc -- "$searchstr" .) || grep_status=$?
if [ "$grep_status" -gt 1 ]; then
    exit 1
fi

matching_lines=$(printf '%s\n' "$line_counts" | awk '{ total += $1 } END { print total + 0 }')

printf 'The number of files are %s and the number of matching lines are %s\n' \
    "$file_count" "$matching_lines"
