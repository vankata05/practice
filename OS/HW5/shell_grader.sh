#!/bin/bash

for arg in "$1" "$2"; do 
    if [ ! -r "$arg" ]; then
        echo "Can't read $arg"
        exit 1
    fi
done

if [ ! -w "$3" ]; then
    echo "Can't write to $3"
    exit 1
fi

if [ "$(find "$3" -maxdepth 0 -empty)" != "$3" ]; then
    echo "$3 is not empty"
    exit 1
fi

if [ "$(find "$1" -maxdepth 1 -type f | wc -l)" != 25 ]; then
    echo "$1 doesn't contain 25 files"
    exit 1
fi

student_files=( "$1"/* )

for student_file in "${student_files[@]}"; do
    if [ "$(wc -l < "$student_file")" != 25 ]; then
        echo "$student_file doesn't contain 25 lines"
        exit 1
    fi

    correct_count=$(paste "$student_file" "$2" | awk '$1==$2' | wc -l)

    grade=$(awk 'BEGIN {if ('$correct_count' <= 13) print 2; else if ('$correct_count' <= 16) print 3; else if ('$correct_count' <= 19) print 4; else if ('$correct_count' <= 22) print 5; else print 6}')

    echo "$grade" > "${3}/${student_file##*/}"
done

echo "Grades computed successfully."
exit 0

#Example call:
#./shell_grader.sh ./'answers location' ./'answers sheet' ./'results dir'

