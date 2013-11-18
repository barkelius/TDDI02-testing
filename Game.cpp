#include "SDL/SDL_ttf.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include "StringInput.h"
#include "sdlFunctions.h"


int game();

int main(int argc, char* argv[]){
  game();
}

int game(){
  bool quit = false;
  
  bool nameEntered = false;

  if(init() == false){
    return 1;
  }

  StringInput name;

  if(loadFiles() == false){
    return 1;
  }

 

  while(quit == false){
    while(SDL_PollEvent(&event)){
      // if(nameEntered == false){
	name.handleInput();
	if((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_RETURN)){
	  //nameEntered = true;
	  name.clearString();
	  SDL_FreeSurface(message);
	  
	}
	// }
      if(event.type == SDL_QUIT){
	quit = true;
      }
    }
    applySurface(0,0, background, screen);


    
    name.showMessage();
    
    if(SDL_Flip(screen) == -1){
      return 1;
    }
  }
  cleanUp();

  return 0;
}

