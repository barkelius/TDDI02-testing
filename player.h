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
        for(unsigned i = 0; i < currentRoom.itemList.size(); ++i){
            if(currentRoom.itemList[i].itemName == name){
                inventory.push_back(currentRoom.itemList[i]);
            }
        }
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
            Room tmpRoom(currentRoom.doorDirection(direction))
            currentRoom = tmpRoom;
        }
        if(currentRoom.isWinRoom()){

        }
    }*/

#endif
