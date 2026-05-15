cmake_minimum_required(VERSION 4.0)
project(File_Compression C)

set(CMAKE_C_STANDARD 99)

add_executable(File_Compression
        src/compressor.c
        src/huffman.c
        include/huffman.h
        src/huffman_compress.c
        include/huffman_compress.h)
