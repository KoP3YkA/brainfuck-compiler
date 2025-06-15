#include <malloc.h>
#include "stdio.h"

typedef struct {
    char* path;
} CompilerFile;

char *file_read(CompilerFile* file) {
    FILE *readFile = fopen(file->path, "r");
    if (readFile == NULL) {
        return NULL;
    }

    fseek(readFile, 0, SEEK_END);
    long filesize = ftell(readFile);
    rewind(readFile);

    char *buffer = malloc(filesize + 1);
    if (!buffer) {
        fclose(readFile);
        return NULL;
    }

    size_t read_size = fread(buffer, 1, filesize, readFile);
    buffer[read_size] = '\0';

    fclose(readFile);
    return buffer;
}

int create_file_if_not_exists(CompilerFile* file) {
    FILE *newFile = fopen(file->path, "w");
    fclose(newFile);
    if (!newFile) return 1;
    return 0;
}

int overwrite_file(CompilerFile* file, char* text) {
    FILE *newFile = fopen(file->path, "w");
    if (!newFile) return 1;
    fprintf(newFile, "%s", text);
    fclose(newFile);
    return 0;
}

int add_text_to_file(CompilerFile* file, char* text) {
    FILE *newFile = fopen(file->path, "a");
    if (!newFile) return 1;
    fprintf(newFile, "%s", text);
    fclose(newFile);
    return 0;
}
