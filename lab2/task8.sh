#!/usr/bin/bash

if [ $# -ne 1 ]; then
    echo "You must only have one integer argument"
    exit 1
fi
x=$1
sum=0
while [ $x -ge 1 ];
do
    let ones=$x%10
    let x=$x/10
    let sum=sum+ones
done

printf "sum = %d\n" $sum

exit 0
