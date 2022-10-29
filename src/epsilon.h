#ifndef EPSILON_H
#define EPSILON_H
#include <vector>
#include <string>

enum Word {
  Add, Sub, Swap, Dup, Disc, Get, Put, Print, Val, If, Custom, Lbl, Goto, Nil
};  //  this is a list of the built-in words, as well as 'Custom', for words defined in dictionary
enum Oper {
  PushA, PushB, PushC, PushR, PushVal, PopA, PopB, PopC, PopR, AddAB, AddAC, AddBC, SubAB, SubAC, SubBC, PrintN, PrintC, IfBC, LblBC, GotoBC, NilBC
};

class Token {
  
};

class Inst {
public:
  Word type;
  int value;
  std::string name;
  Inst();
};
class bcInst {
public:
  Oper type;
  int value;
  std::string name;
  bcInst();
  bcInst(Oper, int = 0, std::string = "");
};

class SLI {
 public:
  std::vector<Inst> list;
};
class BCL {
public:
  std::vector<bcInst> list;
  BCL& app(bcInst);
  BCL& app(Oper, int = 0, std::string = "");
};
#endif
