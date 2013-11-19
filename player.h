#ifndef PLAYER_H
#define PLAYER_H
#include "item.h"
#include "room.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
using namespace std;

class Player{
public:
  Player(string filePath);
  void printPlayer();
  void useItem(string name);


  void printInventory();
  void pickUpItem(string name);
  void talk();
  void walk(string direction);

private:
    Room currentRoom;
    vector <Portable> inventory;
    string currentFile;
};

Player::Player(string filePath){
  ifstream file;
  string x,y;
  int b;
  file.open(filePath.c_str());
  if(!file.is_open())
    cerr << "error: can't open file\n";
  while(!file.eof()){
    getline(file,x,';');
    b = stringToInt(x);
    if(b >= 80000)
      break;
    getline(file,x,';');
    getline(file,y,';');
    Portable item = Portable(filePath,b);
    inventory.push_back(item);
  }
  Room tmpRoom(filePath,b-80000);
  currentRoom = tmpRoom;
  file.close();
  currentFile = filePath;
}

void Player::printPlayer(){
  /*  for(unsigned i = 0; i < inventory.size(); ++i){
    cout << "itemId: " << inventory[i].getId() << endl;
    cout << "itemName: " << inventory[i].getName() << endl;
    cout << "itemText: " << inventory[i].useItem() << endl;
    }*/
  currentRoom.printRoom();
  }
void Player::useItem(string name){
  for(unsigned i = 0; i < inventory.size(); ++i){
    if(inventory[i].getName() == name){
      cout << "tog bort: " << inventory[i].getName() << endl;
      inventory.erase(inventory.begin()+i);
    }
  }
}


void Player::talk(){
  if(currentRoom.alliedNpc.getName() != ""){
    cout << currentRoom.alliedNpc.getName() << ": " 
	 << currentRoom.alliedNpc.getText() << endl;
  }
  else
    cout << "No character in this room." << endl;
}


void Player::pickUpItem(string name){
  int itemId;
  for(unsigned i = 0; i < currentRoom.itemList.size(); ++i){
    if(currentRoom.itemList[i].getName() == name){
      inventory.push_back(currentRoom.itemList[i]);
      itemId = currentRoom.itemList[i].getId();
      currentRoom.itemList.erase(currentRoom.itemList.begin()+i);
    }
  }
  //<----otestat start------> 
  vector <string> lines;
  ifstream inFile;
  string str,str2;
  //int itemId = 2007;
  int lineToMove = 0;    
  inFile.open(currentFile.c_str());
  while(!inFile.eof()){
    getline(inFile,str,';');
    if(stringToInt(str) == itemId)
      lineToMove = lines.size();
    getline(inFile,str2);
    lines.push_back(str + ";" + str2);
  }
  inFile.close();
  if(remove(currentFile.c_str()) != 0 )
    cerr << "failed to remove file" << currentFile << endl;
  ofstream outFile;
  if(lines[lineToMove].at(lines[lineToMove].size()-1) == '¤')
    lines[lineToMove].erase(lines[lineToMove].end()-1);
  lines.insert(lines.begin(),lines[lineToMove]);
  lines.erase(lines.begin()+lineToMove+1);
  outFile.open(currentFile.c_str());
  for(int i = 0; i < lines.size() -1; ++i){  
    outFile << lines[i] << "\n";
  }
  outFile.close();
  //<----otestat end------>
}

void Player::printInventory(){
  for(unsigned i = 0; i < inventory.size(); ++i){
    inventory[i].printPortable();
  }
}

void Player::walk(string direction){
  if(currentRoom.doorDirection(direction) != 0){
    //<----otestat start------> KOMMER NOG INTE FUNGERA...
    vector <string> lines;
    int roomId = currentRoom.getRoomId();
    ifstream inFile;
    string str,str2;
    int newRoomId = currentRoom.doorDirection(direction), inventorySize = 0;
    int lineToMove = -1;
    inFile.open(currentFile.c_str());
    while(!inFile.eof()){
      getline(inFile,str,';');
      int x = stringToInt(str);
      if(x == 80000+roomId)
	lineToMove = lines.size();
      else if(x >= 2000 && x < 3000 && lineToMove == -1)
	++inventorySize;
      getline(inFile,str2);
      lines.push_back(str + ";" + str2);
    }
    inFile.close();
    //lines.delete(lineToDelete);
    if(remove(currentFile.c_str()) != 0 )
      cerr << "failed to remove file" << currentFile << endl;
    ofstream outFile;
    outFile.open(currentFile.c_str());
    lines.insert(lines.begin()+inventorySize,intToString(80000+newRoomId) + ";¤");
    lines.erase(lines.begin()+lineToMove);
    for(int i = 0; i < lines.size(); ++i){  
      outFile << lines[i] << "\n";
    }
    //<----otestat end------>
    
    
    Room tmpRoom(currentFile, currentRoom.doorDirection(direction));
    currentRoom = tmpRoom;
  }
  /*  if(currentRoom.isWinRoom()){
         youWonThisGame();
      }*/  
}


/*
    Player(const Player &other){
        Item tmpItem;
        for(unsigned i = 0; i < inventory.size(); ++i){
            tmpItem.itemId = other.inventory[i].itemId;
            tmpItem.itemName = other.inventory[i].itemName;
            tmpItem.itemText = other.inventory[i].itemText;
            inventory.push_back(tmpItem);
        }
    }*/


#endif
