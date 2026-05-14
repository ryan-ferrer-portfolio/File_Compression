/**
 * @file huffman_compress.h
 * @brief Huffman compression module interface.
 *
 * This header defines the data structures and function prototypes required
 * to build a Huffman compression system. It includes functionality for:
 *
 * - Building frequency tables from byte streams
 * - Constructing Huffman trees
 * - Generating variable-length prefix codes
 * - Writing compressed output headers
 * - Encoding input streams into compressed bitstreams
 * - Cleaning up allocated memory
 *
 * The implementation operates on raw binary data and supports full-file
 * compression of arbitrary input streams.
 *
 * @author Ryan Ferrer
 * @date 2026-5-14
 */

#ifndef HUFFMAN_COMPRESS_H
#define HUFFMAN_COMPRESS_H

#include <stdint.h>
#include <stdio.h>

#define NUM_BYTE_VALUES 256  ///< Number of possible byte values (0–255)

/**
 * @brief Node in the Huffman tree.
 *
 * Internal nodes store only frequency and child pointers.
 * Leaf nodes additionally store the byte value they represent.
 */
typedef struct HuffmanNode {
    unsigned char byte;          ///< Byte value (valid only for leaf nodes)
    uint64_t freq;               ///< Frequency of this node or subtree

    struct HuffmanNode *left;    ///< Pointer to left child
    struct HuffmanNode *right;   ///< Pointer to right child
} HuffmanNode;

/**
 * @brief Represents a Huffman code for a single byte.
 *
 * A Huffman code is a variable-length bit sequence. It is stored here as:
 * - A 64-bit integer containing the bit pattern
 * - A length field indicating how many bits are valid
 */
typedef struct {
    uint64_t bits;       ///< Bit pattern representing the code
    unsigned int length;  ///< Number of valid bits in `bits
} HuffmanCode;

/**
 * @brief Builds a frequency table from an input file stream.
 *
 * Reads the entire input stream byte-by-byte and counts occurrences of
 * each possible byte value (0–255).
 *
 * @param in_fp Input file stream opened for reading
 * @param freq Output frequency table of size NUM_BYTE_VALUES
 */
void build_frequency_table(FILE *in_fp,
                           uint64_t freq[NUM_BYTE_VALUES]);

/**
 * @brief Builds a Huffman tree from a frequency table.
 *
 * Uses a priority queue (min-heap) to iteratively combine the lowest
 * frequency nodes into a single optimal Huffman tree.
 *
 * @param freq Frequency table of size NUM_BYTE_VALUES
 * @return Pointer to the root of the constructed Huffman tree,
 *         or NULL on failure
 */
HuffmanNode *build_huffman_tree(const uint64_t freq[NUM_BYTE_VALUES]);

/**
 * @brief Generates Huffman codes from a Huffman tree.
 *
 * Traverses the tree and assigns a unique prefix-free bit code to each
 * byte value. Left edges typically represent 0 and right edges represent 1.
 *
 * @param root Root of the Huffman tree
 * @param codes Output array of HuffmanCode entries indexed by byte value
 */
void generate_codes(const HuffmanNode *root,
                    HuffmanCode codes[NUM_BYTE_VALUES]);

/**
 * @brief Writes Huffman compression metadata header to output file.
 *
 * The header typically contains enough information to reconstruct the
 * Huffman tree during decompression (commonly the frequency table).
 *
 * @param out_fp Output file stream
 * @param freq Frequency table used for encoding
 *
 * @return 0 on success, non-zero on failure
 */
int write_header(FILE *out_fp,
                 const uint64_t freq[NUM_BYTE_VALUES]);

/**
 * @brief Encodes an input file stream into a Huffman-compressed bitstream.
 *
 * Reads the input file again and writes compressed data using the generated
 * Huffman codes.
 *
 * @param in_fp Input file stream (reset to beginning before calling)
 * @param out_fp Output compressed file stream
 * @param codes Huffman codes indexed by byte value
 *
 * @return 0 on success, non-zero on failure
 */
int encode_stream(FILE *in_fp,
                  FILE *out_fp,
                  const HuffmanCode codes[NUM_BYTE_VALUES]);

/**
 * @brief Frees all memory associated with a Huffman tree.
 *
 * Recursively deallocates all nodes in the tree.
 *
 * @param root Root node of the Huffman tree
 */
void free_huffman_tree(HuffmanNode *root);

#endif // HUFFMAN_COMPRESS_H