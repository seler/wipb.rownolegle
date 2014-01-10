#!/bin/bash

echo -e "s \tn \tt"
for s in 4 16 64 256 512 1024
do
    n=$((((1024*1024)/$s)-$s+10));
    t=`{ time -p ./build/szeregowy $s $n 2 10;} |& grep "real" | sed 's/real //'`
    echo -e "$s \t$n \t$t"
done


