#include "functions.h"
#include "player.h"
#include "character.h"

//#include "item.h"
int main(){
    string filepath;
    Player daniel("adventure.txt");
      
    // cout << daniel.printInventory() << endl;
    daniel.printPlayer();
    cout << "------------------------------------------------" << endl;
    daniel.walk("west");
    // daniel.printPlayer();
    cout << "------------------------------------------------" << endl;
    daniel.walk("east");
    //daniel.printPlayer();
    cout << "------------------------------------------------" << endl;
    daniel.walk("east");
    //daniel.printPlayer();
    cout << "------------------------------------------------" << endl;
    daniel.walk("west");
    //daniel.printPlayer();
    /*
    Room rum1("adventure.txt",1001);
    rum1.printRoom();
    cout << "------------------------------------------------" << endl;
    Room rum2("adventure.txt",1002);
    rum2.printRoom();
    cout << "------------------------------------------------" << endl;
    Room rum3("adventure.txt",1003);
    rum2 = rum1;
    rum2.printRoom();
    cout << "-----------------------------------------------" << endl;
    rum3.printRoom();
    rum3 = rum2;
    cout << "-----------------------------------------------" << endl;
    rum3.printRoom();*/
    return 0;
}
