#!/bin/bash

echo -e "s,n,t"
for s in 4 16 64 256 512 1024
do
    n=$((((1024*1024)/$s)-$s+10));
    t=`{ time -p ./szeregowy $s $n 500 10;} |& grep "real" | sed 's/real //'`
    echo -e "$s,$n,$t"
done


