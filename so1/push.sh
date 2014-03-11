#!/bin/bash

for dir in `ls | sed -n '/lab/ p'`
do
	if [ -d "$dir" ]; then
		cd "$dir"
		../mmf.rb > makefile
		make remove &> /dev/null
		rm makefile
		cd ..
		rm -f "zips/$dir.zip"
		zip -r9 "$dir.zip" "$dir/" > /dev/null
		mv "$dir.zip" zips/
	fi
done

git add .
git commit -m "Regular update."
git push -u origin

