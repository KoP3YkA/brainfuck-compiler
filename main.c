#include <stdio.h>
#include "lib/array/array.h"
#include "lib/files/file_manager.h"
#include "lib/logic/compiler_logic.h"

CompilerFile output = { "output.asm" };
int current_loop_id = 0;
Array brackets_stack;

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

    int res = logic(text);

    array_free(&brackets_stack);

    add_text_to_file(&output, "\n\n_end:\nmov rax, 60\nsyscall");

    return res;
}
