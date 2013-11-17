#ifndef FUNCTION_H
#define FUNCTION_H
#include <sstream>
using namespace std;



int stringToInt(string str){
  stringstream ss;
  int x;
  ss << str;
  ss >> x;
  return x;
}
string intToString(int x){
  stringstream ss;
  ss << x;
  string str = ss.str();
  return str;
}
#endif
