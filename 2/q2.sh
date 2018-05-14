#!/bin/sh
for((i=0;i<26;i++))
do
	echo "$i"
	./caesar.py $i
done
