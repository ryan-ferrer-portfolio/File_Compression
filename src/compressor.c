/**
 * @file compressor.c
 * @brief Program to compress files
 *
 * This program compresses files using different compression algorithms
 *
 * @author Ryan Ferrer
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_usage(const char* prg_name) {
    fprintf(stderr,
            "Usage:\n"
            "  %s (-c | -d) <input-file> [output-file]\n\n"
            "Options:\n"
            "  -c    Compress input file\n"
            "  -d    Decompress input file\n",
            prg_name
        );}

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
    char* input_file = argv[optind++];

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



    return EXIT_SUCCESS;
}
