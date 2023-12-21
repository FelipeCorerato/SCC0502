CC = gcc
compactor-program = compactador
decompressor-program = descompactador

tests-directory = ./src/__test__

clean:
	rm -r src/lib/*/*.o $(program)

compile-compactor: ./src/compactor.c ./src/lib/byte/byte.c ./src/lib/byte/byte.h ./src/lib/huffman/huffman.c ./src/lib/huffman/huffman.h ./src/lib/list/list.c ./src/lib/list/list.h ./src/lib/tree/tree.c ./src/lib/tree/tree.h
	$(CC) -o $(compactor-program) ./src/compactador.c ./src/lib/byte/byte.c ./src/lib/huffman/huffman.c ./src/lib/list/list.c ./src/lib/tree/tree.c

compile-decompressor: ./src/decompressor.c ./src/lib/byte/byte.c ./src/lib/byte/byte.h ./src/lib/huffman/huffman.c ./src/lib/huffman/huffman.h ./src/lib/list/list.c ./src/lib/list/list.h ./src/lib/tree/tree.c ./src/lib/tree/tree.h
	$(CC) -o $(decompressor-program) ./src/descompactador.c ./src/lib/byte/byte.c ./src/lib/huffman/huffman.c ./src/lib/list/list.c ./src/lib/tree/tree.c

compile-all: ./src/compactor.c ./src/decompressor.c ./src/lib/byte/byte.c ./src/lib/byte/byte.h ./src/lib/huffman/huffman.c ./src/lib/huffman/huffman.h ./src/lib/list/list.c ./src/lib/list/list.h ./src/lib/tree/tree.c ./src/lib/tree/tree.h
	$(CC) -o $(compactor-program) ./src/compactor.c ./src/lib/byte/byte.c ./src/lib/huffman/huffman.c ./src/lib/list/list.c ./src/lib/tree/tree.c
	$(CC) -o $(decompressor-program) ./src/decompressor.c ./src/lib/byte/byte.c ./src/lib/huffman/huffman.c ./src/lib/list/list.c ./src/lib/tree/tree.c

exec-compactor:
	$(CC) -o $(compactor-program) ./src/compactor.c ./src/lib/byte/byte.c ./src/lib/huffman/huffman.c ./src/lib/list/list.c ./src/lib/tree/tree.c
	./$(compactor-program) $(tests-directory)/rick.txt

exec-decompressor:
	$(CC) -o $(decompressor-program) ./src/decompressor.c ./src/lib/byte/byte.c ./src/lib/huffman/huffman.c ./src/lib/list/list.c ./src/lib/tree/tree.c
	./$(decompressor-program)  ./rick.comp
