#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* data;
    int size;
    int cursor;
} Array;

void array_init(Array* array) {
    array->size = 4;
    array->cursor = 0;
    array->data = malloc(array->size * sizeof(int));
}

void array_free(Array* array) {
    array->size = 1;
    array->cursor = 0;
    free(array->data);
}

void array_push(Array* array, int data) {
    if (array->cursor >= array->size) {
        array->size *= 2;
        int* new_data = realloc(array->data, array->size * sizeof(int));
        if (!new_data) {
            perror("realloc failed");
            exit(1);
        }
        array->data = new_data;
    }
    array->data[array->cursor] = data;
    array->cursor++;
}

int array_pop(Array* array) {
    if (array->cursor == 0) {
        fprintf(stderr, "Error: pop from empty array\n");
        exit(1);
    }
    array->cursor--;
    return array->data[array->cursor];
}

int array_get(Array* array, int index) {
    return array->data[index];
}

int array_last(Array* array) {
    if (array->cursor == 0) {
        fprintf(stderr, "Error: empty array\n");
        exit(1);
    }
    return array->data[array->cursor - 1];
}
