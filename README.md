### EPSILON

Epsilon is a programming language designed around the principles of expandibility and
the stack. It is heavily inspired by FORTH

Epsilon code is stored in .ep files, and consists of a series of instructions. These instructions include numbers, intrinsic commands, and defined commands

Eventually, epsilon code will have three execution paths:
1) Transpilation to C++
2) Interpretation
3) Compilation (maybe)


### Transpilation
This is the only approach that has been implemented so far. After processing the code into
simple instructions, the transpiler converts each instruction into a snippet of c++ code.
Afterwards, it can be compiled using g++ (other compilers should work, but I haven't tested).

### Interpretation
This path hasn't been fully implemented. In theory, once the code has been converted into bytecode, the interpreter will execute it.

### Compilation
I'm not sure if this will ever be implemented, it is more of a `stretch goal'. This path
would likely rely on something like LLVM to facilitate the production of machine code for
different architectures.


## Execution Steps
Each execution path is broken into several execution steps, explained here
(Many of these names are unclear and confusing, and are subject to change.)

* Interpretation
* Bytecode generation
* Execution
* Transformation


### Interpretation
Interpretation consists of reading an epsilon code file and transforming it into a list of
atomic instructions, stored as a SLI (simplified instruction list). During this process,
dictionary expansion occurs, where defined commands are replaced with their definitions.
This process occurs recursively until no defined commands remain.

[epsilon file] ==> [SLI file]\
syntax: `epsilon interpret <epsilon file> <sli file>'


### Bytecode generation
Bytecode generation is a misnomer. In reality, this stage involves turning each atomic
instruction into simpler instructions, which are similar to an assembly language The result
is, however, not stored in a binary format.

[SLI file] ==> [Bytecode file]\
syntax: `epsilon bytecode <sli file> <bytecode file>'


### Execution
Execution has not yet been implemented. It will consist of loading a bytecode file and
running it.

No transformations occur\
syntax: `epsilon execute <bytecode file>'


### Transformation
Transformation is the process of taking a bytecode file and generating equivalent c++ code.
This code can then be compiled using a standard c++ compiler.

[Bytecode file] ==> [c++ source file]\
syntax: `epsilon transform <bytecode file> <c++ source file>'



## The Dictionary
The dictionary is a component of epsilon. It consists of a list of defined words, along with
a definition, which is a snippet of epsilon code. The dictionary is stored in the .dict/
directory.\
Commands can be added to the dictionary using the following syntax:\
`epsilon define <command> <epsilon source file>'


# Credits:

created by xavenna