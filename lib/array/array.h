#ifndef ARRAY_H
#define ARRAY_H

typedef struct {
    int* data;
    int size;
    int cursor;
} Array;

void array_init(Array* array);
void array_free(Array* array);
void array_push(Array* array, int data);
int array_pop(Array* array);
int array_get(Array* array, int index);
int array_lasted(Array* array);

#endif
