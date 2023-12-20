#ifndef SCC0502_BYTE_H
#define SCC0502_BYTE_H

#include <stdio.h>

typedef unsigned char byte;

void getByteFrequency(FILE* stream, unsigned int* bytesList);
int generateBit(FILE* stream, int position, byte* aux);

#endif //SCC0502_BYTE_H
