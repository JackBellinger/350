#!/usr/bin/bash

#read x
x=5
for i in $(seq 1 $x)
do
    for j in $(seq 1 $i)
    do
        printf $i
    done
    printf "\n"
done
