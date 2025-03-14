# CHIP8_emulator

This repository is ongoing effort towards building a CHIP-8 emulator or interpretor. [CHIP-8](https://github.com/mattmikolay/chip-8) was a simple to use interpreter programming language popular in the 1970s. It was later reintroduced in the 1990s in the shape of the HP84 graphic calculator. A typical system that used CHIP-8 had around 4KB of RAM and each instruction consisted of exactly 2 bytes. The main components required for CHIP-8 emulation are the memory, disassembler, registers, timer, keyboard, and display. In this repository we'll handle all of these to consturct a functional emulator for the system.

# Instuction Set
The complete instruction set of the CHIP-8 language can be found [here]( https://github.com/mattmikolay/chip-8/wiki/CHIP%E2%80%908-Instruction-Set) and [here](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#3xkk). I consists of a total set of 35 instructions.

# Dependencies
CMake

Raylib

