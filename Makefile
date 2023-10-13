CC = gcc
program = main

main: main.c ./lib/stack/stack.c ./lib/stack/stack.h ./lib/queue/queue.c ./lib/queue/queue.h
	$(CC) -o $(program) main.c ./lib/stack/stack.c ./lib/queue/queue.c

clean:
	rm -r lib/*/*.o $(program)

exec:
	$(CC) -o $(program) main.c ./lib/stack/stack.c ./lib/queue/queue.c
	./$(program)