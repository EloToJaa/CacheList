#!/bin/bash

make main
for i in {11..14}
do
    ./main < ./Tests/$i.in > out.out
    if diff -b out.out ./Tests/$i.out > /dev/null
	then
		echo "$i"
	else
		echo "$i BLAD"
	fi
done