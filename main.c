#include <stdio.h>
#include "lib/array/array.h"
#include "lib/files/file_manager.h"

CompilerFile output = { "output.asm" };
int current_loop_id = 0;
Array brackets_stack;

void move_right() {
    add_text_to_file(&output, "\ninc rsi");
}

void move_left() {
    add_text_to_file(&output, "\ndec rsi");
}

void plus() {
    add_text_to_file(&output, "\ninc byte [rsi]");
}

void minus() {
    add_text_to_file(&output, "\ndec byte [rsi]");
}

void dot() {
    add_text_to_file(&output, "\nmov rax, 1\nmov rdi, 1\nmov rdx, 1\nmov r10, rsi\nmov rsi, r10\nsyscall\nmov rsi, r10");
}

void comma() {
    add_text_to_file(&output, "\nmov rax, 0\nmov rdi, 0\nmov rdx, 1\nsyscall");
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

int main() {
    array_init(&brackets_stack);
    create_file_if_not_exists(&output);
    overwrite_file(&output, "section .bss\ntape resb 30000\n\nsection .text\nglobal _start\n\n_start:\nmov rsi, tape");

    CompilerFile file = { "input.b" };
    char* text = file_read(&file);

    if (!text) {
        printf("Cannot find input.b file");
        return -1;
    }

    for (int i = 0; text[i] != '\0'; i++) {
        char chr = text[i];

        if (chr == '>') move_right();
        else if (chr == '<') move_left();
        else if (chr == '+') plus();
        else if (chr == '-') minus();
        else if (chr == '.') dot();
        else if (chr == '[') bracket_open();
        else if (chr == ']') bracket_close();
        else if (chr == ',') comma();
        else return -2;
    }

    array_free(&brackets_stack);

    add_text_to_file(&output, "\n\n_end:\nmov rax, 60\nsyscall");

    return 0;
}
