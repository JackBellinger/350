#!/usr//bin/bash

echo "Enter a directory to search: "

read dir
let len_dir=${#dir}

if [  ${dir:0:1} = '~' ]; then
    dir="$HOME/${dir:2:$len_dir-2}"
elif [  ${dir:0:1} = '.' ]; then
    dir="$PWD/${dir:2:$len_dir-2}"
fi
let len_dir=${#dir}
last_char="${dir:$len_dir-1:$len_dir}"
if [ $last_char = '/' ]; then
    dir="${dir:0:$len_dir-1}"
fi

if [ -d "$dir" ]; then
    list=$(ls $dir)
    echo $list
    echo "Enter a file in the directory"

    filename="none"
    notfound=true
    i=0
    while [[ $i -lt 3 ]] && [[ "$notfound" = true ]];
    do
        read filename
        if [ -f "$dir/$filename" ]; then
            notfound=false
        else
            echo "$dir/$filename is Invalid. Enter a valid file name: "
        fi
    done

    if [ "$notfound" = true ]; then
        echo "File not found"
        exit 2
    else
        if [ ! -r "$dir/$filename" ]; then
            echo "File is not readable\n"
            exit 3
        fi

        echo "Enter a word to search for: "
        read search

        results=$(grep $search "$dir/$filename")
        if [ -z "$results" ]; then
            echo "$search Not found."
            exit 4
        else
            printf "$search Found in lines:\n"
            printf "$results\n"
            #printf "%d Found! \nLines:\n \"%d\"" $search $results #this line has weird output
            exit 0
        fi
    fi
else
    echo "Not a valid directory"
    exit 1
fi
exit 0
