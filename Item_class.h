#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;



int stringToInt(string str){
  stringstream ss;
  int x;
  ss << str;
  ss >> x;
  return x;
}

class Item
{
 protected: 
  string Name, itemUsageText;
  int itemId;
 Item(string name, string text, int id) : Name(name), itemUsageText(text), itemId(id)
  {};
  Item(string filepath, int itemId, int roomId);
  Item();
 public:
  virtual ~Item();
  string getName() ;
  string useItem() ;
};

class Portable : public Item
{
 public:
  Portable();
  Portable(string filepath, int itId, int roomId = 0)
   {
   ifstream file;
   string y,x;
   int d;
   bool Sameroom = true;
   file.open(filepath.c_str());
   if(!file.is_open())
     cerr << "kunde inte öppna filen \n";
   if(roomId != 0){
   while(!file.eof()){
     getline(file,x,';');
     d = stringToInt(x);
     if(d == roomId)
       break;
     getline(file,x,'¤');
   }
   }
   while(!file.eof() || Sameroom == true){
     getline(file,x,';');
     d = stringToInt(x);
     if(d == itId){
       itemId = d;
       getline(file,x,';');
       getline(file,y,';');
       Name = x;
       itemUsageText = y;
       break;
     }
     if(d < 2000 || d >= 1000)
       Sameroom = false;
   }
   }
  string getName() ;
  string useItem() ;
};



string Portable::getName(){
  return Name;
}
string Portable::useItem(){
  return itemUsageText;
}

Portable::Portable()
{
  Name = "";
  itemUsageText = "";
  itemId = 0;
}
