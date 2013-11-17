#ifndef CHARACTER_H
#define CHARACTER_H
using namespace std;
// viktigt att room initierar Allied som:  Allied npc = Allied("","");

class Character
{
    public:
        virtual ~Character();
	string getText(){return characterText;};
	string getName(){return characterName;};
	void printAllied();
    protected:
        Character();
	Character(string filePath, int roomId);

	//Character(string text_, string name_, int id_);
	string characterText;
        string characterName;
	int characterId;
};

class Allied : public Character{
 public:
    Allied() = default;
    // Allied(string text_, string name_, int id_);
    Allied(string filePath, int roomId);
 private:
};

void Character::printAllied(){
  cout << "characterId = " << characterId << endl;
  cout << "characterName = " << characterName << endl;
  cout << "characterText = " << characterText << endl;
}

Character::Character()
{
    characterText = "";
    characterName = "";
    characterId = 0;
}

Character::~Character()
{
    //dtor
}/*
Character::Character(string text_ = "", string name_ = "", int id_ = 0)
:   characterText(text_),characterName(name_),characterId(id_)
{}*/
/*
Allied::Allied(string text_ = "", string name_ = "",int id_ = 0)
:   Character(text_,name_,id_)
{}*/

Allied::Allied(string filePath,int roomId){
  ifstream file;
  string x,y;
  int b;
  stringstream ss;
  file.open(filePath.c_str());
  if(!file.is_open())
    cerr << "error: can't open file\n";
  while(!file.eof()){
    getline(file,x,';');
    b = stringToInt(x);
    if(b == roomId){
      break;
    }
    getline(file,x,'¤');
  }
  b = 0;
  while(!file.eof()){
    getline(file,x,';');
    b = stringToInt(x);
    if(b >= 3000 && b < 4000){
      break;
    }
  }
  characterId = b;
  getline(file,x,';');
  characterName = x;
  getline(file,y,';');
  characterText = y;
}

Character::Character(string filePath,int roomId){
  characterId = 0;
  characterName = "";
  characterText = "";
}
#endif
