#include "SDL/SDL_ttf.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "sdlFunctions.h"
#include "Game.h"
#include "searchDirectory.h"
#include <string>
#include "printText.h"
#include <iostream>
#include "Editor.h"
#include "StringInput.h"
#include <fstream>

using namespace std;

int menu(SDL_Surface *screen,SDL_Event event);
int playChoiceMenu(SDL_Surface *screen, SDL_Event event);
int editChoiceMenu(SDL_Surface *screen, SDL_Event event);
int editAdventureMenu(SDL_Surface *screen, SDL_Event event);
int playAdventureMenu(SDL_Surface *screen, SDL_Event event, string filePath);
int editNewAdventureFile(SDL_Surface *screen, SDL_Event event);
int editNewAdventureImage(SDL_Surface *screen, SDL_Event event, string text);

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
	    int returnStatus = playChoiceMenu(screen,event);
	    if(returnStatus == 5)
	      return 0;
	  }
	  else if((mx > 275) && (mx < 718) && (my > 305) && (my < 398)){
	    int returnStatus = editChoiceMenu(screen,event);
	    if(returnStatus == 5)
	      return 0;
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

int editChoiceMenu(SDL_Surface *screen, SDL_Event event){
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
	    int returnStatus = editNewAdventureFile(screen,event);
	    if(returnStatus == 5)
	      return 5;
	  }
	  else if((mx > 275) && (mx < 718) && (my > 305) && (my < 398)){
	    int returnStatus = editAdventureMenu(screen,event);
	    if(returnStatus == 5)
	      return 5;
	  }
	  else if((mx > 275) && (mx < 718) && (my > 430) && (my < 523)){
	    return 0;
	  }
	}
      }
      if(event.type == SDL_QUIT){
	  return 5;
      }
    }
    SDL_Flip(screen);

  }
  return 0;
}

int playChoiceMenu(SDL_Surface *screen, SDL_Event event){
  SDL_Surface *menuImage = NULL;
  bool quit = false;
  int mx = 0;
  int my = 0;
  menuImage = IMG_Load("playChoiceMenu.png");
    while(quit == false){
    applySurface(0,0, menuImage, screen);
    while(SDL_PollEvent(&event)){
      if(event.type == SDL_MOUSEBUTTONDOWN){
	if( event.button.button == SDL_BUTTON_LEFT ){
	  mx = event.button.x;
	  my = event.button.y;
	  if((mx > 275) && (mx < 718) && (my > 180) && (my < 273)){
	    int returnStatus = playAdventureMenu(screen,event, "Adventures");	    
	    if(returnStatus == 5)
	      return 5;
	  }
	  else if((mx > 275) && (mx < 718) && (my > 305) && (my < 398)){
	    int returnStatus = playAdventureMenu(screen,event, "Saved games");
	    if(returnStatus == 5)
	      return 5;
	  }
	  else if((mx > 275) && (mx < 718) && (my > 430) && (my < 523)){
	    return 0;
	  }
	}
      }
      if(event.type == SDL_QUIT){
	return 5;
      }
    }
    SDL_Flip(screen);

  }
  return 0;
}


