#include "character.h"
#include <vector>
#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;


class Room{
public:
  /*
  Room(bool a, int b, string d, vector<pair<string, int > > c) 
    : is_win_room(a), room_id(b), room_image(d), door_ids(c) 
  {}	
  */
  void printRoom(){
    cout << "roomId = " << room_id << endl;
    cout << "roomName = " << room_name << endl;
    cout << "roomDescription = " << room_description << endl;
    cout << "isWinRoom = " << is_win_room << endl;
    for(int i = 0; i < door_ids.size(); i++)
      cout << door_ids.at(i).first << ": " 
	   << door_ids.at(i).second << endl;
    for(int i = 0; i < itemList.size(); i++)
      itemList.at(i).printPortable();
    alliedNpc.printAllied();
  }
  Room() = default;
  Room(string filepath, int id){
    ifstream file;
    string x,y;
    int b;
    file.open(filepath.c_str());
    if(!file.is_open())
      cerr<< "error: can't open file\n";
    while(!file.eof()){
      getline(file, x, ';');
      b = stringToInt(x);
      if(b == id){
	room_id = b;
	getline(file, x , ';');
	room_name = x;
	getline(file, x , ';');
	room_description = x;
	getline(file, x , ';');
	b = stringToInt(x);
	door_ids.push_back(make_pair("north",stringToInt(x)));
	getline(file, x , ';');
	door_ids.push_back(make_pair("south",stringToInt(x)));
	getline(file, x , ';');
	door_ids.push_back(make_pair("east",stringToInt(x)));
	getline(file, x , ';');
	door_ids.push_back(make_pair("west",stringToInt(x)));
	getline(file, x , ';');
	is_win_room = stringToInt(x);
	while(!file.eof()){
	  getline(file, x, ';');
	  b = stringToInt(x);	
	  if(b < 3000 && b >= 2000){
	    Portable item = Portable(filepath, b, id);
	    itemList.push_back(item);
	  }
	  else if(b < 4000 && b >= 3000){
	    Allied tmpNpc(filepath, id);
	    alliedNpc = tmpNpc;
	    break;
	  }
	  else if(b < 2000)
	    break;
	  getline(file,x);
	}
      }
      else
	getline(file, x);
    }
  }
 
  
  int doorDirection(string apa){
    for(int i = 0; i < door_ids.size(); i++){
      if(apa == door_ids.at(i).first){
	return door_ids.at(i).second;
      }
    }
    return 0;
  }
  
  int getRoomId(){ return room_id;}
  string get_room_image(){ return room_image; }
  bool is_win_room;
  string room_name;
  string room_description;
  int door_id[4];
  vector<pair<string, int> > door_ids;
  int room_id;
  string room_image;	
  vector<Portable> itemList;
  Allied alliedNpc;
  
private:  
};

 /*  
  Room& operator =(const Room& other){
    cout << "hej4" << endl;
    this->room_name = other.room_name;
    this->room_description = other.room_description;
    this->is_win_room = other.is_win_room;
    this->room_id = other.room_id;
    this->room_image = other.room_image;
    cout << "hej6" << endl;
    for(int i = 0; i < other.door_ids.size(); i++){
      cout << i << endl;
      this->door_ids.at(i) = other.door_ids.at(i);
    }
    cout << "hej7" << endl;
    return *this;
    }*/
