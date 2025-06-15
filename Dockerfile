FROM gcc:latest

RUN apt update && apt install -y nasm

WORKDIR /app

COPY . .

RUN gcc main.c lib/files/file_manager.c lib/array/array.c -o bf_compiler

CMD ["/bin/bash", "-c", "./bf_compiler && nasm -f elf64 output.asm -o output.o && ld output.o -o output && ./output"]
