/**
 * @file huffman_compress.c
 * @brief High-level compression and decompression entry points for Huffman coding.
 *
 * This module implements the top-level Huffman compression and decompression
 * pipelines. Each public function coordinates the major stages of the algorithm
 * while delegating detailed work to helper modules.
 *
 * @author Ryan Ferrer
 * @date 2026-05-12
 */

#include "../include/huffman.h"
#include "../include/huffman_compress.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


int huffman_compress_file(FILE* in_fp, FILE* out_fp) {
    uint64_t freq[256] = {0};
    HuffmanCode codes[256];
    HuffmanNode* root;

    build_frequency_table(in_fp, freq); // updates freq, used in building tree
    root = build_huffman_tree(freq);
    generate_codes(root, codes);

    rewind(in_fp);

    if (write_header(out_fp, freq) != EXIT_SUCCESS)
        return EXIT_FAILURE;

    if (encode_stream(in_fp, out_fp, codes) != EXIT_SUCCESS)
        return EXIT_FAILURE;

    free_huffman_tree(root);
    return EXIT_SUCCESS;
}

int huffman_decompress_file(FILE* in_fp, FILE* out_fp) {

}