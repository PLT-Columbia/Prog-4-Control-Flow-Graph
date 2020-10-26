# COMS W4115: Programming Assignment 4 (Control Flow Graph)

## Course Summary

Course: COMS 4115 Programming Languages and Translators (Fall 2020)  
Website: https://www.rayb.info/fall2020  
University: Columbia University.  
Instructor: Prof. Baishakhi Ray


## Logistics
* **Announcement Date:** **(TBD)**Thursday, October 1, 2020
* **Due Date:** **(TBD)**Wednesday, October 14, 2020 by 11:59 PM. **No extensions!**
* **Total Points:** **(TBD)**100

## Grading Breakdown
* **(TBD)**

## Assignment Objectives

From this assignment:

1. You **will learn** how to write a LLVM pass.
2. You **will learn** how to generate control flow graph by analyzing the basic blocks.
3. You **will learn** how to perform analysis on a control flow graph using LLVM API.

## Assignment

In previous assignments for syntax analysis and sematic analysis, you worked with `clang`, the LLVM frontend for C C++ and Objective-C.

The core of LLVM is the [intermediate representation](https://en.wikipedia.org/wiki/Intermediate_representation) (IR), a low-level programming language similar to assembly, which abstract away most details of the programming language and the target. When compiling a programming language under LLVM, it will first convert the specific programming language into IR, then perform analysis / optimizations against the IR, and finally generate the target binary code (e.g. x86, ARM, ...).

Optimizations are implemented as Passes that traverse some portion of a program to either collect information or transform the program.

We will work with IR and LLVM pass for this assignment.

### Get started

1. Convert `bubble.c` to IR:
```
LLVM_HOME="<the absolute path to llvm-pproject>"
export PATH="$LLVM_HOME/build/bin:$PATH"

clang -O0 -emit-llvm -c bubble.c
llvm-dis bubble.bc
```

You will get `bubble.bc`, which contains the IR in binary format, and `bubble.ll`, which contains the IR in human-readable format.

2. Generate the CFG of `bubble.bc`:
```
cd ./examples

opt -dot-cfg < bubble.bc
dot -Tpdf .bubbleSort.dot -o bubblesort-detailed.pdf

opt -dot-cfg-only < bubble.bc
dot -Tpdf .bubbleSort.dot -o bubblesort.pdf

cd ..
```

Then you can view the CFG of `bubbleSort()` in `bubble.c`. Obviously you can view the CFG of other functions with `dot` command, e.g. `dot -Tpdf .printArray.dot -o printArray.pdf`.

3. Create a new folder `clang-hw4` in `llvm-project/llvm/lib/Transforms` for this assignment, and copy the files:
```
cp -r ./src "$LLVM_HOME/llvm/lib/Transforms/clang-hw4"
```

4. Append `add_subdirectory(clang-hw4)` to `$LLVM_HOME/llvm/lib/Transforms/CMakeLists.txt`.

5. Build `clang-hw4`:
```
cd "$LLVM_HOME/build"
make
```

6. For the following parts of the assignment, you may assume that for each function, exactly one basic block will have `ret` as its [terminator instruction](https://llvm.org/docs/LangRef.html#terminator-instructions), with other basic blocks having `br` as their [terminator instruction](https://llvm.org/docs/LangRef.html#terminator-instructions). You may also assume that `br` will have *at most* **2** successors.

### Part 1: Generate CFG

In this part, you need to construct the CFG of a function by analyzing the basic blocks.

Instead of generating a dot file yourself, please use the `OFile` class to output all the edges you found. The results will be saved to `<function_name>.txt`.

Compare the edges you found with `bubblesort.pdf` for sanity check.

### Part 2: Analyze CFG

You can do many kinds of analysis / transformations against a CFG. For example, dead block elimination, loop detection / simplification, ...

In this part, you need to identify all the "**key blocks**" in a function. We define "**key block**" as following: a **key block** is the basic block of a function, such that every path from the entry of the function to the exit of the function **MUST** go through this basic block.

Remember that you may assume that exactly **one** basic block will have `ret` as its [terminator instruction](https://llvm.org/docs/LangRef.html#terminator-instructions) in each function, and `ret` is considered to be the exit of a function.

1. Note that the entry basic block, and the basic block with `ret` instruction are also **key blocks** by definition.

3. Hint: instead of removing / re-inserting a basic block directly, you can change the [terminator instruction](https://llvm.org/docs/LangRef.html#terminator-instructions) of the basic block that you want to delete, then change it back to the original instruction to re-insert the basic block.

4. You need to figure out which APIs you should use for this task. It's also OK if you prefer to construct a graph structure yourself and analyze it manually.