#ifndef BRAINFUCK_COMPILER_GLOBAL_H
#define BRAINFUCK_COMPILER_GLOBAL_H

#include "files/file_manager.h"
#include "array/array.h"

extern CompilerFile output;
extern int current_loop_id;
extern Array brackets_stack;

#endif //BRAINFUCK_COMPILER_GLOBAL_H
