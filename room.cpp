#include "room.h"
#include <vector>
#include "functions.h"
#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;


void Room::printRoom(){
    cout << "roomId = " << room_id << endl;
    cout << "roomName = " << room_name << endl;
    cout << "roomDescription = " << room_description << endl;
    cout << "room_image =" << room_image << endl;
    cout << "isWinRoom = " << winRoom << endl;
    cout << "west=" << west << ", east=" << east << ", north=" << north 
	 << ", south=" << south << endl;

    for(int i = 0; i < itemList.size(); i++)
      itemList.at(i).printPortable();
    alliedNpc.printAllied();
  }
Room::Room() = default;
 
Room::Room(string filepath, int id){
    ifstream file;
    string x,y;
    int b;
    file.open(filepath.c_str());
    if(!file.is_open())
      cerr<< "error: can't open file\n";
    while(!file.eof()){
      getline(file, x, ';');
      b = stringToInt(x);
      if(b == id)
	break;
      getline(file,x,'¤');
    }
    room_id = b;
    getline(file, x , ';');
    room_name = x;
    getline(file, x , ';');
    room_description = x;
    getline(file, x , ';');
    room_image = x;
    getline(file, x , ';');
    north = stringToInt(x);
    getline(file, x , ';');
    south = stringToInt(x);
    getline(file, x , ';');
    east = stringToInt(x);
    getline(file, x , ';');
    west = stringToInt(x);
    getline(file, x , ';');
    winRoom = stringToInt(x);
    while(!file.eof()){
      getline(file, x, ';');
      b = stringToInt(x);
      getline(file,x);
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
    }    
  }
 
  
int Room::doorDirection(string apa){
    if(apa == "west")
      return west;
    else if(apa == "east")
      return east;
    else if(apa == "north")
      return north;
    else if(apa == "south")
      return south;
    return 0;
  }

Room& Room::operator =(const Room& other){
  this->room_name = other.room_name;
  this->room_description = other.room_description;
  this->winRoom = other.winRoom;
  this->room_id = other.room_id;
  this->room_image = other.room_image;
  this->north = other.north;
  this->south = other.south;
  this->west = other.west;
  this->east = other.east;
  this->itemList.clear();
  for(int i = 0; i < other.itemList.size(); ++i)
    this->itemList.push_back(other.itemList.at(i));
  this->alliedNpc = other.alliedNpc;
  return *this;
}
 

