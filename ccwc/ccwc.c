#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct WC {
    char* filename;
    long fileSize;
    long lineCount;
    long wordCount;
    long charCount;
};

struct Options {
    bool c;
};

void printWC(struct WC wc, struct Options op) {
    if (op.c) {
        printf("%ld ", wc.fileSize);
    }
    printf("%s", wc.filename);
}

int getFileSize(FILE *file, struct Options op) {
    if (!op.c) {
        return 0;
    }

    // Move the file pointer to the end of the file
    fseek(file, 0, SEEK_END);

    // Get the current position of the file pointer
    long filesize = ftell(file);

    if (filesize == -1) {
        perror("Error getting file size");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    return filesize;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fputs("Usage: ccwc -c <filename>\n", stdout);
        exit(EXIT_FAILURE);
    }

    struct Options options = { false };
    for (int i=1; i<argc; i++) {
        if (strcmp(argv[i], "-c") == 0) {
            options.c = true;
        }
    }

    struct WC wc;

    // read the filename from the command line
    char* filename = argv[argc-1];
    wc.filename = filename;

    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    long filesize = getFileSize(file, options);
    wc.fileSize = filesize;

    // print the final result
    printWC(wc, options);

    fclose(file);

}
