#include "functions.h"
#include "player.h"
#include "character.h"

//#include "item.h"
int main(){
    string filepath;
    Player daniel("adventure.txt");
    daniel.printPlayer();
    //  daniel.printInventory();
    daniel.walk("west");
    cout << "----------------------" << endl;
    daniel.printPlayer();
    // daniel.useItem("nyckel");
    //daniel.printPlayer();
    /*    Allied f1;
    Allied friend1("adventure.txt",1001);
    f1 = friend1;
    f1.printAllied();
    Room danielRoom("adventure.txt", 1003);
    danielRoom.printRoom();*/
return 0;
}
