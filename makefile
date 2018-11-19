all: shell.o read_line.o
	gcc -o shell shell.o read_line.o

shell.o: shell.c shell.h
	gcc -c shell.c

read_line.o: read_line.c shell.h
	gcc -c read_line.c

clean:
	rm shell shell.o read_line.o

run:
	./shell
