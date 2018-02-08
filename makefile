all: prog2 simple

prog2: prog2.o
	gcc prog2.o -o prog2 -g
	
prog2.o: prog2.c
	gcc -c prog2.c -o prog2.o -g

simple: simple.c
	gcc simple.c -o simple -g
checkmem: prog2
	valgrind --track-origins=yes ./prog2 $(ARGS)

run: prog2 simple
	./prog2 $(ARGS)

clean:
	rm *.o prog2 simple vgcore.*