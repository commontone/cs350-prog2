all: prog2tree simple

prog2tree: prog2tree.o
	gcc prog2tree.o -o prog2tree -g
	
prog2tree.o: prog2tree.c
	gcc -c prog2tree.c -o prog2tree.o -g

simple: simple.c
	gcc simple.c -o simple -g
	
checkmem: prog2tree
	valgrind --track-origins=yes ./prog2tree $(ARGS)

run: prog2tree simple
	./prog2tree $(ARGS)

clean:
	rm *.o prog2tree simple vgcore.*