int playAdventureMenu(SDL_Surface *screen, SDL_Event event, string filePath){
  SDL_Surface *menuImage = NULL;
  SDL_Surface *message = NULL;
  bool quit = false;
  string temp;
  int pos = 0;
  string fileNames = searchD(filePath);
  int mx = 0;
  int my = 0;
  TTF_Font *font = NULL;
  SDL_Color textColor = {255, 255, 255}; 
  font = TTF_OpenFont("arial.ttf", 28);
  menuImage = IMG_Load("playChooseAdventure.png");
    while(quit == false){
      applySurface(0,0, menuImage, screen);
      printText(fileNames,292 , 146,textColor,message,font,screen);
    while(SDL_PollEvent(&event)){
      if(event.type == SDL_MOUSEBUTTONDOWN){
        if( event.button.button == SDL_BUTTON_LEFT ){
            mx = event.button.x;
            my = event.button.y;
            for(int i = 0; i < fileNames.length()/36; ++i){
                if((mx > 282) && (mx < 736) && (my > (146+28*i+3)) && (my < (146+28*(i+1)+3))){
                    pos = fileNames.find(" ", 36*i);
                    temp = fileNames.substr(36*i, pos-36*i);
                    //cout << "." << temp << "." << endl;
                    int returnStatus = game(screen,event,filePath + "//" + temp);
		    if(returnStatus == 5)
		      return 5;
                }
                else if((mx > 278) && (mx < 741) && (my > 603) && (my < 681) ){
                    quit = true;
                }
            }
        }
      }
      if(event.type == SDL_QUIT){
        return 5;
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
  int pos = 0;
  string fileNames = searchD("Adventures");
  int mx = 0;
  int my = 0;
  TTF_Font *font = NULL;
  SDL_Color textColor = {255, 255, 255};
  font = TTF_OpenFont("arial.ttf", 28);
  menuImage = IMG_Load("editorChooseAdventure.png");
    while(quit == false){
      applySurface(0,0, menuImage, screen);
      
      printText(fileNames,292 , 146,textColor,message,font,screen);
    while(SDL_PollEvent(&event)){
      if(event.type == SDL_MOUSEBUTTONDOWN){
        if( event.button.button == SDL_BUTTON_LEFT ){
            mx = event.button.x;
            my = event.button.y;
            for(int i = 0; i < fileNames.length()/36; ++i){
                if((mx > 282) && (mx < 736) && (my > (146+28*i+3)) && (my < (146+28*(i+1)+3))){
                    pos = fileNames.find(" ", 36*i);
                    temp = fileNames.substr(36*i, pos-36*i);
		    int returnStatus = editor(screen,event,temp,"");
		    if(returnStatus == 5)
		      return 5;
                }
                else if((mx > 278) && (mx < 741) && (my > 603) && (my < 681) ){
                    quit = true;
                }
            }
        }
      }
      if(event.type == SDL_QUIT){
        return 5;
      }
    }
    SDL_Flip(screen);

  }
  return 0;
}
int editNewAdventureFile(SDL_Surface *screen, SDL_Event event){
  SDL_Surface *menuImage = NULL;
  bool quit = false;
  int textLength = 20;
  int mx = 0;
  int my = 0;
  StringInput inputText;
  string text;
  menuImage = IMG_Load("newAdventureFilename.png");
  while(quit == false){
    applySurface(0,0, menuImage, screen);
    while(SDL_PollEvent(&event)){
      inputText.handleInput(event,textLength);
      if((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_RETURN)){
	text = inputText.getStr();
	ofstream newFile;
	newFile.open("Adventures//" + text + ".txt");
	if(!newFile.is_open())
	  cerr << "couldn't create: " << text << "\n"; 
	newFile.close();
	int returnStatus = editNewAdventureImage(screen,event,text);
	if(returnStatus == 1)
	  return 0;
	else if(returnStatus == 5)
	  return 5;
	inputText.clearString();
      }
      if(event.type == SDL_MOUSEBUTTONDOWN){
	if( event.button.button == SDL_BUTTON_LEFT ){
	  mx = event.button.x;
	  my = event.button.y;
	  
	  if((mx > 275) && (mx < 718) && (my > 430) && (my < 523)){
	    return 0;
	  }
	}
      }
      if(event.type == SDL_QUIT){
	  return 5;
      }
    }

    inputText.showMessage(screen, 400, 350);
    SDL_Flip(screen);

  }
  return 0;
}


int editNewAdventureImage(SDL_Surface *screen, SDL_Event event, string text){
  SDL_Surface *menuImage = NULL;
  bool quit = false;
  int textLength = 20;
  int mx = 0;
  int my = 0;
  StringInput inputText;
  string imagePath;
  menuImage = IMG_Load("defaultImageName.png");
  while(quit == false){
    applySurface(0,0, menuImage, screen);
    while(SDL_PollEvent(&event)){
      inputText.handleInput(event,textLength);
      if((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_RETURN)){
	imagePath = inputText.getStr();
	
	int returnStatus = editor(screen,event,text,"Adventures//" + imagePath + ".png");
	if(returnStatus == 1)
	  return 1;
	else if(returnStatus == 5)
	  return 5;
      }
      if(event.type == SDL_MOUSEBUTTONDOWN){
	if( event.button.button == SDL_BUTTON_LEFT ){
	  mx = event.button.x;
	  my = event.button.y;
	  
	  if((mx > 275) && (mx < 718) && (my > 430) && (my < 523)){
	    return 1;
	  }
	}
      }
      if(event.type == SDL_QUIT){
	  return 5;
      }
    }

    inputText.showMessage(screen, 400, 350);
    SDL_Flip(screen);

  }
  return 0;
}
