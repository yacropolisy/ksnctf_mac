#!/bin/sh
for((i=0;i<17;i++))
do
	echo "$i"
	./b64.py $i
done
