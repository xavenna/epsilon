#include <fstream>
#include <iostream>
#include <vector>
#include <cctype>
#include <filesystem>
#include "epsilon.h"
#include "interpret.h"
#include "token.h"
#include "transform.h"
#include "define.h"
#include "util.h"
#include "bytecode.h"

// this is an environment for a language, called epsilon. It is intended to self-bootstrap, and is extensible
// components:
// dictionary--contains a list of words, both base words and user-defined words
// interpreter--turns a user program into a 'SLI', a simplified list of instructions
// transformator--transforms the SLI into c++ code to be compiled
// executor--runs a SLI as an interpreter
// expandinator--adds additional instructions to the dictionary permanently

// this is inspired by FORTH and Emacs
// it is a stack-based language

// Words:
// print -- pops the top value from the stack, converts it to a ascii string, and prints it to stdout
// add -- adds the top two values from the stack and pushes the sum to the stack
// sub -- pops A and B from stack and pushes B-A
// swap -- swaps top two stack values
// dup -- duplicates top of stack
// <val> -- pushes specified numerical value to stack
// if -- pops two values from the stack, if they are the same, execute next instruction, otherwise, skip.

namespace fs = std::filesystem;

int main(int argc, char** argv) {  //this is just driver code right now, this will change
  if(argc < 2) {
    fs::path at(argv[0]);
    std::cout << "Error: improper usage of " << at.filename() << ".\n";
    std::cout << "proper usage:\nepsilon <command>\n";
    std::cout << "Commands are: interpret, execute, transform\n";
    return 0;
  }
  std::string arg(argv[1]);
  if(arg == "help") {
    std::cout << "Epsilon\n";
  }
  else if(arg == "build") {
    //run turn .ep into .cpp in one step
    if(argc < 4) {
      SLI res;
      interpret(argv[2], res);
      slidump(res, ".tmp/tmp.sli");
      bytecodeGen(".tmp/tmp.sli", ".tmp/tmp.bcl");
      transform(".tmp/tmp.bcl", argv[3]);
    }
  }
  else if(arg == "interpret") {
    if(argc < 4) {
      std::cout << "Error: Missing arguments for command `interpret'\n";
    }
    else {
      SLI res;  //result of interpretation
      interpret(argv[2], res);
      slidump(res, argv[3]);
    }
  }
  else if(arg == "bytecode") {
    if(argc < 4) {
      std::cout << "Error: Improper usage of `bytecode' subcommand.\n";
    }
    else {
      bytecodeGen(argv[2], argv[3]);
    }
  }
  else if(arg == "execute") {
    //execute
    std::cout << "This subcommand has not yet been created...\n";
  }
  else if(arg == "transform") {
    if(argc < 4) {
      std::cout << "Error: Improper usage of `transform' subcommand.\n";
    }
    else {
      transform(argv[2], argv[3]);
    }
  }
  else if(arg == "define") {
    if(argc < 4) {
      std::cout << "Error: Improper usage of `define' subcommand.\n";
    }
    else {
      dictAdd(argv[2], argv[3]);
    }
  }
  return 0;
}
