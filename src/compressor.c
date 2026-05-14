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
#include <string.h>

#include "../include/huffman.h"

#define HUFF_EXTENSION ".huff" ///< File extension for Huffman compressed files

/**
 * Prints usage instructions to stderr
 *
 * Usage format displayed:
 *   ./prg_name (-c | -d) <input-file> [output-file]
 *
 * @param prg_name Name of the program
 */
static void print_usage(const char* prg_name) {
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
 * @brief Generates the default output filename for compression or decompression.
 *
 * This function constructs an appropriate output filename based on the input file
 * and the current operation mode.
 *
 * Behavior:
 *   - Compression mode:
 *       Appends the Huffman extension (".huff") to the input filename.
 *
 *   - Decompression mode:
 *       If the input filename ends with the Huffman extension, it is removed.
 *       Otherwise, a default ".out" extension is appended.
 *
 * The result is written into a caller-provided buffer. The caller is responsible
 * for allocating the buffer and ensuring it has sufficient size.
 *
 * @param input_file   Path to the input file.
 * @param compress_mode Non-zero for compression, zero for decompression.
 * @param out          Buffer where the generated filename will be written.
 * @param out_size     Size of the output buffer in bytes.
 *
 * @note The output is always null-terminated if out_size > 0.
 */
void get_output_filename(const char *input_file, int compress_mode,
                         char *out, size_t out_size)
{
    size_t len = strlen(input_file);
    size_t ext_len = strlen(HUFF_EXTENSION);

    if (compress_mode) {
        snprintf(out, out_size, "%s%s", input_file, HUFF_EXTENSION);
        return;
    }

    // decompress mode
    if (len >= ext_len &&
        strcmp(input_file + len - ext_len, HUFF_EXTENSION) == 0)
    {
        snprintf(out, out_size, "%.*s",
                 (int)(len - ext_len),
                 input_file);
    }
    else {
        snprintf(out, out_size, "%s.out", input_file);
    }
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
    char* input_file_name = argv[optind++];

    // Set default output file
    size_t output_name_size = strlen(input_file_name) + strlen(HUFF_EXTENSION) + 1;
    char default_output_name[output_name_size];
    char *output_file_name = default_output_name;
    snprintf(default_output_name, output_name_size,
             "%s%s", input_file_name, HUFF_EXTENSION);
    // use specified name if there
    if (optind < argc) {
        output_file_name = argv[optind++];
    }

    // reject extra args
    if(optind < argc) {
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    // Open input file
    FILE* input_fp = fopen(input_file_name, "rb");
    if(input_fp == NULL) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    // Open output file
    FILE* output_fp = fopen(output_file_name, "wb");
    if(output_fp == NULL) {
        fclose(input_fp);
        perror("fopen");
        return EXIT_FAILURE;
    }

    // Compress using huffman module
    int status = EXIT_FAILURE;
    if(compress_mode) {
        status = huffman_compress_file(input_fp, output_fp);
    }
    if(decompress_mode) {
        status = huffman_decompress_file(input_fp, output_fp);
    }

    fclose(input_fp);
    fclose(output_fp);
    return status;
}
