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
#include "functions.h"
using namespace std;

/*int stringToInt(string str){
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
}*/

string removeIdFromString(string str);
//Returnerar true om allt gick bra, false om inmatningen fr�n anv�ndaren var felaktig.
bool roomToFile(string room, string defaultimage, string filename);
bool itemToFile(string item, string filename);
bool characterToFile(string character, string filename);
bool deleteRoom(string room, string filename);
bool deleteItem(string item, string filename);
bool deleteCharacter(string character, string filename);
void setCurrentRoom(string filename);


/*int main(){
  string AdventureName;
  string penis;
  bool r;
  cout << "nytt?????";
  cin >> r;
  if(r == true){
    cout << "Name your adventure, using template \"Name.txt\" : ";
    cin >> AdventureName;
    ofstream outputFile;
    outputFile.open(AdventureName.c_str());				    	//Fil skapad
    if(!outputFile.is_open())
      cerr << "error: can't open file\n";
    outputFile.close();
  }
  else
    cin >> AdventureName;
	
  cin.sync();
  getline(cin,penis);
  if(roomToFile(penis, "hej.jpg", AdventureName))
    cerr << "Det gick bra*!" << endl;
  else
  cerr << "Det gick ju inte bra" << endl;
  //setCurrentRoom(AdventureName);
  //deleteRoom(penis, AdventureName);
  setCurrentRoom(AdventureName);
  //if sats för room 
  /*string apa = MakeRoom();
    outputFile << apa;
    apa = MakeItem();
    outputFile << apa;
    apa = MakeCharacter();
    outputFile << apa;
  
  //if satser för char och item
	
}*/

