#include <stdio.h>
#include "../array/array.h"
#include "../files/file_manager.h"
#include "../global.h"

void move_right() {
    add_text_to_file(&output, "\ninc rsi");
}

void move_left() {
    add_text_to_file(&output, "\ndec rsi");
}

void plus(int count) {
    if (count == 1) add_text_to_file(&output, "\ninc byte [rsi]");
    else {
        char text[255];
        sprintf(text, "\nadd byte [rsi], %d", count);
        add_text_to_file(&output, text);
    }
}

void minus(int count) {
    if (count == 1) add_text_to_file(&output, "\ndec byte [rsi]");
    else {
        char text[255];
        sprintf(text, "\nsub byte [rsi], %d", count);
        add_text_to_file(&output, text);
    }
}

void dot() {
    add_text_to_file(&output, "\nmov rax, 1\nmov rdi, 1\nmov rdx, 1\nmov r10, rsi\nmov rsi, r10\nsyscall\nmov rsi, r10");
}

void comma() {
    add_text_to_file(&output, "\nmov rax, 0\nmov rdi, 0\nmov rdx, 1\nsyscall");
}

void zero() {
    add_text_to_file(&output, "\nmov byte [rsi], 0");
}

void bracket_open() {
    array_push(&brackets_stack, current_loop_id);
    char label_start[64], label_end[64];
    sprintf(label_start, "loop_start_%d", current_loop_id);
    sprintf(label_end, "loop_end_%d", current_loop_id);

    char text[255];
    sprintf(text, "\n%s:"
                  "\ncmp byte [rsi], 0"
                  "\nje %s", label_start, label_end);

    add_text_to_file(&output, text);
    current_loop_id++;
}

void bracket_close() {
    int id = array_pop(&brackets_stack);
    char label_start[64], label_end[64];
    sprintf(label_start, "loop_start_%d", id);
    sprintf(label_end, "loop_end_%d", id);

    char text[255];
    sprintf(text, "\njmp %s\n%s:", label_start, label_end);

    add_text_to_file(&output, text);
}
