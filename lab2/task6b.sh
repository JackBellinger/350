#!/usr/bin/bash

x=5
let x2=($x*2)
j=0

for i in $(seq 1 $x2);
do
    if [ $i -ge $x ]; then
        for n in $(seq 0 $j); do
            printf '*'
		done
        let j=$j-1
    else
        for m in $(seq 0 $j); do
            printf '*'
        done
        let j=$j+1
    fi
	printf '\n'
done
