#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

typedef struct {
    char* path;
} CompilerFile;

char *file_read(CompilerFile* file);
int create_file_if_not_exists(CompilerFile* file);
int overwrite_file(CompilerFile* file, char* text);
int add_text_to_file(CompilerFile* file, char* text);

#endif
