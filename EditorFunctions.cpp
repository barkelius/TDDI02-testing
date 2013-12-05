//#include "player.h"
//#include "room.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>
#include <string>
#include <vector>

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

//Returnerar true om allt gick bra, false om inmatningen från användaren var felaktig.
bool roomToFile(string room, string defaultimage, string filename);
bool itemToFile(string item, string filename);
bool characterToFile(string character, string filename);
bool deleteRoom(string room, string filename);
bool deleteItem(string item, string filename);
bool deleteCharacter(string character, string filename);
void setCurrentRoom(string filename);


bool itemToFile(string item, string filename){
  ifstream file;
  int check = 0;
  string in;
  string tmp;
  stringstream ss;
  ofstream outputFile;
  vector<string> temp;
  if(item.size() < 8)                                         //minimum längd för inmatning
    return false;
  ss << item;
  getline(ss,in,';');
  if(stringToInt(in) < 1000 || stringToInt(in) > 1999){       //Kollar om inmatning börjar med rum id
    if(stringToInt(in) != 0)
      return false;
  }
  getline(ss,in,';');
  if(stringToInt(in) < 2000 || stringToInt(in) > 2999){       //Kollar om nästa id är item id
    return false;
  }
  ss.sync();
  check = 0;
  for(int i = 0; i < item.size(); i++){                      //Kollar om antalet semikolon är korrekt
    if(item.at(i) == ';')
      check++;
    if(item.at(i) == '¤'){                                   //Solar ej tillåtna
      return false;
    }
  }
  if(check != 4){                   
    return false;
  }
  file.open(filename.c_str());
  if(!file.is_open())
    cerr<< "error: can't open file\n";
  while(!file.eof()){                                     //Läser in alla rader från filen till vector 
    getline(file, in);
    temp.push_back(in);
  }
  file.close();
  vector<string>::iterator it = temp.begin();
  while(it != temp.end()-1){                             //Kolla om id är upptaget
    if(item.at(5) == (*it).at(0) && 
       item.at(6) == (*it).at(1) && 
       item.at(7) == (*it).at(2) && 
       item.at(8) == (*it).at(3)){
      return false;
    }
    ++it;
  }

  if(remove(filename.c_str()) != 0 )                         //tar bort filen
    cerr << "failed to remove file";
  if(item.at(0) == '0'){                                    //kollar om item ska hamna hos player inventory eller i ett rum
    ss << item;
    getline(ss,tmp,';');
    ss >> tmp;
    temp.insert(temp.begin(), tmp);
  }
  else{
    it = temp.begin();
    while(it != temp.end()){
      if(item.at(0) == (*it).at(0) && 
	 item.at(1) == (*it).at(1) && 
	 item.at(2) == (*it).at(2) && 
	 item.at(3) == (*it).at(3)){                      //letar igenom till rätt rum hittas
	ss << item;
	getline(ss,tmp,';');
	getline(ss, tmp);
	if((*it).at((*it).size() -1) == '¤'){           //stegar tills slutet av rummet hittas och sätter in npc sist i rummet
	  (*it).erase((*it).size()-1);
	  tmp = tmp + "¤";
	}	
	temp.insert(it, tmp);
	swap(*it,*(it+1));
	break;
      }
      it++;
    }
  }
  outputFile.open(filename.c_str());
  for(int i = 0; i < temp.size(); i++){                //skriver allt till filen med radbrytning
    outputFile << temp.at(i);
    if(i != temp.size() - 1){
      outputFile << "\n";	
    }
  }
  outputFile.close();
  file.close();
  return true;

}



