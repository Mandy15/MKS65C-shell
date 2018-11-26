all: shell.o read_line.o parse_args.o exec_args.o
	gcc -o shell shell.o read_line.o parse_args.o exec_args.o

shell.o: shell.c shell.h
	gcc -c shell.c

read_line.o: read_line.c shell.h
	gcc -c read_line.c

parse_args.o: parse_args.c shell.h
	gcc -c parse_args.c

exec_args.o: exec_args.c shell.h
	gcc -c exec_args.c

clean:
	rm shell shell.o read_line.o parse_args.o exec_args.o

run:
	./shell
