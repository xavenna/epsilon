#include <string>
std::string lowercase(std::string in) {
  std::string e;
  for(auto x : in) {
    e += std::tolower(x);
  }
  return e;
}
bool isNum(std::string st) {
  for( auto x : st) {
    if(!isdigit(x))
      return false;
  }
  return true;
}
