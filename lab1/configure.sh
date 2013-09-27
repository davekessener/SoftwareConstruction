#!/bin/bash
FILES=`ls *.c | sed -e 's/[ \t]\+/\n/' -e 's/\.c.*$//'`
printf "CC=cc\nCFLAGS=-Wall -g -O0\nLIB=-lm\n\n"

FLS=""
for f in $FILES
do
	FLS="$FLS $f"
done

printf "all: $FLS\n\n"

for f in $FILES
do
	TMP=`cat $f.c | sed -n '/#include/ s/#include[ \t]\+//p' | sed -e 's/[\"<>]//g' -e 's/\.h.*$//'`
	INC=""
	OBJ=""
	for i in $TMP
	do
		INC="$INC `ls $i.h 2>/dev/null`"
		OBJ="$OBJ `ls $i.c 2>/dev/null | sed 's/\.c/.o/'`"
	done
	OCMD="$f.o: `printf "$f.c $INC\n\t"'$(CC) $(CFLAGS)'" -c $f.c -o $f.o" | sed 's/ \+/ /g'`"
	CMD="$f: `printf "$f.o $OBJ $INC\n\t"'$(CC) $(CFLAGS)'" $f.o $OBJ -o $f -lm" | sed 's/ \+/ /g'`"
	echo "$OCMD"
	echo "$CMD"
done

