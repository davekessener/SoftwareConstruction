#!/bin/bash
cd lab1
./makemake.rb > makefile
make remove
rm makefile
cd ..
git add .
git commit -m "Regular update."
git push -u origin

