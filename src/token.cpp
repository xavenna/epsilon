#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "token.h"

std::string InStr(Inst n) {
  std::string nn = "Val:" + std::to_string(n.value);
  std::string nnn = "Custom:" + n.name;
  std::string nnnn = "Label:" + n.name;  //these variable names are really stupid
  std::string nnnnn = "Goto:" + n.name;
  switch(n.type) {
  case Add:
    return "Add";
    break;
  case Sub:
    return "Sub";
    break;
  case Swap:
    return "Swap";
    break;
  case Get:
    return "Get";
    break;
  case Put:
    return "Put";
    break;
  case Dup:
    return "Dup";
    break;
  case Disc:
    return "Disc";
    break;
  case Print:
    return "Print";
    break;
  case Val:
    return nn;
    break;
  case If:
    return "If";
    break;
  case Lbl:
    return nnnn;
    break;
  case Goto:
    return nnnnn;
    break;
  case Nil:
    return "Nil";
    break;
  case Custom:
    return nnn;
    break;
  default:
    //if this section of code is reached, there is a serious error. Contact the developer.
    return "Error: Something has gone horribly wrong...Please contact the developer";
    break;
  }
}
std::string InStrD(Inst n) {
  std::string nnn = "Custom:" + n.name;
  std::string nnnn = "lbl" + n.name;
  std::string nnnnn = "goto" + n.name;
  switch(n.type) {
  case Add:
    return "add";
    break;
  case Sub:
    return "sub";
    break;
  case Swap:
    return "swap";
    break;
  case Dup:
    return "dup";
    break;
  case Disc:
    return "disc";
    break;
  case Get:
    return "get";
    break;
  case Put:
    return "put";
    break;
  case Print:
    return "print";
    break;
  case Val:
    return std::to_string(n.value);
    break;
  case If:
    return "if";
    break;
  case Lbl:
    return nnnn;
    break;
  case Goto:
    return nnnnn;
    break;
  case Nil:
    return "nil";
    break;
  default:
    //if this section of code is reached, there is a serious error. Contact the developer.
    return "Error: Invalid SLI dump file. If the SLI file used was created by epsilon, please contact the developer";
    break;
  }
}
std::string BcInStrD(bcInst n) {
  std::string nn = "pushval:";
  nn += std::to_string(n.value);
  std::string nnn = "lblbc" + n.name;
  std::string nnnn = "gotobc" + n.name;
  switch(n.type) {
  case PushA:
    return "pusha";
    break;
  case PushB:
    return "pushb";
    break;
  case PushC:
    return "pushc";
    break;
  case PushR:
    return "pushr";
    break;
  case PushVal:
    return nn;
    break;
  case PopA:
    return "popa";
    break;
  case PopB:
    return "popb";
    break;
  case PopC:
    return "popc";
    break;
  case PopR:
    return "popr";
    break;
  case AddAB:
    return "addab";
    break;
  case AddAC:
    return "addac";
    break;
  case AddBC:
    return "addbc";
    break;
  case SubAB:
    return "subab";
    break;
  case SubAC:
    return "subac";
    break;
  case SubBC:
    return "subbc";
    break;
  case PrintN:
    return "printn";
    break;
  case PrintC:
    return "printc";
    break;
  case IfBC:
    return "ifbc";
    break;
  case LblBC:
    return nnn;
    break;
  case GotoBC:
    return nnnn;
    break;
  default:
    return "nilbc";
    break;
  }
}
Inst makeWord(std::string input) {
  Inst out;
  if(input == "print") {
    out.type = Print;
  }
  else if(input == "add") {
    out.type = Add;
  }
  else if(input == "sub") {
    out.type = Sub;
  }
  else if(input == "swap") {
    out.type = Swap;
  }
  else if(input == "dup") {
    out.type = Dup;
  }
  else if(input == "disc") {
    out.type = Disc;
  }
  else if(input == "get") {
    out.type = Get;
  }
  else if(input == "put") {
    out.type = Put;
  }
  else if(isNum(input) || input.substr(0,3) == "val") {
    out.type = Val;
    try {
    out.value = std::stoi(input);
    } catch (...) {
      std::cout << "Error: cannot convert '" << input << "' to string.\n";
    }
  }
  else if(input.substr(0,3) == "lbl") {
    out.type = Lbl;
    out.name = input.substr(3);
  }
  else if(input.substr(0,4) == "goto") {
    out.type = Goto;
    out.name = input.substr(4);
  }
  else if(input == "if") {
    out.type = If;
  }
  else { //dictionaryLookup
    out.type = Custom;  //for now, assumes it is a custom word
    out.name = input;
  }
  return out;
}
bcInst makeBcWord(std::string input) {
  bcInst out;
  if(input == "pusha") {
    out.type = PushA;
  }
  else if(input == "pushb") {
    out.type = PushB;
  }
  else if(input == "pushc") {
    out.type = PushC;
  }
  else if(input == "pushr") {
    out.type = PushR;
  }
  else if(input.substr(0,7) == "pushval") {
    out.type = PushVal;
    out.value = std::stoi(input.substr(8));
  }
  else if(input == "popa") {
    out.type = PopA;
  }
  else if(input == "popb") {
    out.type = PopB;
  }
  else if(input == "popc") {
    out.type = PopC;
  }
  else if(input == "popr") {
    out.type = PopR;
  }
  else if(input == "addab") {
    out.type = AddAB;
  }
  else if(input == "addac") {
    out.type = AddAC;
  }
  else if(input == "addbc") {
    out.type = AddBC;
  }
  else if(input == "subab") {
    out.type = SubAB;
  }
  else if(input == "subac") {
    out.type = SubAC;
  }
  else if(input == "subbc") {
    out.type = SubBC;
  }
  else if(input == "printn") {
    out.type = PrintN;
  }
  else if(input == "printc") {
    out.type = PrintC;
  }
  else if(input == "ifbc") {
    out.type = IfBC;
  }
  else if(input.substr(0,5) == "lblbc") {
    out.type = LblBC;
    out.name = input.substr(5);
  }
  else if(input.substr(0,6) == "gotobc") {
    out.type = GotoBC;
    out.name = input.substr(6);
  }
  else {
    std::cout << "Error: Invalid bytecode instruction '" << input << "'.\n";
    out.type = NilBC;
  }
  return out;
}
void slidump(SLI e, std::string fn) {
  std::ofstream get(fn);
  if(!get.is_open()) {
    //error
    return;
  }
  for(auto x : e.list) {
    get << InStrD(x) + '\n';
  }
}
void bcldump(BCL e, std::string fn) {
  std::ofstream get(fn);
  if(!get.is_open()) {
    //error
    return;
  }
  for(auto x : e.list) {
    get << BcInStrD(x) + '\n';
  }
}
void sliLoad(SLI& out, std::string fn) {
  std::ifstream get(fn);
  std::string line;
  if(!get.is_open()) {
    //error
    return;
  }
  while(get.peek() != EOF) {
    std::getline(get, line);
    out.list.push_back(makeWord(lowercase(line)));
  }
}
void bclLoad(BCL& out, std::string fn) {
  std::ifstream get(fn);
  std::string line;
  if(!get.is_open()) {
    //error
    return;
  }
  while(get.peek() != EOF) {
    std::getline(get, line);
    out.list.push_back(makeBcWord(lowercase(line)));
  }
}
int add(SLI& out, std::vector<Inst> tline) {
  for(auto x : tline) {
    out.list.push_back(x);
  }
  return 0;
}
int tokenize(std::string line, std::vector<Inst>& out) {
  std::string accum;
  if(line.substr(0,2) == "--")
    return 0; //comment, do nothing
  for(auto x : line) {
    if(x == ' ' || x == '\n') {
      out.push_back(makeWord(lowercase(accum)));
      accum.clear();
      //word boundary
    }
    else {
      accum += x;
    }
  }
  return 0;
}
int dictRes(const SLI& input, SLI& output, const std::string& index, LabelReg& la, PrefixMaker& pm) {  //driver code, this doesn't recurse
  for(auto x : input.list) {
    if(x.type == Custom) { //call expander
      //check if in dictionary
      if(index.find(x.name) != std::string::npos) {
	SLI files;
	//expand custom definition
	expandCustom(x, files, la, pm);
	//call dictRes on custom definition
	dictRes(files, output, index, la, pm);
      }
    }
    else {
      output.list.push_back(x);
    }
  }
  return 0;
}
void labelClean(SLI& in, PrefixMaker& pm) {
  std::string prefix = "_" + std::to_string(pm.getNextPrefix());  //contains a unique prefix generated for
  for(size_t i=0;i<in.list.size();i++) {
    if(in.list[i].type == Lbl || in.list[i].type == Goto) {  //find labels
      in.list[i].name = prefix + in.list[i].name;
    }
  }
}
int expandCustom(Inst x, SLI& output, LabelReg& la, PrefixMaker& pm) {
  SLI fin;  /// contains custom thing; works this way in order to uniquify labels
  std::string filename = ".dict/" + x.name + ".epd";
  std::ifstream get(filename);
  std::string def;
  std::string line;
  if(!get.is_open()) {
    //dictionary error
    std::cout << "Dictionary Error: operation not completed successfully.\n";
  }
  while(get.peek() != EOF) {
    std::getline(get, line);
    line = line + " ";
    tokenize(line, fin.list);
  }
  labelClean(fin, pm);
  add(output, fin.list);
  return 0;
}

void indexGen(std::string& index) {
  std::ifstream get(".dict/.epd");
  std::string line;
  std::string def;
  while(get.peek() != EOF) {
    std::getline(get, line);
    index += line + '\n';
  }
  get.close();
}
