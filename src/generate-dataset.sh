#! /bin/bash

# Usage Function
usage()
{
    echo "Usage: $0 <filename> <num_records>"
}

# Generate a Number between 0 and 2^32-1 (RANDOM gives between 0 and 2^16-1)
generate()
{
    echo "$(od -N 4  -t uL -An /dev/random | tr -d " ") $1" 
}

# Verify the number of arguments given
if [ $# -ne 2 ]
then
    usage
    exit 0
fi

# Init Params
filename=$1
batch_size=1000
num_records=$(($2 / $batch_size))

# Delete the file if exists
if [ -f $filename ]
then
    rm $filename
fi

# Create the file
touch $filename

string=$(pwgen 95 1)

# Generate data
for i in $(eval echo {1..$num_records})
do
    batch=
    for i in $(eval echo {2..$batch_size})
    do
        batch+="$(generate $string)\n"
    done
    batch+="$(generate $string)"
    echo -e $batch >> $filename
done