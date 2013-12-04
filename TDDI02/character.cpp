//#include "character.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "functions.h"
#include "character.h"
using namespace std;

void Character::printAllied(){
  cout << "characterId = " << characterId << endl;
  cout << "characterName = " << characterName << endl;
  cout << "characterText = " << characterText << endl;
}

Character::Character()
{
    characterText = "";
    characterName = "";
    characterId = 0;
}

Character::~Character()
{
    //dtor
}

Allied::Allied(string filePath,int roomId){
  ifstream file;
  string x,y;
  int b;
  stringstream ss;
  file.open(filePath.c_str());
  if(!file.is_open())
    cerr << "error: can't open file\n";
  while(!file.eof()){
    getline(file,x,';');
    b = stringToInt(x);
    if(b == roomId){
      break;
    }
    getline(file,x,'¤');
  }
  b = 0;
  while(!file.eof()){
    getline(file,x,';');
    b = stringToInt(x);
    if(b >= 3000 && b < 4000){
      break;
    }
  }
  characterId = b;
  getline(file,x,';');
  characterName = x;
  getline(file,y,';');
  characterText = y;
}

Character::Character(string filePath,int roomId){
  characterId = 0;
  characterName = "";
  characterText = "";
}
