#include <iostream>
#include <fstream>
#include <string>
#include "define.h"

// THIS DOESN'T WORK: THIS NEEDS TO BE FIXED

int dictAdd(std::string name, std::string fname) {
  std::string fileCont;
  std::string line;
  std::string ffname;
  std::ifstream get(fname);
  std::ofstream put;
  if(!get.is_open()) {
    std::cout << "Error: file could not be opened.\n";
    return -1;
  }
  while(get.peek() != EOF) {
    std::getline(get, line);
    fileCont += line + '\n';
  }
  get.close();
  get.open(".dict/.epd");  //open index file, search for `name'
  while(get.peek() != EOF) {
    std::getline(get, line);
    if(line == name) {
      std::cout << "Error: word '" << name << "' already defined.\n";
      return -1;
    }
  }
  put.open(".dict/.epd");
  put << name << '\n';
  put.close();
  ffname = ".dict/";
  ffname += name + ".epd";
  put.open(ffname);
  put << fileCont;
  put.close();
  return 0;
}
