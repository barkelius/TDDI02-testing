#ifndef ROOM_H
#define ROOM_H
#include <string>
#include <vector>
#include "character.h"
#include "item.h"
class Room{
 public:
  void printRoom();
  Room();
  Room(std::string filepath, int id);
  
  int doorDirection(std::string direction);
  bool isWinRoom(){ return winRoom; }
  int getRoomId(){ return roomId;}
  std::string getRoomImage(){ return roomImage; }
  bool winRoom;
  std::string roomName;
  std::string roomDescription;
  int doorId[4];
  int north,west,east,south;
  int roomId;
  std::string roomImage;	
  std::vector<Portable> itemList;
  Allied alliedNpc;
  Room& operator =(const Room& other);
 private:  
};
#endif
 

