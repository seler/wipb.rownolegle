#!/bin/bash

for i in 1 2 4 8 16 32 64 128 256 512 1024; do
    ping -s $i 192.168.0.114 -c 1 >> wynik_ping.txt
done;
