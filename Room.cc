#include <vector>
#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
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

class Room{
public:

//Room(bool a, int b, string d, vector<pair<string, int > > c) : is_win_room(a), room_id(b), room_image(d), door_ids(c) {}	

Room(string filepath, int id){
	ifstream file;
	string x,y;
	int b;
	stringstream ss;
	file.open(filepath.c_str());
	if(!file.is_open())
		cerr<< "error: can't open file\n";
	while(!file.eof()){
		getline(file, x, ';');
		b = stringToInt(x);
		if(b == id){
			room_id = b;
			getline(file, x , ';');
			room_name = x;
			getline(file, x , ';');
			room_description = x;
			getline(file, x , ';');
			b = stringToInt(x);
			door_ids.push_back(make_pair("north",stringToInt(x)));
			getline(file, x , ';');
			door_ids.push_back(make_pair("south",stringToInt(x)));
			getline(file, x , ';');
			door_ids.push_back(make_pair("east",stringToInt(x)));
			getline(file, x , ';');
			door_ids.push_back(make_pair("west",stringToInt(x)));
			getline(file, x , ';');
			is_win_room = stringToInt(x);
		}
		else
			getline(file, x);
	}
}

Room& operator =(const Room& other){
this->room_name = other.room_name;
this->room_description = other.room_description;
this->is_win_room = other.is_win_room;
this->room_id = other.room_id;
this->room_image = other.room_image;
for(int i = 0; i < other.door_ids.size(); i++){
	this->door_ids.at(i) = other.door_ids.at(i);
}
return *this;
}

int door_direction(string apa){
for(int i = 0; i < door_ids.size(); i++){
	if(apa == door_ids.at(i).first){
		return door_ids.at(i).second;
	}
}
	return 0;
}

int get_room_id(){ return room_id;}
string get_room_image(){ return room_image; }

bool is_win_room;
string room_name;
string room_description;
int door_id[4];
vector<pair<string, int> > door_ids;
int room_id;
string room_image;	
//vector<Item> item_list;
//Character allied_NPC;

private:
	

	
	
};

int main(){

Room* room1 = new Room("/home/gunbe856/TDDI02/adventure.txt", 1001);
//cout << room1->room_name << endl;
//cout << room1->room_description << endl;
//cout << room1->is_win_room << endl;
Room* room2 = room1;
cout << room2->room_id << endl;
cout << room2->room_name << endl; 
cout << room2->room_description << endl;
cout << room2->is_win_room << endl;
for(int i = 0; i < room2->door_ids.size(); i++)
	cout << room2->door_ids.at(i).first << ": " << room2->door_ids.at(i).second << endl;

return 0;
}
