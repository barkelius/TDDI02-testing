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

using namespace std;
int game(SDL_Surface *screen);

int main(int argc, char* argv[]){
  SDL_Surface *screen = NULL;
  game(screen);
}

int game(SDL_Surface *screen){
  const int width = 1024;
  const int height = 720;
  const int bpp = 32;
  SDL_Surface *background = NULL;
  SDL_Surface *message = NULL;
  SDL_Surface *message2 = NULL;
  SDL_Surface *roomImage = NULL;

  SDL_Event event;
  SDL_Color textColor = {255, 255, 255};

  TTF_Font *font = NULL;
  bool quit = false;
  Player spelare("adventure.txt"); 

  SDL_Init(SDL_INIT_EVERYTHING);
  TTF_Init(); 
  SDL_WM_SetCaption("Adventure", NULL);

  screen = SDL_SetVideoMode(width,height,bpp,SDL_SWSURFACE);
  background = IMG_Load("background_image_black.png");
  roomImage = IMG_Load("defaultRoomImage.png");
  font = TTF_OpenFont("lazy.ttf", 28);
 
  StringInput inputText;
  string text; 
  string roomDescriptionText  = "Description: " + spelare.getRoomDescription();

  while(quit == false){
    applySurface(0,0, background, screen);
    applySurface(515,0, roomImage, screen); 
    printText(roomDescriptionText,10 , 10,textColor,message,font,screen);
    printText(text,10 , (roomDescriptionText.length()/36)*20 + 50,
	      textColor,message,font,screen );
    
    while(SDL_PollEvent(&event)){
      
      inputText.handleInput(event);
    
      if((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_RETURN)){

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
	else if(cmd == "Walk" && cmd2 != "Walk"){
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

    inputText.showMessage(screen);
    
    SDL_Flip(screen);
     
    
  }
  cleanUp(background,message,font);

  return 0;
}


