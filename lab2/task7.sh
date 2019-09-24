#!/usr/bin/bash

read x
prod=1
while [ $x -ge 1 ];
do
    let prod=x*prod
    x=$((x-1))
done

echo $prod

exit 0
