#include "SDL/SDL_ttf.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include "StringInput.h"
#include "sdlFunctions.h"
#include "printText.h"
#include "functions.h"
#include "player.h"
#include "character.h"

SDL_Surface *roomImage = NULL;
int game();

int main(int argc, char* argv[]){
  game();
}

int game(){
  bool quit = false;
  Player spelare("adventure.txt");
  bool nameEntered = false;
  Room rumm;
  if(init() == false){
    return 1;
  }

  StringInput inputText;

  if(loadFiles() == false){
    return 1;
  }

  string text;
  string roomDescriptionText = "Description: " + spelare.getRoomDescription();
  roomImage = IMG_Load("defaultRoomImage.png");
  while(quit == false){
    applySurface(0,0, background, screen);
    applySurface(515,0, roomImage, screen);
    printText(roomDescriptionText,10 , 10);
    printText(text,10 , (roomDescriptionText.length()/36)*20 + 50);
    while(SDL_PollEvent(&event)){
      // if(nameEntered == false){
	inputText.handleInput();
	if((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_RETURN)){
	  //nameEntered = true;
	  string tmp = inputText.getStr();
	  int pos = tmp.find(" ");
	  string cmd = tmp.substr(0,pos);
	  string cmd2 = tmp.substr(pos+1,tmp.length());
	  if(cmd == "Talk"){
	    text = spelare.talk();
	  }
	  else if(cmd == "Use"){
	    text = spelare.useItem(cmd2);
	  }
	  else if(cmd == "Inventory"){
	    text = spelare.printInventory();
	  }
	  else if(cmd == "Walk"){
	    roomDescriptionText = spelare.walk(cmd2);
        roomImage = IMG_Load(spelare.getRoomImage().c_str());
	  }
	  else if(cmd == "Pickup"){
        text = spelare.pickUpItem(cmd2);
	  }
      else{
        text = "Unknown command";
      }
	  inputText.clearString();
	  SDL_FreeSurface(message);

	}
	if(event.type == SDL_QUIT){
	  quit = true;
	}
    }

    inputText.showMessage();

    if(SDL_Flip(screen) == -1){
      return 1;
    }
  }
  cleanUp();

  return 0;
}

//makeRoomDescriptionText(string description, string name)