bool characterToFile(string character, string filename){
  ifstream file;
  string in;
  string tmp;
  int check = 0;
  stringstream ss;
  ofstream outputFile;
  vector<string> temp;
  if(character.size() < 8)                                   //kollar ett minimum på inmatningens storlek
    return false;
  ss << character;
  getline(ss,in,';');
  if(stringToInt(in) < 1000 || stringToInt(in) > 1999){      //kollar om det är ett rum-id först på inmatniningen
    return false;
  }
  getline(ss,in,';');
  if(stringToInt(in) < 3000 || stringToInt(in) > 3999){      //kollar om ett npc-id kommer in på andra platsen 
    return false;
  }
  ss.sync();
  for(int i = 0; i < character.size(); i++){                 //stegar upp en int för varje semikolon som finns i inmatningen
    if(character.at(i) == ';')
      check++;
    if(character.at(i) == '¤'){                             //Solar är ej accepterade i inmatningen
      return false;
    }
  }
  if(check != 4){                                            // kollar att antalet semikolon är korrekt
    return false;
  }
  file.open(filename.c_str());
  if(!file.is_open())
    cerr<< "error: can't open file\n";
  while(!file.eof()){                                       //Läser in rad för rad från filen till en vector
    getline(file, in);
    temp.push_back(in);
  }
  file.close();
  vector<string>::iterator it = temp.begin();
  while(it != temp.end()-1){
    if(character.at(5) == (*it).at(0) && 
       character.at(6) == (*it).at(1) && 
       character.at(7) == (*it).at(2) && 
       character.at(8) == (*it).at(3)){                    //om npc-id:et är upptaget redan
      return false;
    }
    ++it;
  }
  it = temp.begin();
  while(it != temp.end()){
    if(character.at(0) == (*it).at(0) && 
       character.at(1) == (*it).at(1) && 
       character.at(2) == (*it).at(2) && 
       character.at(3) == (*it).at(3)){                  //letar efter rätt rum
      while((*it).at((*it).size() -1) != '¤'){           //stegar till slutet av rummet
	++it;
      }
      if((*it).at(0) == '3')                            //kollar om rummet redan har en npc
	return false;
      else
	break;
    }
    ++it;
  }
  if(remove(filename.c_str()) != 0 )
    cerr << "failed to remove file";

  it = temp.begin();
  while(it != temp.end()){
    if(character.at(0) == (*it).at(0) && 
       character.at(1) == (*it).at(1) && 
       character.at(2) == (*it).at(2) && 
       character.at(3) == (*it).at(3)){                //Letar efter rätt rum
      ss << character;
      getline(ss,tmp,';');
      getline(ss, tmp);
      tmp = tmp + "¤";
      while((*it).at((*it).size() -1) != '¤'){         //stegar till slutet av rummet
	it++;
      }
      (*it).erase((*it).size()-1);	             //tar bort solen från föregående rad
      temp.insert(it, tmp);
      swap(*it,*(it+1));                            //sätter den nya npc på rätt rad
      break;
    }
    it++;
  }
  outputFile.open(filename.c_str());
  for(int i = 0; i < temp.size(); i++){             //Skriver allt till filen
    outputFile << temp.at(i);
    if(i != temp.size() - 1){
      outputFile << "\n";
    }
  }
  outputFile.close();
  file.close();
  return true;
}

