#include "SDL/SDL_ttf.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include "sdlFunctions.h"


using namespace std;

void applySurface( int x, int y, SDL_Surface* source, SDL_Surface* destination){

  SDL_Rect offset; 
  
  offset.x = x; 
  offset.y = y; 
   
  SDL_BlitSurface( source, NULL, destination, &offset ); 
}

void cleanUp(SDL_Surface* background, SDL_Surface* message, TTF_Font* font){
  SDL_FreeSurface(background);
  SDL_FreeSurface(message);
 	
  TTF_CloseFont(font);

  TTF_Quit();

  SDL_Quit();
}
