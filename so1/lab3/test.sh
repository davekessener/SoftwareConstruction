#!/bin/bash
ruby -e "$1.times{|i|;puts i;}" | ./lab3_2 -d | sed -n '/err/ s/^.*| *//p' | sed 's/[ \t]\+/ /g' | sed -n '/[1-9]/ p'

