#!/bin/bash

echo -e "s,n,t,threads"
for o in 1 2 3 4 5 6 7 8 9 10
do
    for s in 4 16 64 256 512 1024
    do
        n=$((((1024*1024)/$s)-$s+10));
        t=`{ time -p ./rownolegly $s $n 500 10 $o;} |& grep "real" | sed 's/real //'`
        echo -e "$s,$n,$t,$o"
    done
done
