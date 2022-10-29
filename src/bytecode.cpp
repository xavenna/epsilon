#include <string>
#include <iostream>
#include "epsilon.h"
#include "token.h"
#include "bytecode.h"

int bytecodeGen(std::string filename, std::string outfile) {
  //turn a SLI into a BCL
  SLI list;
  sliLoad(list, filename);
  BCL out;

  for(auto x : list.list) {
    switch(x.type) {
    case Add: //clobbers A and B
      out.app(PopA).app(PopB).app(AddAB).app(PushA);
      break;
    case Sub: //clobbers A and B
      out.app(PopB).app(PopA).app(SubAB).app(PushA);
      break;
    case Swap: //clobbers A and B
      out.app(PopA).app(PopB).app(PushA).app(PushB);
      break;
    case Dup:  //clobbers C
      out.app(PopC).app(PushC).app(PushC);
      break;
    case Disc:  //clobbers C
      out.app(PopC);
      break;
    case Get:
      out.app(PopR);
      break;
    case Put:
      out.app(PushR);
      break;
    case Print:  //clean
      out.app(PrintN);
      break;
    case Val:  //clean
      out.app(PushVal, x.value);
      break;
    case If:  //clean
      out.app(PopA).app(PopB).app(IfBC);
      break;
    case Lbl:
      out.app(LblBC, x.value, x.name);
      break;
    case Goto:
      out.app(GotoBC, x.value, x.name);
      break;
    case Nil:
      std::cout << "Error: Invalid instruction. This error was likely caused by invalid user code.\n";
      break;
    default:
      break;
    }
  }
  bcldump(out, outfile);
  return 0;
}
