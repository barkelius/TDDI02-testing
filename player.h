#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <string>
#include "room.h"
#include "item.h"
class Player{
public:
  Player(std::string filePath);
  void printPlayer();
  std::string useItem(std::string name);

  std::string printInventory();
  std::string pickUpItem(std::string name);
  std::string talk();
  std::string walk(std::string direction);
  std::string getRoomImage();
  std::string getRoomDescription();
  std::string getRoomName();
  std::string helpFunction();
  void moveFile();
private:
    Room currentRoom;
    std::vector <Portable> inventory;
    std::string currentFile;
};


#endif
