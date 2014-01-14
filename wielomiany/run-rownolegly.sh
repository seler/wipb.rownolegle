#!/bin/bash

echo -e "s\tn\tt\tthreads"
for o in 1 2 3 4 5 6 7 8 9 10
do
    export OMP_NUM_THREADS=$o
    #for s in 4 16 64 256 512 1024
    for s in 256 512 1024
    do
        n=$((((1024*1024)/$s)-$s+10));
        t=`{ time -p ./szeregowy $s $n 500 100;} |& grep "real" | sed 's/real //'`
        echo -e "$s\t$n\t$t\t$o"
    done
done
