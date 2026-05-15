# Huffman Compressor

A C implementation of Huffman coding for lossless file compression and decompression using byte-level frequency analysis.

This project supports arbitrary binary files and demonstrates core data structures such as binary trees, priority queues (min-heaps), and bit-level file I/O.

---

## Features

- Lossless compression using Huffman coding
- Supports all file types (text and binary)
- Command-line interface
- Generates `.huff` compressed files
- Decompression restores original data
- Efficient byte-frequency based encoding

---

## Build Instructions

This project uses CMake.

```bash
mkdir build
cd build
cmake ..
make