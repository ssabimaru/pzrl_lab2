#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operations.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <file> <operation> [options]\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    const char *operation = argv[2];

    if (strcmp(operation, "-r") == 0 && argc == 5) {
        replace_text(filename, argv[3], argv[4]);
    } else if (strcmp(operation, "-d") == 0 && argc == 4) {
        delete_lines(filename, argv[3]);
    } else if (strcmp(operation, "-i") == 0 && argc == 5) {
        if (strcmp(argv[3], "-f") == 0) {
            insert_text(filename, argv[4], 1);
        } else if (strcmp(argv[3], "-b") == 0) {
            insert_text(filename, argv[4], 0);
        } else {
            fprintf(stderr, "Invalid insert flag. Use -f for front or -b for back.\n");
            return 1;
        }
    } else {
        fprintf(stderr, "Invalid arguments.\n");
        return 1;
    }

    return 0;
}