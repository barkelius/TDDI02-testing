 Room& operator =(const Room& other){
    cerr << "hej" << endl;
    this->room_name = other.room_name;
    this->room_description = other.room_description;
    this->is_win_room = other.is_win_room;
    this->room_id = other.room_id;
    this->room_image = other.room_image;
    cerr << "hej1" << endl;
    /*  for(int i = 0; i < other.door_ids.size(); i++){
      cerr << this->door_ids.at(i).second << endl;
      this->door_ids.at(i).second = other.door_ids.at(i).second;
      }*/
    this->door_ids.clear();
    cerr << "dasdasd" << endl;
    copy(other.door_ids.begin(),other.door_ids.end(),this->door_ids.begin());
    cerr << "hej2" << endl;
    this->alliedNpc = other.alliedNpc;
    cerr << "hej3" << endl;
    this->itemList.clear();
    for(int i = 0; i < other.itemList.size(); ++i)
      this->itemList.push_back(other.itemList.at(i));
    cerr << "hej4" << endl;
    return *this;
  }
