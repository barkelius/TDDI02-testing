#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
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

struct Item {
  int itemId;
  string itemName,itemText;
};


class Room{
public:
    Room(){
        roomId = 0;
    }
    Room(int inputRoomId)
        :   roomId(inputRoomId)
    {}
    void printRoom(){
        cout << "roomId: " << roomId << endl;
    }

private:
    int roomId;
};

class Player{
public:
  Player(string filePath);
  void printPlayer();
  void useItem(string name);


  //  void printInventory();
  //  void pickUpItem(string name);
  //  void talk();
  //  void walk(string direction);

private:
    Room currentRoom;
    vector <Item> inventory;
    string currentFile;
};


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

Player::Player(string filePath){
  ifstream file;
  string x,y;
  Item item;
  int b;
  stringstream ss;
  file.open(filePath.c_str());
  if(!file.is_open())
    cerr << "error: can't open file\n";
  while(!file.eof()){
    getline(file,x,';');
    b = stringToInt(x);
    if(b >= 80000)
      break;
    //<-- struct test -->
    // detta borde ist vara struct test2
    item.itemId = b;
    getline(file,x,';');
    item.itemName = x;
    getline(file,y,';');
    item.itemText = y;
    //<-- END struct test -->
    
    /* //<-- struct test2 -->
    // detta borde ist vara struct test2
    getline(file,x,';');
    getline(file,y,';');
    Item item = new Item(b,x,y);
    //<-- END struct test2 -->*/
    inventory.push_back(item);
  }
  Room tmpRoom(b-80000);
  currentRoom = tmpRoom;
  file.close();
  currentFile = filePath;
}

void Player::printPlayer(){
  for(unsigned i = 0; i < inventory.size(); ++i){
    cout << "itemId: " << inventory[i].itemId << endl;
    cout << "itemName: " << inventory[i].itemName << endl;
    cout << "itemText: " << inventory[i].itemText << endl;
  }
  currentRoom.printRoom();
}
void Player::useItem(string name){
  for(unsigned i = 0; i < inventory.size(); ++i){
    if(inventory[i].itemName == name){
      cout << "tog bort: " << inventory[i].itemName << endl;
      inventory.erase(inventory.begin()+i);
    }
  }
}

/*
    void Player::talk(){
        if(currentRoom.character.isUsed()){
            cout << currentRoom.character.getText() << endl;
        }
    }
*//*
    void Player::pickUpItem(string name){
        int itemId;
        for(unsigned i = 0; i < currentRoom.itemList.size(); ++i){
            if(currentRoom.itemList[i].itemName == name){
                inventory.push_back(currentRoom.itemList[i]);
		itemId = currentRoom.itemList[i].itemId;
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
    string removeFile = "adventure3.txt";
    if(remove(currentFile.c_str()) != 0 )
      cerr << "failed to remove file" << removeFile << endl;
    ofstream outFile;
    if(lines[lineToMove].at(lines[lineToMove].size()-1) == '¤')
      lines[lineToMove].erase(lines[lineToMove].end()-1);
    lines.insert(lines.begin(),lines[lineToMove]);
    lines.erase(lines.begin()+lineToMove+1);
    outFile.open("adventure3.txt");
    for(int i = 0; i < lines.size(); ++i){  
      outFile << lines[i] << "\n";
    }
    outFile.close();
    //<----otestat end------>


    }
    */
/*
    void Player::printInventory(){
        for(unsigned i = 0; i < inventory.size(); ++i){
            inventory[i].printItem();
        }
    }*/
/*
    void Player::walk(string direction){

        if(currentRoom.doorDirection(direction) != 0){
	    //<----otestat start------> KOMMER NOG INTE FUNGERA...
    vector <string> lines;
    int roomId = currentRoom.getRoomId();
    ifstream inFile;
    string str,str2;
    int newRoomId = 1002, inventorySize = 0;
    int lineToMove = -1;
    inFile.open("adventure2.txt");
    while(!inFile.eof()){
      getline(inFile,str,';');
      int x = stringToInt(str);
      if(x == 80000+currentRoom.getRoomId())
	lineToMove = lines.size();
      else if(x >= 2000 && x < 3000 && lineToMove == -1)
	++inventorySize;
      getline(inFile,str2);
      lines.push_back(str + ";" + str2);
    }
    inFile.close();
    //lines.delete(lineToDelete);
    string removeFile = "adventure3.txt";
    if(remove(removeFile.c_str()) != 0 )
      cerr << "failed to remove file" << removeFile << endl;
    ofstream outFile;
    outFile.open("adventure3.txt");
    lines.insert(lines.begin()+inventorySize,intToString(80000+tmpRoom.getRoomId()) + ";¤");
    lines.erase(lines.begin()+lineToMove+1);
    for(int i = 0; i < lines.size(); ++i){  
      outFile << lines[i] << "\n";
    }
    //<----otestat end------>


            Room tmpRoom(currentRoom.doorDirection(direction))
            currentRoom = tmpRoom;
        }
        if(currentRoom.isWinRoom()){

        }




    }*/

#endif
