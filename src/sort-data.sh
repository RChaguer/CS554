#! /bin/bash

# Usage Function
usage()
{
    echo "Usage: $0 <filename>"
}

# Verify the number of arguments given
if [ $# -ne 1 ]
then
    usage
    exit 0
fi

# Init Params
TIMEFORMAT=%Rs
filename=$1
output_filename=Bash_sorted_$filename

# Sort data
echo Execution Time is : $((time sort -n -k1 $filename > $output_filename) 2>&1)