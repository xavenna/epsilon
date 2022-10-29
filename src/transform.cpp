#include <deque>
#include <iostream>
#include <string>
#include <fstream>
#include "epsilon.h"
#include "transform.h"
#include "token.h"

//rewrite this to use bytecode

int transform(std::string filename, std::string outfile) {
  if(filename.find(".bcl") != std::string::npos) {
    //transform bytecode file (still in text, not binary)
    std::ofstream out(outfile);
    BCL list;

    int inIf = 0;

    std::string program;
    std::string body;
    std::string header = "#include <iostream>\n#include <deque>\nint main(int argc, char** argv) {\nint A;\nint B;\nint C;\nint R;\nstd::deque<int> stack;\n";
    std::string footer = "return 0;\n}";
    bclLoad(list, filename);
    for(auto x : list.list) {
      switch(x.type) {
      case PushA:
	body += "stack.push_back(A);\n";
	break;
      case PushB:
	body += "stack.push_back(B);\n";
	break;
      case PushC:
	body += "stack.push_back(C);\n";
	break;
      case PushR:
	body += "stack.push_back(R);\n";
	break;
      case PushVal:
	body += "stack.push_back(" + std::to_string(x.value) + ");\n";
	break;
      case PopA:
	body += "A = stack.back();\nstack.pop_back();\n";
	break;
      case PopB:
	body += "B = stack.back();\nstack.pop_back();\n";
	break;
      case PopC:
	body += "C = stack.back();\nstack.pop_back();\n";
	break;
      case PopR:
	body += "R = stack.back();\nstack.pop_back();\n";
	break;
      case AddAB:
	body += "A = A+B;\n";
	break;
      case AddAC:
	body += "A = A+C;\n";
	break;
      case AddBC:
	body += "A = B+C;\n";
	break;
      case SubAB:
	body += "A = A-B;\n";
	break;
      case SubAC:
	body += "A = A-C;\n";
	break;
      case SubBC:
	body += "A = B-C;\n";
	break;
      case PrintN:
	body += "std::cout << std::to_string(stack.back())<<'\\n';\nstack.pop_back();\n";
	break;
      case PrintC:
	body += "std::cout << std::static_cast<char>(stack.back()));\nstack.pop_back();\n";
	break;
      case IfBC:
	body += "if(A==B) {\n";
	inIf++;
	continue;
	break;
      case LblBC:
	body += x.name + ":\n";
	break;
      case GotoBC:
	body += "goto " + x.name + ";\n";
	break;
      case NilBC:
	break;
      }
      if(inIf > 0) {
	//if next statement is in an if statement: then 
	body += "}\n";
	inIf--;
      }
    }
    out << header + body + footer;
    return 0;
  }
  else if(filename.find(".sli") != std::string::npos) {
    std::ofstream out(outfile);
    SLI list;
    
    int inIf = 0;  //whether the program is in an 'if' block
    
    std::string program;  //will contain the final program
    std::string body; //contains program body
    std::string header = "#include <iostream>\n#include <deque>\nint main(int argc, char** argv) {\nint A;\nint B;\nint C;\nint R;\nstd::deque<int> stack;\n";
    //eventually make it so necessary headers are determined during parsing
    std::string footer = "return 0;\n}";
    sliLoad(list, filename);
    //now, list contains the SLI for the program
    for(auto x : list.list) {
      switch(x.type) {
      case Val:
	//push value to stack
	body += "stack.push_back(";
	body += std::to_string(x.value) + ");\n";
	break;
      case Add:
	//add top two stack values
	body += "A=stack.back();\nstack.pop_back();\nB=stack.back();\nstack.pop_back();\nstack.push_back(A-B);\n";
	break;
      case Sub:
	//push difference of top two values
	body += "A=stack.back();\nstack.pop_back();\nB=stack.back();\nstack.pop_back();\nstack.push_back(B-A);\n";
	break;
      case Swap:
	//swap top two values
	body += "A=stack.back();\nstack.pop_back();\nB=stack.back();\nstack.pop_back();\nstack.push_back(A);\nstack.push_back(B);\n";
	break;
      case Dup:
	//duplicate top value
	body += "stack.push_back(stack.back());\n";
	break;
      case Disc:
	//discard top value
	body += "stack.pop_back();\n";
	break;
      case Get:
	//pop top of stack to register
	body += "R = stack.back();\nstack.pop_back();\n";
	break;
      case Put:
	//push register to top of stack
	body += "stack.push_back(R);\n";
	break;
      case Print:
	//print and discard top stack value
	body += "std::cout<<stack.back()<<'\\n';\nstack.pop_back();\n";
	break;
      case If:
	//pop and compare top two stack values. If they aren't the same, skip next instruction
	inIf++;
	body += "A=stack.back();\nstack.pop_back();\nB=stack.back();\nstack.pop_back();\nif(A==B){\n";
	continue;
      case Lbl:
	//create a label
	body += x.name + ":\n";
	break;
      case Goto:
	//goto a label
	body += "goto " + x.name + ";\n";
	break;
      default:
	std::cout << "Error: Invalid token. This is likely due to invalid user code.\n";
	break;
      }
      if(inIf > 0) {
	//if next statement is in an if statement: then 
	body += "}\n";
	inIf--;
      }
    }
    out << header + body + footer;
    return 0;
  }
  return 1; //invalid file extension
}
//stack is a deque, named `stack'
//there are several registers, named `A', `B', and `C'