bool itemToFile(string item, string filename){
  cout << item << endl;
  ifstream file;
  int check = 0;
  string in;
  string tmp;
  stringstream ss;
  ofstream outputFile;
  vector<string> temp;
  if(item.size() < 8)                                         //minimum l�ngd f�r inmatning
    return false;
  ss << item;
  getline(ss,in,';');
  if(stringToInt(in) < 1000 || stringToInt(in) > 1999){       //Kollar om inmatning b�rjar med rum id
    if(stringToInt(in) != 0)
      return false;
  }
  getline(ss,in,';');
  if(stringToInt(in) < 2000 || stringToInt(in) > 2999){       //Kollar om n�sta id �r item id
    return false;
  }
  ss.sync();
  check = 0;
  for(int i = 0; i < item.size(); i++){                      //Kollar om antalet semikolon �r korrekt
    if(item.at(i) == ';')
      check++;
    if(item.at(i) == '�'){                                   //Solar ej till�tna
      return false;
    }
  }
 cout << item << endl;
  if(check != 4){                   
    return false;
  }
  file.open(("Adventures//" + filename).c_str());
  if(!file.is_open())
    cerr<< "error: can't open file\n";
  while(!file.eof()){                                     //L�ser in alla rader fr�n filen till vector 
    getline(file, in);
    temp.push_back(in);
  }
  cout << "swag: " << item << endl;
  file.close();
  vector<string>::iterator it = temp.begin();

  while(it != temp.end()-1){                             //Kolla om id �r upptaget
    if((*it).size() > 3){
      if(item.at(5) == (*it).at(0) && 
	 item.at(6) == (*it).at(1) && 
	 item.at(7) == (*it).at(2) && 
	 item.at(8) == (*it).at(3)){
	return false;
      }
    }    
    ++it;
  }
  cout << "swag2: " << item << endl;
  ss.sync();
  if(remove(("Adventures//" + filename).c_str()) != 0 )                         //tar bort filen
    cerr << "failed to remove file";
  if(item.at(0) == '0'){ //kollar om item ska hamna hos player inventory eller i ett rum
    cerr << "swagettw" << endl;
    tmp = removeIdFromString(item);
    cerr << "swagetti yolonesis" << tmp << endl;
    temp.insert(temp.begin(), tmp);
  }
  else{
     cerr << item << endl;
    it = temp.begin();
    while(it != temp.end()){
      if(item.at(0) == (*it).at(0) && 
	 item.at(1) == (*it).at(1) && 
	 item.at(2) == (*it).at(2) && 
	 item.at(3) == (*it).at(3)){              //letar igenom till r�tt rum hittas
	tmp = removeIdFromString(item);	
	cerr << tmp << endl;
	if((*it).at((*it).size() -1) == '�'){           //stegar tills slutet av rummet hittas och s�tter in npc sist i rummet
	  (*it).erase((*it).size()-1);
	  tmp = tmp + "�";
	}	
	temp.insert(it, tmp);
	swap(*it,*(it+1));
	break;
      }
      it++;
    }
  }
  outputFile.open("Adventures//" + filename);
  if(!outputFile.is_open())
    cout << "tchj���na";
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

string removeIdFromString(string str){
  int x = 0;
  while(str.at(x) != ';'){
    ++x;
  }
  str.erase(0,x+1);
  return str;
}



bool characterToFile(string character, string filename){
  ifstream file;
  string in;
  string tmp;
  int check = 0;
  stringstream ss;
  ofstream outputFile;
  vector<string> temp;
  if(character.size() < 8)                                   //kollar ett minimum p� inmatningens storlek
    return false;
  ss << character;
  getline(ss,in,';');
  if(stringToInt(in) < 1000 || stringToInt(in) > 1999){      //kollar om det �r ett rum-id f�rst p� inmatniningen
    return false;
  }
  getline(ss,in,';');
  if(stringToInt(in) < 3000 || stringToInt(in) > 3999){      //kollar om ett npc-id kommer in p� andra platsen 
    return false;
  }
  ss.sync();
  for(int i = 0; i < character.size(); i++){                 //stegar upp en int f�r varje semikolon som finns i inmatningen
    if(character.at(i) == ';')
      check++;
    if(character.at(i) == '�'){                             //Solar �r ej accepterade i inmatningen
      return false;
    }
  }
  if(check != 4){                                            // kollar att antalet semikolon �r korrekt
    return false;
  }
  cout<<filename<< endl;
  file.open(("Adventures//" + filename).c_str());
  if(!file.is_open())
    cerr<< "error: can't open file\n";
  while(!file.eof()){                                       //L�ser in rad f�r rad fr�n filen till en vector
    getline(file, in);
    temp.push_back(in);
  }
  file.close();
  vector<string>::iterator it = temp.begin();
  while(it != temp.end()-1){
    if(character.at(5) == (*it).at(0) && 
       character.at(6) == (*it).at(1) && 
       character.at(7) == (*it).at(2) && 
       character.at(8) == (*it).at(3)){                    //om npc-id:et �r upptaget redan
      return false;
    }
    ++it;
  }
  it = temp.begin();
  while(it != temp.end()){
    if(character.at(0) == (*it).at(0) && 
       character.at(1) == (*it).at(1) && 
       character.at(2) == (*it).at(2) && 
       character.at(3) == (*it).at(3)){                  //letar efter r�tt rum
      while((*it).at((*it).size() -1) != '�'){           //stegar till slutet av rummet
	++it;
      }
      if((*it).at(0) == '3')                            //kollar om rummet redan har en npc
	return false;
      else
	break;
    }
    ++it;
  }
  if(remove(("Adventures//" + filename).c_str()) != 0 )
    cerr << "failed to remove file";

  it = temp.begin();
  while(it != temp.end()){
    if(character.at(0) == (*it).at(0) && 
       character.at(1) == (*it).at(1) && 
       character.at(2) == (*it).at(2) && 
       character.at(3) == (*it).at(3)){                //Letar efter r�tt rum
      /* ss << character;
      getline(ss,tmp,';');
      getline(ss, tmp);*/
      tmp = removeIdFromString(character);
      tmp = tmp + "�";
      while((*it).at((*it).size() -1) != '�'){         //stegar till slutet av rummet
	it++;
      }
      (*it).erase((*it).size()-1);	             //tar bort solen fr�n f�reg�ende rad
      temp.insert(it, tmp);
      swap(*it,*(it+1));                            //s�tter den nya npc p� r�tt rad
      break;
    }
    it++;
  }
  outputFile.open(("Adventures//" + filename).c_str());
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
  cout << "fil: " << filename << endl;
  if(room.size() < 18)                               //kollar ett minimum f�r inmatningsstorleken
    return false;
  for(int i = 0; i < room.size(); i++){              // stegar varje semikolon
    if(room.at(i) == ';')
      check++;
    if(room.at(i) == '�'){                           // inga solar
      return false;
    }
  }
  if(check != 9){                                  // hur m�nga semikolon fanns
    return false;
  }
  ss << room;
  getline(ss,in,';');
  if(stringToInt(in) < 1000 || stringToInt(in) > 1999){    // kollar om det f�rsta �r ett rum-id
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
  for(int i = 0; i < 4; i++){                            //kollar om all l�nkning g�rs r�tt
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
  if(stringToInt(in) != 0){                                //kollar om det sista p� raden �r ett vinstrum
    if(stringToInt(in) != 1)
      return false;
  }
  tmp += in + ";";
  room = tmp;
  file.open(("Adventures//" + filename).c_str());
  if(!file.is_open())
    cerr<< "error: can't open file\n";
  while(!file.eof()){                                     //fil till vector
    getline(file, in);
    temp.push_back(in);
  }
  temp.push_back(room);                                          // rum sist i vector
  outputFile.open(("Adventures//" + filename).c_str());
  temp.erase(temp.begin()+temp.size()-2);                       //tar bort blank rad
  for(int i = 0; i < temp.size(); i++){                         //Skriver allt till fil och slutar med en sol bakom det nya rummet
    outputFile << temp.at(i);
    if(i == temp.size() - 1){
      outputFile << "�";
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
  if(room.size() != 4)                                   //minimum f�r inmatning
    return false;
  file.open(("Adventures//" + filename).c_str());
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
  if(remove(("Adventures//" + filename).c_str()) != 0 )
    cerr << "failed to remove file";

  it = temp.begin();
  while(it != temp.end()){
    id.clear();
    for(int y = 0; y < 4; y++){                              //tar de 4 f�rsta siffrorna fr�n varje rad
      id = id + (*it).at(y);
    }
    if(room == id){                                         //letar efter r�tt rum
      while((*it).at((*it).size() -1) != '�'){              // stegar och tarbort varje rad tills slutet av rummet
	temp.erase(it);
      }
      temp.erase(it);                                       // tar bort den sista raden av rumet
      break;
    }
    ++it;
  }
  outputFile.open(("Adventures//" + filename).c_str());
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
  file.open(("Adventures//" + filename).c_str());
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
  if(remove(("Adventures//" + filename).c_str()) != 0 )                       //raderar fil f�r att g�ra det m�jligt f�r omstrukturering
    cerr << "failed to remove file";

  it = temp.begin();
  while(it != temp.end()){
    id.clear();
    for(int y = 0; y < 4; y++){                                 // tar de 4 det f�rsta id fr�n varje rad
      id = id + (*it).at(y);
    }
    if(character == id){                                       //letar efter r�tt  npc och tar bort och s�tter sol p� raden innan
      temp.erase(it);
      *(it-1) = *(it-1) + "�";
      break;
    }
    ++it;
  }
  outputFile.open(("Adventures//" + filename).c_str());
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
  file.open(("Adventures//" + filename).c_str());
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
  if(remove(("Adventures//" + filename).c_str()) != 0 )                 // raderar fil f�r att g�ra det m�jligt f�r omstrukturering
    cerr << "failed to remove file";

  it = temp.begin();
  while(it != temp.end()){
    id.clear();
    for(int y = 0; y < 4; y++){                      // gunnar kommer i byxan meddans denna tar id fr�n varje rad till en str�ng
      id = id + (*it).at(y);
    }
    if(item == id){
      if((*it).at((*it).size() -1) != '�'){          //om raden inte slutar med en sol s� tar vi bara bort raden
	temp.erase(it);
      }
      else{                                          //annars s� tar vi bort raden och l�gger till sol p� raden �ver
	temp.erase(it);
	*(it-1) = *(it-1) + "�";
      }
      break;
    }
    ++it;
  }
  outputFile.open(("Adventures//" + filename).c_str());
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
  file.open(("Adventures//" + filename).c_str());
  if(!file.is_open())
    cerr<< "error: can't open file\n";
  while(!file.eof()){                                       //fil till vector
    getline(file, in);
    temp.push_back(in);
  }
  vector<string>::iterator it;
  for(it = temp.begin(); it != temp.end(); it++){          //stegar till f�rsta rum �r hittat
    if((*it).at(0) == '1'){
      ss << *it;
      getline(ss,in,';');
      eight += in;
      eight += ";�";
      temp.insert(it, eight);                             //stoppar in det �versta rummet som current room
      break;
    }
    else if((*it).at(0) == '8'){                        // kollar om det finns ett current room
      if((*it).at(1) == (*(it+1)).at(0) && 
	 (*it).at(2) == (*(it+1)).at(1) &&
	 (*it).at(3) == (*(it+1)).at(2) &&
	 (*it).at(4) == (*(it+1)).at(3))                  // om current room �r samma som �versta rummet s� avsluta
	break;
      else{                                              // s�tter det �versta rummet som current room
	(*it).at(1) = (*(it+1)).at(0);  
	(*it).at(2) = (*(it+1)).at(1); 
	(*it).at(3) = (*(it+1)).at(2); 
	(*it).at(4) = (*(it+1)).at(3);
      }
      break;
    }
  }
  outputFile.open(("Adventures//" + filename).c_str());
  for(int i = 0; i < temp.size(); i++){                      // vector till fil
    outputFile << temp.at(i);
    outputFile << "\n";
  }
  outputFile.close();
  file.close();
}
