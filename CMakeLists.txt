cmake_minimum_required(VERSION 3.27)
project(brainfuck_compiler C)

set(CMAKE_C_STANDARD 11)

add_executable(brainfuck_compiler main.c
        lib/array/array.c
        lib/array/array.h
        lib/files/file_manager.c
        lib/files/file_manager.h)
