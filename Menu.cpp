#include "SDL/SDL_ttf.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "sdlFunctions.h"
#include "Game.h"
#include "searchDirectory.h"
#include <string>
#include "printText.h"

using namespace std;

int menu(SDL_Surface *screen,SDL_Event event);
int choiceMenu(SDL_Surface *screen, SDL_Event event);
int editAdventureMenu(SDL_Surface *screen, SDL_Event event);
int playAdventureMenu(SDL_Surface *screen, SDL_Event event);

int main(int argc, char* argv[]){
  SDL_Surface *screen = NULL;
  const int width = 1024;
  const int height = 720;
  const int bpp = 32;
  SDL_Event event;
  SDL_Init(SDL_INIT_EVERYTHING);
  TTF_Init(); 
  SDL_WM_SetCaption("Adventure", NULL);
  screen = SDL_SetVideoMode(width,height,bpp,SDL_SWSURFACE);
  menu(screen,event);
}


int menu(SDL_Surface *screen, SDL_Event event){
  SDL_Surface *menuImage = NULL;
  bool quit = false;
  int mx = 0;
  int my = 0;
  menuImage = IMG_Load("mainMenu.png");

  while(quit == false){
    applySurface(0,0, menuImage, screen);
    while(SDL_PollEvent(&event)){
      if(event.type == SDL_MOUSEBUTTONDOWN){
	if( event.button.button == SDL_BUTTON_LEFT ){
	  mx = event.button.x;
	  my = event.button.y;
	  if((mx > 275) && (mx < 718) && (my > 180) && (my < 273)){
	    playAdventureMenu(screen,event);
	  }
	  else if((mx > 275) && (mx < 718) && (my > 305) && (my < 398)){
	    choiceMenu(screen,event);
	  }
	  else if((mx > 275) && (mx < 718) && (my > 430) && (my < 523)){
	    quit = true;
	  }
	}
      }  
      if(event.type == SDL_QUIT){
	  quit = true;
      }
    }
    SDL_Flip(screen);
    
  }
  return 0;
}

int choiceMenu(SDL_Surface *screen, SDL_Event event){
  SDL_Surface *menuImage = NULL;
  bool quit = false;
  int mx = 0;
  int my = 0;
  menuImage = IMG_Load("editChoiceMenu.png");
    while(quit == false){
    applySurface(0,0, menuImage, screen);
    while(SDL_PollEvent(&event)){
      if(event.type == SDL_MOUSEBUTTONDOWN){
	if( event.button.button == SDL_BUTTON_LEFT ){
	  mx = event.button.x;
	  my = event.button.y;
	  if((mx > 275) && (mx < 718) && (my > 180) && (my < 273)){
	    // game(screen,event);
	  }
	  else if((mx > 275) && (mx < 718) && (my > 305) && (my < 398)){
	    editAdventureMenu(screen,event);
	  }
	  else if((mx > 275) && (mx < 718) && (my > 430) && (my < 523)){
	    return 0;
	  }
	}
      }  
      if(event.type == SDL_QUIT){
	  quit = true;
      }
    }
    SDL_Flip(screen);
    
  }
  return 0;
}

int editAdventureMenu(SDL_Surface *screen, SDL_Event event){
  SDL_Surface *menuImage = NULL;
  SDL_Surface *message = NULL;
  bool quit = false;
  string temp;
  string fileNames;
  int mx = 0;
  int my = 0;
  TTF_Font *font = NULL;
  SDL_Color textColor = {255, 255, 255};
  font = TTF_OpenFont("Blockstepped.ttf", 28);
  menuImage = IMG_Load("editorChooseAdventure.png");
    while(quit == false){
      applySurface(0,0, menuImage, screen);
      fileNames = searchD();
      printText(fileNames,292 , 146,textColor,message,font,screen);
    while(SDL_PollEvent(&event)){
      if(event.type == SDL_MOUSEBUTTONDOWN){
	if( event.button.button == SDL_BUTTON_LEFT ){
	  mx = event.button.x;
	  my = event.button.y;
	  if((mx > 0) && (mx < 1024) && (my > 0) && (my < 720)){
	    cout << "hej";
	    int pos = fileNames.find(" ");
	    temp = fileNames.substr(0, pos);
	    cout << pos <<": " << pos << " :"<< pos;
	    // game(screen,event,temp);
	   
	  }
	}
      }  
      if(event.type == SDL_QUIT){
	  quit = true;
      }
    }
    SDL_Flip(screen);
    
  }
  return 0;
}

int playAdventureMenu(SDL_Surface *screen, SDL_Event event){
  SDL_Surface *menuImage = NULL;
  bool quit = false;
  int mx = 0;
  int my = 0;
  menuImage = IMG_Load("playerChooseAdventure.png");
    while(quit == false){
    applySurface(0,0, menuImage, screen);
    while(SDL_PollEvent(&event)){
      if(event.type == SDL_MOUSEBUTTONDOWN){
	if( event.button.button == SDL_BUTTON_LEFT ){
	  mx = event.button.x;
	  my = event.button.y;
	  if((mx > 275) && (mx < 718) && (my > 180) && (my < 273)){
	    // game(screen,event);
	  }
	}
      }  
      if(event.type == SDL_QUIT){
	  quit = true;
      }
    }
    SDL_Flip(screen);
    
  }
  return 0;
}