bool roomToFile(string room, string defaultimage, string filename){
  ifstream file;
  string in;
  string tmp;
  stringstream ss;
  int check = 0;
  ofstream outputFile;
  vector<string> temp;
  SDL_Surface *image = NULL;
  if(room.size() < 18)                               //kollar ett minimum för inmatningsstorleken
    return false;
  for(int i = 0; i < room.size(); i++){              // stegar varje semikolon
    if(room.at(i) == ';')
      check++;
    if(room.at(i) == '¤'){                           // inga solar
      return false;
    }
  }
  if(check != 9){                                  // hur många semikolon fanns
    return false;
  }
  ss << room;
  getline(ss,in,';');
  if(stringToInt(in) < 1000 || stringToInt(in) > 1999){    // kollar om det första är ett rum-id
    return false;
  }
  tmp = in + ";";
  getline(ss,in,';');
  tmp += in + ";";
  getline(ss,in,';');
  tmp += in + ";";
  getline(ss,in,';');
  image = IMG_Load(in.c_str());
  if(image == NULL)
    tmp += defaultimage + ";";
  else
    tmp += in + ";";
  for(int i = 0; i < 4; i++){                            //kollar om all länkning görs rätt
    getline(ss,in,';');
    if(!isdigit(in[0]))
      return false;
    if(stringToInt(in) < 1000 || stringToInt(in) > 1999){ 
      if(stringToInt(in) != 0)
	return false;
    }
    tmp += in + ";";
  }
  getline(ss,in,';');
  if(stringToInt(in) != 0){                                //kollar om det sista på raden är ett vinstrum
    if(stringToInt(in) != 1)
      return false;
  }
  tmp += in + ";";
  room = tmp;
  file.open(filename.c_str());
  if(!file.is_open())
    cerr<< "error: can't open file\n";
  while(!file.eof()){                                     //fil till vector
    getline(file, in);
    temp.push_back(in);
  }
  temp.push_back(room);                                          // rum sist i vector
  outputFile.open(filename.c_str());
  temp.erase(temp.begin()+temp.size()-2);                       //tar bort blank rad
  for(int i = 0; i < temp.size(); i++){                         //Skriver allt till fil och slutar med en sol bakom det nya rummet
    outputFile << temp.at(i);
    if(i == temp.size() - 1){
      outputFile << "¤";
    }
    outputFile << "\n";
  }
  outputFile.close();
  file.close();
  return true;
}


bool deleteRoom(string room, string filename){
  ifstream file;
  string in;
  string id;
  ofstream outputFile;
  vector<string> temp;
  if(room.size() != 4)                                   //minimum för inmatning
    return false;
  file.open(filename.c_str());
  if(!file.is_open())
    cerr<< "error: can't open file\n";
  while(!file.eof()){                                  // fil till vector
    getline(file, in);
    temp.push_back(in);
  }
  file.close();
  vector<string>::iterator it;
  for(it = temp.begin(); it != temp.end(); it++){             //kollar om rummet finns i filen
    if((*it).at(0) == room.at(0) && 
       (*it).at(1) == room.at(1) &&
       (*it).at(2) == room.at(2) &&
       (*it).at(3) == room.at(3))
      break;
    if(it == temp.end() - 1)
      return false;
  }
  if(remove(filename.c_str()) != 0 )
    cerr << "failed to remove file";

  it = temp.begin();
  while(it != temp.end()){
    id.clear();
    for(int y = 0; y < 4; y++){                              //tar de 4 första siffrorna från varje rad
      id = id + (*it).at(y);
    }
    if(room == id){                                         //letar efter rätt rum
      while((*it).at((*it).size() -1) != '¤'){              // stegar och tarbort varje rad tills slutet av rummet
	temp.erase(it);
      }
      temp.erase(it);                                       // tar bort den sista raden av rumet
      break;
    }
    ++it;
  }
  outputFile.open(filename.c_str());
  for(int i = 0; i < temp.size(); i++){                    //vector till fil
    outputFile << temp.at(i);
    outputFile << "\n";
  }
  outputFile.close();
  file.close();	
  return true;
}

bool deleteCharacter(string character, string filename){
  ifstream file;
  string in;
  string id;
  ofstream outputFile;
  vector<string> temp;
  if(character.size() != 4)                                 //kollar inmatningstorlek
    return false;
  file.open(filename.c_str());
  if(!file.is_open())
    cerr<< "error: can't open file\n";
  while(!file.eof()){                                       //fil till vector
    getline(file, in);
    temp.push_back(in);
  }
  file.close();
  vector<string>::iterator it;
  for(it = temp.begin(); it != temp.end(); it++){
    if((*it).at(0) == character.at(0) && 
       (*it).at(1) == character.at(1) &&
       (*it).at(2) == character.at(2) &&
       (*it).at(3) == character.at(3))                       //kollar om npc finns
      break;
    if(it == temp.end() - 1)
      return false;
  }
  if(remove(filename.c_str()) != 0 )                       //raderar fil för att göra det möjligt för omstrukturering
    cerr << "failed to remove file";

  it = temp.begin();
  while(it != temp.end()){
    id.clear();
    for(int y = 0; y < 4; y++){                                 // tar de 4 det första id från varje rad
      id = id + (*it).at(y);
    }
    if(character == id){                                       //letar efter rätt  npc och tar bort och sätter sol på raden innan
      temp.erase(it);
      *(it-1) = *(it-1) + "¤";
      break;
    }
    ++it;
  }
  outputFile.open(filename.c_str());
  for(int i = 0; i < temp.size(); i++){                       // vector till fil
    outputFile << temp.at(i);
    outputFile << "\n";
  }
  outputFile.close();
  file.close();
  return true;

}

