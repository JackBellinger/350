#!/usr/bin/bash

x=5
x2=$(($x*2))

j=0

for i in $(seq 1 $x2);
do
    if [ $i -gt $x ]; then
        for n in $(seq 0 $j); do
            echo *
        done
        j=$j-1
    else
        for j in $(seq $i 0); do
            echo *
        done
        j=$j+1
    fi
done
