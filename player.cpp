#include "functions.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
#include "player.h"

using namespace std;


Player::Player(string filePath){
  ifstream file;
  string x,y;
  int b;
  file.open(filePath.c_str());
  if(!file.is_open())
    cerr << "error: can't open file: "<< filePath << "\n" ;
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

string Player::useItem(string name){
  string tmp;
  for(unsigned i = 0; i < inventory.size(); ++i){
    if(inventory[i].getName() == name){
      tmp = "tog bort: " + inventory[i].getName();
      inventory.erase(inventory.begin()+i);
    }
  }
  return tmp;
}


string Player::talk(){
  string tmp;
  if(currentRoom.alliedNpc.getName() != ""){
    tmp = currentRoom.alliedNpc.getName() + ": "
	 + currentRoom.alliedNpc.getText();
  }
  else
    tmp = "No character in this room.";
  return tmp;
}


string Player::pickUpItem(string name){
  int itemId;
  for(unsigned i = 0; i < currentRoom.itemList.size(); ++i){
    if(currentRoom.itemList[i].getName() == name){
      inventory.push_back(currentRoom.itemList[i]);
      itemId = currentRoom.itemList[i].getId();
      currentRoom.itemList.erase(currentRoom.itemList.begin()+i);

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
      return "plockade upp" + name;
    }
  }
  return "Det fanns inte";
    //<----otestat end------>
}

string Player::printInventory(){
  string tmp = "";
  for(unsigned i = 0; i < inventory.size(); ++i){
    tmp +=inventory[i].getName();
    for(int x = 0; x < 36-inventory[i].getName().size(); ++x)
      tmp += " ";
  }
  return tmp;
}

string Player::walk(string direction){
  int newRoomId = currentRoom.doorDirection(direction);
  Room tmpRoom(currentFile, newRoomId);
  string returnString = "Fail";
  if(newRoomId != 0){
    vector <string> lines;
    int roomId = currentRoom.getRoomId();
    ifstream inFile;
    string str,str2;
    int inventorySize = 0;
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
    if(remove(currentFile.c_str()) != 0 )
      cerr << "failed to remove file" << currentFile << endl;
    ofstream outFile;
    outFile.open(currentFile.c_str());
    lines.insert(lines.begin()+inventorySize,intToString(80000+newRoomId) + ";¤");
    lines.erase(lines.begin()+inventorySize+1);
    for(int i = 0; i < lines.size() - 1; ++i){
      outFile << lines[i] << "\n";
    }
    currentRoom = tmpRoom;
    returnString = "Room: " + currentRoom.room_name;
    for(int x = 0; x < 36-returnString.size(); ++x){
        returnString += " ";
    }
    returnString += "Description: " + currentRoom.room_description;
  }
  if(currentRoom.isWinRoom()){
    return "YOU WON!";
  }
  return returnString;
}

string Player::getRoomImage(){
  return currentRoom.room_image;
}
string Player::getRoomDescription(){
  return currentRoom.room_description;
}
string Player::getRoomName(){
  return currentRoom.room_name;
}

string Player::helpFunction(){
  string returnString = "Commands in this room:               ";
  returnString += "'Walk <direction>', 'Inventory'";
  if(currentRoom.alliedNpc.getName() != "")
    returnString += " ,'Talk <text>'";
  if(currentRoom.itemList.size() != 0)
    returnString += " ,'Pickup <itemname>'";
  if(inventory.size() != 0)
     returnString += " ,'Use <itemname>'";
  return returnString;
}
