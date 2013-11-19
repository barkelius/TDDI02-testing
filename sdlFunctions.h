#ifndef sdlFunction_h
#define sdlFunction_h
#include "SDL/SDL_ttf.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>

SDL_Surface *background = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *message = NULL;
SDL_Event event;

TTF_Font *font = NULL;

SDL_Color textColor = {255, 255, 255};

using namespace std;

void applySurface( int x, int y, SDL_Surface* source, SDL_Surface* destination){

  SDL_Rect offset; 
  
  offset.x = x; 
  offset.y = y; 
   
  SDL_BlitSurface( source, NULL, destination, &offset ); 
}

bool init(){
  const int width = 1024;
  const int height = 720;
  const int bpp = 32;

  if(SDL_Init(SDL_INIT_EVERYTHING) == -1){
    return false;
  }
  screen = SDL_SetVideoMode(width,height,bpp,SDL_SWSURFACE);

  if(screen == NULL){
    return false;
  }
  
  if(TTF_Init() == -1){
       return false;
  }

  SDL_WM_SetCaption("Adventure", NULL);
  
  return true;
}

bool loadFiles(){
  background = IMG_Load("background_image_black.png");

  font = TTF_OpenFont("lazy.ttf", 28);
  
  if(background == NULL){
    return false;
  }
  
  if(font == NULL){
    return false;
  }
  
  return true;
}



void cleanUp(){
  SDL_FreeSurface(background);
  SDL_FreeSurface(message);
 	
  TTF_CloseFont(font);

  TTF_Quit();

  SDL_Quit();
}

#endif
