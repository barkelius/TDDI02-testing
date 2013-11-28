
Player::Player(string filePath){
  ifstream file;
  string x,y;
  int b;
  file.open(filePath.c_str());
  if(!file.is_open())
    cerr << "error: can't open file\n";
  while(!file.eof()){
    getline(file,x,';');
    b = stringToInt(x);
    if(b >= 80000)
      break;
    getline(file,x,';');
    getline(file,y,';');
    Portable item = Portable(filePath,b);
    inventory.push_back(item);
  }
  Room tmpRoom(filePath,b-80000);
  currentRoom = tmpRoom;
  file.close();
  currentFile = filePath;
}

void Player::printPlayer(){
  /*  for(unsigned i = 0; i < inventory.size(); ++i){
    cout << "itemId: " << inventory[i].getId() << endl;
    cout << "itemName: " << inventory[i].getName() << endl;
    cout << "itemText: " << inventory[i].useItem() << endl;
    }*/
  currentRoom.printRoom();
  }

string Player::useItem(string name){
  string tmp;
  for(unsigned i = 0; i < inventory.size(); ++i){
    if(inventory[i].getName() == name){
      tmp = "tog bort: " + inventory[i].getName();
      inventory.erase(inventory.begin()+i);
    }
  }
  return tmp;
}

string Player::talk(){
  string tmp;
  if(currentRoom.alliedNpc.getName() != ""){
    tmp = currentRoom.alliedNpc.getName() + ": " 
	 + currentRoom.alliedNpc.getText();
  }
  else
    tmp = "No character in this room.";
  return tmp;
}
