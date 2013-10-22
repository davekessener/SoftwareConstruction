#!/bin/bash

for dir in `ls | sed -n '/lab/ p'`
do
	if [ -d "$dir" ]; then
		echo "$dir"
	fi
done

