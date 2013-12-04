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
  
  int doorDirection(std::string apa);
  bool isWinRoom(){ return winRoom; }
  int getRoomId(){ return room_id;}
  std::string get_room_image(){ return room_image; }
  bool winRoom;
  std::string room_name;
  std::string room_description;
  int door_id[4];
  //vector<pair<string, int> > door_ids;
  int north,west,east,south;
  int room_id;
  std::string room_image;	
  std::vector<Portable> itemList;
  Allied alliedNpc;
  Room& operator =(const Room& other);
 private:  
};
#endif
 

