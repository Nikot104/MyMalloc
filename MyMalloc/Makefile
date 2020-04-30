all: memgrind.c mymalloc.o mymalloc.h
	gcc -g -O -o memgrind memgrind.c 
mymalloc.o: mymalloc.c
	gcc -c mymalloc.c
clean:
	rm memgrind; rm mymalloc.o
