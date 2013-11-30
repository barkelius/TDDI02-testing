#ifndef ITEM_H
#define ITEM_H

#include <string>
class Item
{
 protected: 
  std::string Name, itemUsageText;
  int itemId;
 Item(std::string name, std::string text, int id) : Name(name), itemUsageText(text), itemId(id)
  {};
  Item(std::string filepath, int itemId, int roomId);
  Item();
 public:
  virtual int getId() =0;
  virtual std::string getName() =0;
  virtual std::string useItem() =0;
};

class Portable : public Item
{
 public:
  Portable();
  void printPortable();
  Portable(std::string filepath, int itId, int roomId = 0);
  int getId();
  std::string getName();
  std::string useItem();
};


#endif
