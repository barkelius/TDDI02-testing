#ifndef EditorFunctions_h
#define EditorFunctions_h
#include <string>
#include <vector>

bool roomToFile(std::string room, std::string defaultimage, std::string filename);
bool itemToFile(std::string item, std::string filename);
bool characterToFile(std::string character, std::string filename);
bool deleteRoom(std::string room, std::string filename);
bool deleteItem(std::string item, std::string filename);
bool deleteCharacter(std::string character, std::string filename);
bool setCurrentRoom(std::string filename);
void deleteBlankLines(std::vector<std::string>& v);
std::string removeIdFromString(std::string str);

#endif
