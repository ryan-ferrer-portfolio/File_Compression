/**
 * @file huffman.h
 * @brief Public interface for Huffman coding compression and decompression.
 *
 * This module provides the core functionality for building Huffman trees,
 * generation variable-length codes, and performing losless compression and
 * decompression of files.
 *
 * The implementation operates on raw bytes, allowing it to compress both text
 * and arbitrary binary files.
 *
 * @author Ryan Ferrer
 * @date 2026-05-12
 */

#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdio.h>

/**
 * @brief Compresses data from an input stream using Huffman coding.
 *
 * This function coordinates the complete compression process, including
 * frequency analysis, Huffman tree construction, code generation, header
 * writing, and bitstream encoding.
 *
 * @param in_fp Input stream containing the original uncompressed data.
 * @param out_fp Output stream where the compressed data will be written.
 *
 * @return EXIT_SUCCESS if compression completes successfully, or
 *         EXIT_FAILURE if an error occurs during compression.
 */
int huffman_compress_file(FILE* in_fp, FILE* out_fp);

/**
 * @brief Decompresses a Huffman-encoded input stream.
 *
 * This function coordinates the decompression process by reading the file
 * header, reconstructing the Huffman tree, decoding the compressed bitstream,
 * and writing the restored data to the output stream.
 *
 * @param in_fp Input stream containing Huffman-compressed data.
 * @param out_fp Output stream where the decompressed data will be written.
 *
 * @return EXIT_SUCCESS if decompression completes successfully, or
 *         EXIT_FAILURE if an error occurs during decompression.
 */
int huffman_decompress_file(FILE* in_fp, FILE* out_fp);

#endif // HUFFMAN_H
