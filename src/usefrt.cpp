//usefrt.cpp
#include <string>
#include <map>
#include <functional>
#include <algorithm>
#include <deque>
#include <fstream>
#include <iostream>
#include "usefrt.h"

//USEFul RouTines; contains several functions to do various things
bool ifMatch(char n, std::string key) { //returns whether n is found in key
	return (key.find(n) != std::string::npos);
}
bool isEmpty(std::string n) {
	return (n.empty() ? 1 : (n == " " ? 1 : 0));
}
std::string tos(int n) {  //wrapper for to_string because to_string is long
	return std::to_string(n);
}
std::string getUnt(std::string in, std::string unt) { //a string up until another string
	return in.substr(0,in.find(unt));
}
std::string getAft(std::string in, std::string unt) { //a string, after the other string
	return in.substr(in.find(unt)+1);
}
std::string alp() {  //used for cipher routines, maybe scrap
	return std::string("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
}
std::string io(std::string in) {
	std::cout << in;
	std::getline(std::cin, in);
	return in;
}
void strToMap(std::string a, std::string b, std::map<std::string, std::string>&);  //need to write
std::string chAdd(std::string in, int n) {  //increment each character in a string by a set number
	std::string out;
	for(auto x : in) {
		if(x > 64 && x < 91) {
			int tmp;
			tmp = (x-64+n)%26;
			if(tmp<0)
				tmp+=26;
			out += (tmp==0?26:tmp)+64;
		}
		else if(x > 96 && x < 123) {
			int tmp;
			tmp = (x-96+n)%26;
			if(tmp<0)
				tmp+=26;
			out += (tmp==0?26:tmp)+96;
		}
	}
	return out;
}
std::string chAdd(char in, int n) {
	std::string out;
	if(in > 64 && in < 91) {
		int tmp;
		tmp = (in-64+n)%26;
			if(tmp<0)
				tmp+=26;
		out += (tmp==0?26:tmp)+64;
	}
	else if(in > 96 && in < 123) {
		int tmp;
		tmp = (in-96+n)%26;
			if(tmp<0)
				tmp+=26;
		out += (tmp==0?26:tmp)+96;
	}
	return out;
}
std::string chSub(std::string in, int n) {  //increment each character in a string by a set number
	std::string out;
	for(auto x : in) {
		if(x > 64 && x < 91) {
			int tmp;
			tmp = ((x-64)-n)%26;
			out += (tmp<=0?tmp+26:tmp)+64;
		}
		else if(x > 96 && x < 123) {
			int tmp;
			tmp = ((x-96)-n)%26;
			out += (tmp<=0?tmp+26:tmp)+96;
		}
	}
	return out;
}
std::string chSub(char in, int n) {
	std::string out;
	if(in > 64 && in < 91) {
		int tmp;
		tmp = ((in-64)-n)%26;
		out += (tmp<=0?tmp+26:tmp)+64;
	}
	else if(in > 96 && in < 123) {
		int tmp;
		tmp = ((in-96)-n)%26;
		out += (tmp<=0?tmp+26:tmp)+96;
	}
	return out;
}
std::string fLoad(std::string fname) {  //loads the contents of a file
	std::string out;
	std::string tmp;
	std::ifstream in;
	in.open(fname);
	if(!in.is_open())
		return out;
	while(in.peek() != EOF) {
		std::getline(in, tmp);
		out += tmp + '\n';
	}
	in.close();
	return out;
}
bool fPrint(std::string fname, std::string content) {  //adds 'content' to specified file
	std::ofstream out;
	out.open(fname);
	if(!out.is_open())
		return false;
	out << content;
	return true;
}
void parse(std::string n, std::deque<std::string>& th, std::string key) { //splits a string into a deque
	//each entry is a string delimited by a character in key, similar to bk but more general
	//default argument is "./\\-"
	std::string cw;
	for(size_t i=0;i<n.size();i++) {
		if(ifMatch(n[i], key)) {
			if(cw.empty())
				cw += '\0';
			th.push_back(cw);
			cw.clear();
		}
		else {
			cw += n[i];
		}
	}
}
void bk(std::string n, std::deque<std::string>& th) {  //parses input for shell
	/*RULE TABLE:
	 *  alphanumeric: add to cw
	 *  space: add cw to th, clear cw
	 *  backslash: turn escape on
	 *  vertical bar: add '\\|' to th (marks a pipe action)
	 *  quotes: turn in_q on
	 *q-alphanumeric: add to cw
	 *q-space: add to cw
	 *q-backslash: turn escape on
	 *e-alphanumeric: do something
	 *
	 * */
	//int last_q = -1;
	bool in_q = false;  //if the cursor is in quotation marks
	bool escape = false;  //if the next cursor is escaped
	std::string cw;  //current word
	for(size_t i=0;i<n.size();i++) {  //iterates through the characters in the string
		switch(n[i]) {
		case '\\':
			if(escape)
				cw += "\\\\";
			escape = !escape;
			break;
		case '\'':
			in_q = !in_q;
			break;
		case ' ':
			if(in_q)
				cw += n[i];
			else {
				th.push_back(cw);
				cw.clear();
			}
			break;
		case '|':
			if(cw == "") {
				th.push_back("\\|");
			}
			else {
				if(escape)
					cw += '|';
			}
			break;
		default:
			//handle escape characters
			if(escape) {
				switch(n[i]) {
					default:
						cw += n[i];
						break;
					//add more at some point, no escape characters yet
				}
			}
			else
				cw += n[i];
			break;
		}
		//finalization
	}
}
std::string tf(std::string in, std::string l1, std::string l2) {
	std::string out;
	std::map<char, char> key;
	for(unsigned i=0;i<(l1.size()>l2.size()?l1.size():l2.size());i++) {
		key.insert(std::pair<char, char> (l1[i], l2[i]));
	}
	char tmp;
	std::for_each(in.begin(), in.end(), [&, key](char n){
		for(auto x : key) {
			if(x.first == n) {
				tmp = x.second;
				break;
			}
			else
				tmp = n;
		}
		out += tmp;
	});
	return out;
}
