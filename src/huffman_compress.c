//
// Created by ryanf on 5/12/2026.
//

#include "../include/huffman_compress.h"

void build_frequency_table(FILE* in_fp, uint64_t freq[NUM_BYTE_VALUES]) {
    int byte;

    while((byte = fgetc(in_fp)) != EOF) {
        freq[(unsigned char) byte]++;
    }
}