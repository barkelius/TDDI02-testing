#include "functions.h"
#include "player.h"
#include "character.h"

//#include "item.h"
int main(){
    string filepath;
    Player daniel("adventure.txt");
    //daniel.printPlayer();
    //  daniel.printInventory();
    //daniel.walk("west");
    //cout << "----------------------" << endl;
    //daniel.printPlayer();
    //daniel.talk();
    //cout << "----------------------" << endl;
    daniel.printPlayer();
    cout << "----------------------" << endl;
    daniel.pickUpItem("Flojt");
    cout << "----------------------" << endl;
    daniel.printPlayer();

    return 0;
}
