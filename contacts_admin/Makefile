CC = gcc
program = main
src-folder = ./src/
lib-folder = ./lib/

all: ./src/main.c ./src/lib/skip_list/skip_list.c ./src/lib/skip_list/skip_list.h
	$(CC) -o $(program) ./src/main.c ./src/lib/skip_list/skip_list.c

clean:
	rm -r src/lib/*/*.o $(program)

run:
	$(CC) -o $(program) ./src/main.c ./src/lib/skip_list/skip_list.c
	./$(program)