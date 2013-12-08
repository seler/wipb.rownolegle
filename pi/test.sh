#!/bin/bash

for i in $(seq 1 64); do
	t=`{ time -p ./pi $i 100 >/dev/null;} |& grep "real" | sed 's/real //'`
   	echo "$i, $t"
done
