#ifndef USEFRT_H
#define USEFRT_H
//USEFul RouTines; contains several functions to do various things
bool ifMatch(char n, std::string key);
bool isEmpty(std::string n);
std::string tos(int n);
std::string getUnt(std::string in, std::string unt);
std::string getAft(std::string in, std::string unt);
std::string alp();
std::string io(std::string in);
void strToMap(std::string a, std::string b, std::map<std::string, std::string>&);
std::string chAdd(std::string in, int n);
std::string chAdd(char in, int n);
std::string chSub(std::string in, int n);
std::string chSub(char in, int n);
std::string fLoad(std::string fname);
bool fPrint(std::string fname, std::string content);
void parse(std::string n, std::deque<std::string>& th, std::string key = "./\\-");
void bk(std::string n, std::deque<std::string>& th);
std::string tf(std::string in, std::string l1, std::string l2);
#endif
