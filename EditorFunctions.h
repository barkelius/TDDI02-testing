#ifndef EditorFunctions_h
#define EditorFunctions_h
#include <string>

bool roomToFile(std::string room, std::string defaultimage, std::string filename);
bool itemToFile(std::string item, std::string filename);
bool characterToFile(std::string character, std::string filename);
bool deleteRoom(std::string room, std::string filename);
bool deleteItem(std::string item, std::string filename);
bool deleteCharacter(std::string character, std::string filename);
void setCurrentRoom(std::string filename);

#endif
