# 🧠 Brainfuck to NASM x64 Compiler

This project is a simple compiler that translates [Brainfuck](https://esolangs.org/wiki/Brainfuck) source code into x86-64 NASM assembly.

It does **not interpret** or simulate Brainfuck — it directly **generates .asm** output that can be assembled and run as native Linux binaries.

---

## 🗂️ What This Project Does

- Takes a `.txt` file with Brainfuck code as input
- Translates each Brainfuck command into corresponding NASM x64 instructions
- Outputs an `output.asm` file containing valid assembly code
- You can then assemble and run the generated code manually (or automatically)

---

## ⚙️ How to Use

1. In the `input.b` file, write your Brainfuck code.  
   For example:

```brainfuck
++++++++[>++++++++<-]>+.
```

2. Run `docker-compose up --build` and wait for complete.
3. Check output.