bool deleteItem(string item, string filename){
  ifstream file;
  string in;
  string id;
  ofstream outputFile;
  vector<string> temp;
  if(item.size() != 4)                                  //imantingstorlek ok?
    return false;
  file.open(filename.c_str());
  if(!file.is_open())
    cerr<< "error: can't open file\n";
  while(!file.eof()){                                  // fil till vector
    getline(file, in);
    temp.push_back(in);
  }
  file.close();
  vector<string>::iterator it;
  for(it = temp.begin(); it != temp.end(); it++){
    if((*it).at(0) == item.at(0) && 
       (*it).at(1) == item.at(1) &&
       (*it).at(2) == item.at(2) &&
       (*it).at(3) == item.at(3))                     // kollar om item finns
      break;
    if(it == temp.end() - 1)
      return false;
  }
  if(remove(filename.c_str()) != 0 )                 // raderar fil för att göra det möjligt för omstrukturering
    cerr << "failed to remove file";

  it = temp.begin();
  while(it != temp.end()){
    id.clear();
    for(int y = 0; y < 4; y++){                      // gunnar kommer i byxan meddans denna tar id från varje rad till en sträng
      id = id + (*it).at(y);
    }
    if(item == id){
      if((*it).at((*it).size() -1) != '¤'){          //om raden inte slutar med en sol så tar vi bara bort raden
	temp.erase(it);
      }
      else{                                          //annars så tar vi bort raden och lägger till sol på raden över
	temp.erase(it);
	*(it-1) = *(it-1) + "¤";
      }
      break;
    }
    ++it;
  }
  outputFile.open(filename.c_str());
  for(int i = 0; i < temp.size(); i++){              //vector till fil
    outputFile << temp.at(i);
    outputFile << "\n";
  }
  outputFile.close();
  file.close();
  return true;

}

void setCurrentRoom(string filename){
  ifstream file;
  vector<string> temp;
  ofstream outputFile;
  string eight = "8";
  stringstream ss;
  string in;
  file.open(filename.c_str());
  if(!file.is_open())
    cerr<< "error: can't open file\n";
  while(!file.eof()){                                       //fil till vector
    getline(file, in);
    temp.push_back(in);
  }
  vector<string>::iterator it;
  for(it = temp.begin(); it != temp.end(); it++){          //stegar till första rum är hittat
    if((*it).at(0) == '1'){
      ss << *it;
      getline(ss,in,';');
      eight += in;
      eight += ";¤";
      temp.insert(it, eight);                             //stoppar in det översta rummet som current room
      break;
    }
    else if((*it).at(0) == '8'){                        // kollar om det finns ett current room
      if((*it).at(1) == (*(it+1)).at(0) && 
	 (*it).at(2) == (*(it+1)).at(1) &&
	 (*it).at(3) == (*(it+1)).at(2) &&
	 (*it).at(4) == (*(it+1)).at(3))                  // om current room är samma som översta rummet så avsluta
	break;
      else{                                              // sätter det översta rummet som current room
	(*it).at(1) = (*(it+1)).at(0);  
	(*it).at(2) = (*(it+1)).at(1); 
	(*it).at(3) = (*(it+1)).at(2); 
	(*it).at(4) = (*(it+1)).at(3);
      }
      break;
    }
  }
  outputFile.open(filename.c_str());
  for(int i = 0; i < temp.size(); i++){                      // vector till fil
    outputFile << temp.at(i);
    outputFile << "\n";
  }
  outputFile.close();
  file.close();
}
