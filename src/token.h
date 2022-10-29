#ifndef TOKEN_H
#define TOKEN_H
//includes that are required for proper functionality of this module
#include <string>
#include <vector>
#include <deque>
#include <map>
#include "epsilon.h"
#include "util.h"
class LabelReg {
public:
  std::deque<std::string> list;
  std::deque<std::string> newlist;
};
class LabelHash {
public:
  std::map<int, std::string> hash;
};
class PrefixMaker {
public:
  int num;
  PrefixMaker() {num = 0;}
  int getNextPrefix() {return ++num;}
};

void labelClean(SLI&, PrefixMaker&);
void indexGen(std::string&);
int expandCustom(Inst, SLI&, LabelReg&, PrefixMaker&);
int dictRes(const SLI&, SLI&, const std::string&, LabelReg&, PrefixMaker&);
int tokenize(std::string, std::vector<Inst>&);
int add(SLI&, std::vector<Inst>);
void slidump(SLI, std::string);
void bcldump(BCL, std::string);
void sliLoad(SLI&, std::string);
void bclLoad(BCL&, std::string);
Inst makeWord(std::string);
std::string InStr(Inst);
std::string InStrD(Inst);  //for dumping sli file
std::string BcInStrD(Oper);

#endif
