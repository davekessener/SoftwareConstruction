CC=cc
CFLAGS=-Wall -g -O0 -Wno-psabi

all: lab1_1a lab1_1c test lab1_3 lab1_1b

lab1_1a.o: lab1_1a.c include.h 
	$(CC) $(CFLAGS) -c lab1_1a.c -o lab1_1a.o

lab1_1a: lab1_1a.o
	$(CC) $(CFLAGS) lab1_1a.o -o lab1_1a 

lab1_1c.o: lab1_1c.c include.h 
	$(CC) $(CFLAGS) -c lab1_1c.c -o lab1_1c.o

lab1_1c: lab1_1c.o
	$(CC) $(CFLAGS) lab1_1c.o -o lab1_1c 

logger.o: logger.c include.h 
	$(CC) $(CFLAGS) -c logger.c -o logger.o

dstack.o: dstack.c 
	$(CC) $(CFLAGS) -c dstack.c -o dstack.o

test.o: test.c 
	$(CC) $(CFLAGS) -c test.c -o test.o

test: test.o logger.o
	$(CC) $(CFLAGS) test.o logger.o -o test 

tokenizer.o: tokenizer.c 
	$(CC) $(CFLAGS) -c tokenizer.c -o tokenizer.o

evaluate.o: evaluate.c include.h 
	$(CC) $(CFLAGS) -c evaluate.c -o evaluate.o

lab1_3.o: lab1_3.c include.h 
	$(CC) $(CFLAGS) -c lab1_3.c -o lab1_3.o

lab1_3: lab1_3.o evaluate.o tokenizer.o dstack.o logger.o
	$(CC) $(CFLAGS) lab1_3.o evaluate.o tokenizer.o dstack.o logger.o -o lab1_3 -lm

lab1_1b.o: lab1_1b.c include.h 
	$(CC) $(CFLAGS) -c lab1_1b.c -o lab1_1b.o

lab1_1b: lab1_1b.o
	$(CC) $(CFLAGS) lab1_1b.o -o lab1_1b 


clean:
	rm *.o
