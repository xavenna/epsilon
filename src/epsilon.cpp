#include "epsilon.h"
Inst::Inst() {
  type = Nil;
  value = 0;
}

bcInst::bcInst() {
  type = NilBC;
  value = 0;
}
bcInst::bcInst(Oper op, int val, std::string n) {
  type = op;
  value = val;
  name = n;
}

BCL& BCL::app(bcInst ins) {
  list.push_back(ins);
  return *this;
}

BCL& BCL::app(Oper op, int val, std::string n) {
  list.push_back(bcInst(op, val, n));
  return *this;
}
