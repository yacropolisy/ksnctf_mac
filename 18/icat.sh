#!/bin/sh
for((i = 0; i<6; i++))
do
	icat drive.img 36-128-$((i+4)) > "$i"
done
