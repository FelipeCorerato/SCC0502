CC = gcc
compactor-program = compactador
decompressor-program = descompactador

clean:
	rm -r src/lib/*/*.o $(program)

compile-compactor: ./src/compactador.c ./src/lib/byte/byte.c ./src/lib/byte/byte.h ./src/lib/huffman/huffman.c ./src/lib/huffman/huffman.h ./src/lib/list/list.c ./src/lib/list/list.h ./src/lib/tree/tree.c ./src/lib/tree/tree.h
	$(CC) -o $(compactor-program) ./src/compactador.c ./src/lib/byte/byte.c ./src/lib/huffman/huffman.c ./src/lib/list/list.c ./src/lib/tree/tree.c

compile-decompressor: ./src/descompactador.c ./src/lib/byte/byte.c ./src/lib/byte/byte.h ./src/lib/huffman/huffman.c ./src/lib/huffman/huffman.h ./src/lib/list/list.c ./src/lib/list/list.h ./src/lib/tree/tree.c ./src/lib/tree/tree.h
	$(CC) -o $(decompressor-program) ./src/descompactador.c ./src/lib/byte/byte.c ./src/lib/huffman/huffman.c ./src/lib/list/list.c ./src/lib/tree/tree.c

compile-all: ./src/compactador.c ./src/descompactador.c ./src/lib/byte/byte.c ./src/lib/byte/byte.h ./src/lib/huffman/huffman.c ./src/lib/huffman/huffman.h ./src/lib/list/list.c ./src/lib/list/list.h ./src/lib/tree/tree.c ./src/lib/tree/tree.h
	$(CC) -o $(compactor-program) ./src/compactador.c ./src/lib/byte/byte.c ./src/lib/huffman/huffman.c ./src/lib/list/list.c ./src/lib/tree/tree.c
	$(CC) -o $(decompressor-program) ./src/descompactador.c ./src/lib/byte/byte.c ./src/lib/huffman/huffman.c ./src/lib/list/list.c ./src/lib/tree/tree.c

exec-compactor:
	$(CC) -o $(compactor-program) ./src/compactador.c ./src/lib/byte/byte.c ./src/lib/huffman/huffman.c ./src/lib/list/list.c ./src/lib/tree/tree.c
	./$(compactor-program) ./src/main.c

exec-decompressor:
	$(CC) -o $(decompressor-program) ./src/descompactador.c ./src/lib/byte/byte.c ./src/lib/huffman/huffman.c ./src/lib/list/list.c ./src/lib/tree/tree.c
	./$(decompressor-program)  ./main.comp
