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
filename=$1
output_filename=sorted_$filename

# Sort data
sort -n -k1 $filename > $output_filename