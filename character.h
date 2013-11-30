#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
// viktigt att room initierar Allied som:  Allied npc = Allied("","");

class Character
{
    public:
        virtual ~Character();
	std::string getText(){return characterText;};
	std::string getName(){return characterName;};
	void printAllied();
    protected:
        Character();
	Character(std::string filePath, int roomId);

	//Character(string text_, string name_, int id_);
	std::string characterText;
        std::string characterName;
	int characterId;
};

class Allied : public Character{
 public:
    Allied() = default;
    // Allied(string text_, string name_, int id_);
    Allied(std::string filePath, int roomId);
 private:
};

#endif
