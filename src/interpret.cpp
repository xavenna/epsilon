#include "interpret.h"
#include "token.h"

int interpret(std::string filename, SLI& out) {
  std::ifstream get(filename);
  std::string line;
  std::string index;
  std::vector<Inst> tline;
  LabelReg reg;  //used to make sure all labels are unique
  PrefixMaker pm;  //used for same purpose as `reg'
  SLI tok;
  if(!get.is_open()) {
    //error, file couldn't be opened
    return -1;
  }
  while(get.peek() != EOF) {
    std::getline(get, line);
    tline.clear();
    //process line
    tokenize(line + " ", tline); //add space so last word is recognized as a token
    add(tok, tline);  //add tokens from the line to the token list
  }
  indexGen(index);
  dictRes(tok, out, index, reg, pm);
  return 0;
}
