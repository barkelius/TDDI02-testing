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


void Room::printRoom(){                                                    //Testfunktion för utskrift av variabler
    cout << "roomId = " << roomId << endl;
    cout << "roomName = " << roomName << endl;
    cout << "roomDescription = " << roomDescription << endl;
    cout << "room_image =" << roomImage << endl;
    cout << "isWinRoom = " << winRoom << endl;
    cout << "west=" << west << ", east=" << east << ", north=" << north 
	 << ", south=" << south << endl;

    for(int i = 0; i < itemList.size(); i++)                             //Testfunktion för utskrift 
      itemList.at(i).printPortable();
    alliedNpc.printAllied();
  }
Room::Room() = default;                                                  //Defaultkonstruktor
 
Room::Room(string filepath, int id){
    ifstream file;
    string tmp;
    int check;
    file.open(filepath.c_str());                                        //Öppna fil
    if(!file.is_open())
      cerr<< "error: can't open file\n";
    while(!file.eof()){
      getline(file, tmp, ';');                                          //Läs in ID och leta efter rätt ID
      check = stringToInt(tmp);
      if(check == id)
	break;
      getline(file,tmp,'¤');                                           //Läs in resten av rummet
    }
    roomId = check;                                                    //Ta in all information till rummet som sak skapas
    getline(file, tmp, ';');
    roomName = tmp;
    getline(file, tmp, ';');
    roomDescription = tmp;
    getline(file, tmp, ';');
    roomImage = tmp;
    getline(file, tmp, ';');
    north = stringToInt(tmp);
    getline(file, tmp, ';');
    south = stringToInt(tmp);
    getline(file, tmp, ';');
    east = stringToInt(tmp);
    getline(file, tmp, ';');
    west = stringToInt(tmp);
    getline(file, tmp, ';');
    winRoom = stringToInt(tmp);
    while(!file.eof()){ 
      getline(file, tmp, ';');                                          //Läs in alla items
      check = stringToInt(tmp);
      getline(file,tmp);                                  
      if(check < 3000 && check >= 2000){
	Portable item = Portable(filepath, check, id);                  //Skapa de items som finns i rummet
	itemList.push_back(item);
      }
      else if(check < 4000 && check >= 3000){                           //Skapa karaktär som finns i rummet
	Allied tmpNpc(filepath, id);
	alliedNpc = tmpNpc;
	break;
      }
      else if(check < 2000)                                             //Avsluta om vi kommer till nytt rum
	break;
    }    
  }
 
  
int Room::doorDirection(string direction){                            //Returnerar ID:t till den riktning som funktionen får
    if(direction == "west")
      return west;
    else if(direction == "east")
      return east;
    else if(direction == "north")
      return north;
    else if(direction == "south")
      return south;
    return 0;
  }

Room& Room::operator =(const Room& other){                            //Kopieringstilldelningsoperator
  this->roomName = other.roomName;                                    //Kopiera alla värden till det nya rummet
  this->roomDescription = other.roomDescription;
  this->winRoom = other.winRoom;
  this->roomId = other.roomId;
  this->roomImage = other.roomImage;
  this->north = other.north;
  this->south = other.south;
  this->west = other.west;
  this->east = other.east;
  this->itemList.clear();
  for(int i = 0; i < other.itemList.size(); ++i)                     //Kopiera alla items till det nya rummet
    this->itemList.push_back(other.itemList.at(i));
  this->alliedNpc = other.alliedNpc;                                 //Kopiera karaktären till det nya rummet
  return *this;
}
 

