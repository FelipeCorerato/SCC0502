#include "byte.h"

void getByteFrequency(FILE* stream, unsigned int* bytesList) {
    byte c;

    while (fread(&c, 1, 1, stream) >= 1) {
        bytesList[(byte)c]++;
    }

    rewind(stream);
}

int generateBit(FILE* stream, int position, byte* aux) {
    if (position % 8 == 0) {
        fread(aux, 1, 1, stream);
    }

    return !!(*aux & 1 << position % 8);
}
