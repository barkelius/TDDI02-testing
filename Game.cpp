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
#include "Game.h"
#include <iostream>

using namespace std;


int game(SDL_Surface *screen, SDL_Event event, string fileName){

  SDL_Surface *background = NULL;
  SDL_Surface *message = NULL;
  SDL_Surface *roomImage = NULL;
  int mx = 0;
  int my = 0;
  int textLength = 36;
  SDL_Color textColor = {255, 255, 255};

  TTF_Font *font = NULL;
  bool quit = false;
  Player spelare(fileName);
  spelare.moveFile();

  background = IMG_Load("background_image_black.png");
  roomImage = IMG_Load(spelare.getRoomImage().c_str());
  if(roomImage == NULL){
    roomImage = IMG_Load(spelare.getDefaultImage().c_str());
  }
  font = TTF_OpenFont("arial.ttf", 28);

  StringInput inputText;
  string text;
  string text3 = "";
  string roomDescriptionText = "Room: " + spelare.getRoomName();
  for(int x = 0; x < 36-roomDescriptionText.size(); ++x){
        roomDescriptionText += " ";
  }
  roomDescriptionText += "Description: " + spelare.getRoomDescription();
  while(quit == false){
    applySurface(0,0, background, screen);
    applySurface(515,0, roomImage, screen);
    printText(roomDescriptionText,10 , 10,textColor,message,font,screen);
    printText(text,10 , (roomDescriptionText.length()/36)*28 + 50,
	      textColor,message,font,screen );

    printText(text3, 10, ((text.length() + roomDescriptionText.length())/36)*28 + 50,textColor,message,font,screen);

    while(SDL_PollEvent(&event)){

      inputText.handleInput(event,textLength);

      if((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_RETURN)){

	string tmp = inputText.getStr();
	int pos = tmp.find(" ");
	string cmd = tmp.substr(0,pos);
	string cmd2 = tmp.substr(pos+1,tmp.length());

	if(cmd == "Talk" || cmd == "talk"){
	  text = spelare.talk();
	}
	else if(cmd == "Use" || cmd == "use"){
	  text = spelare.useItem(cmd2);
	}
	else if(cmd == "Inventory" || cmd == "inventory"){
	  text = spelare.printInventory();
	}
	else if(cmd == "Walk" || cmd == "walk"){
	  roomDescriptionText = spelare.walk(cmd2);
	  text3 = "";
	  roomImage = IMG_Load(spelare.getRoomImage().c_str());
	  if(roomImage == NULL){
	    roomImage = IMG_Load(spelare.getDefaultImage().c_str());
	    }
	  text  = "";
	}
	else if(cmd == "Pickup" || cmd == "pickup"){
	  text = spelare.pickUpItem(cmd2);
	}
	else{
	    text = "Unknown command";
	}
	inputText.clearString();
	SDL_FreeSurface(message);

      }
      if(spelare.isGameOver()){
	text = "";
	roomDescriptionText = "";
	text3 ="";
	background = IMG_Load("gameOver.png");
	roomImage = NULL;
	if(event.type == SDL_QUIT){
	  return 5;
	}
      }

      if(event.type == SDL_QUIT){
	return 5;
      }
      if(event.type == SDL_MOUSEBUTTONDOWN){
	if( event.button.button == SDL_BUTTON_LEFT ){
	  mx = event.button.x;
	  my = event.button.y;
	  if((mx > 610) && (mx < 935) && (my > 632) && (my < 700)){
	    return 4;
	  }
	  else if((mx > 610) && (mx < 935) && (my > 383) && (my < 447)){
	    text3 = spelare.helpFunction();
	  }
      else if((mx > 610) && (mx < 935) && (my > 507) && (my < 571)){
        text = spelare.printInventory();
      }
	}
      }



    }

    inputText.showMessage(screen,10,675);

    SDL_Flip(screen);

  }

  cleanUp(background,message,font);

}

