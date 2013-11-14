#include <iostream>
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
 public:
 Item(string name, string text, int id) : Name(name), itemUsageText(text), itemId(id)
    {};
 //Item(string filepath, int itemId ) : Name(), ItemUsageText(), itemId()
 // {};

 ~Item();
 virtual getName() = 0;
 virtual useItem() = 0;
};




class Portable
:public Item
{
 protected:
  Portable(string filepath, int itemId, int roomId)
   {
   ifstream file;
   string a,s;
   int d;
   stringstream ss;

   file.open(filepath.c_str());
   if(!file.is_open())
     cerr << "kunde inte öppna filen \n";

   while(true){
     getline(file,x,';');
     ss.clear();

     if(stringToInt(x) == itemId)
       break;

   }

 public:
  string getName();



 private:


};

