#!/bin/bash

cores=`grep -c ^processor /proc/cpuinfo`
./run-rownolegly.sh > rownolegly-$cores-cores.txt
./run-szeregowy.sh > szeregowy-$cores-cores.txt
