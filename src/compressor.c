/**
 * @file compressor.c
 * @brief Command-line interface for Huffman compression and decompression.
 *
 * This file implements the main entry point of the compressor program.
 * It is responsible for parsing command-line arguments, validating user input,
 * and invoking the appropriate compression or decompression routines.
 *
 * Supported operations:
 *   - Compression of input files using Huffman coding (-c)
 *   - Decompression of previously compressed files (-d)
 *
 * Usage:
 *   ./compressor (-c | -d) <input-file> [output-file]
 *
 * @author Ryan Ferrer
 * @date 2026-05-12
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/huffman.h"

/**
 * Prints usage instructions to stderr
 *
 * Usage format displayed:
 *   ./prg_name (-c | -d) <input-file> [output-file]
 *
 * @param prg_name Name of the program
 */
void print_usage(const char* prg_name) {
    fprintf(stderr,
            "Usage:\n"
            "  %s (-c | -d) <input-file> [output-file]\n\n"
            "Options:\n"
            "  -c    Compress input file\n"
            "  -d    Decompress input file\n",
            prg_name
        );
}

/**
 * @brief Entry point for the compressor program.
 *
 * This function is responsible for parsing command-line arguments, validating
 * user input, and dispatching execution to either the compression or
 * decompression pipeline.
 *
 * Supported modes:
 *   - Compression (-c): Compresses the input file using Huffman coding
 *   - Decompression (-d): Restores a previously compressed file
 *
 * Note:
 *   This function does not implement compression logic directly.
 *   It delegates core functionality to the Huffman module.
 *
 * @param argc Argument count
 * @param argv Argument vector
 *
 * @return EXIT_SUCCESS on successful execution,
 *         EXIT_FAILURE on invalid input or error conditions
 */
int main(int argc, char* argv[]) {

    int compress_mode = 0;
    int decompress_mode = 0;

    // Parse command line args
    int opt;
    while ((opt = getopt(argc, argv, "cd")) != -1) {
        switch(opt) {
            case 'c':
                compress_mode = 1;
                break;
            case 'd':
                decompress_mode = 1;
                break;
            default:
                print_usage(argv[0]);
                return EXIT_FAILURE;
        }
    }

    // ensure exactly one flag
    if(compress_mode == decompress_mode) {
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    // ensure input file is there
    if(optind >= argc) {
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }
    const char* input_file = argv[optind++];

    // check for output file
    char* output_file = NULL;
    if(optind < argc) {
        output_file = argv[optind++];
    }

    // reject extra args
    if(optind < argc) {
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    // Open input file
    FILE* input_fp = fopen(input_file, "rb");
    if(input_fp == NULL) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    // FILE* output_fp;
    // if(output_file) {
    //     output_fp = fopen(output_file, "wb");
    //     if(output_fp == NULL) {
    //         perror("fopen");
    //         fclose(input_fp);
    //         return EXIT_FAILURE;
    //     }
    // }





    return EXIT_SUCCESS;
}
