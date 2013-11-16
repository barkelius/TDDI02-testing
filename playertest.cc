#include "player.h"
#include "character.h"
#include "item.h"
int main(){
    string filepath;
    Player daniel("adventure.txt");
    daniel.printPlayer();
    daniel.useItem("nyckel");
    daniel.printPlayer();
    Allied friend1("adventure.txt",1001);
    friend1.printAllied();
    Allied friend2("adventure.txt",1003);
    friend2.printAllied();
  
return 0;
}
