#include "SDL/SDL_ttf.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include "sdlFunctions.h"
#include "StringInput.h"

using namespace std;

StringInput::StringInput(){
  str = "";

  text = NULL;

  SDL_EnableUNICODE(SDL_ENABLE);
}

StringInput::~StringInput(){
  SDL_FreeSurface(text);

  SDL_EnableUNICODE(SDL_DISABLE); 
}

void StringInput::clearString(){
  str= "";
  text = NULL;
}

string StringInput::getStr(){
  return str;
}

void StringInput::handleInput(SDL_Event event){
  if(event.type == SDL_KEYDOWN){
    string tmp = str;
    if(str.length() <= 33){
      //om man tycker ner space
      if(event.key.keysym.unicode == (Uint16)' '){
	str += (char)event.key.keysym.unicode;
      }
      
      //om man trycker ner en siffra
      else if((event.key.keysym.unicode >=(Uint16)'0') && (event.key.keysym.unicode <= (Uint16)'9')){
	str += (char)event.key.keysym.unicode;
      }
    
      //om man trycker ner en stor bokstav
      else if((event.key.keysym.unicode >=(Uint16)'A') && (event.key.keysym.unicode <= (Uint16)'Z')){
	str += (char)event.key.keysym.unicode;
      }
    
      //om man trycker ner en liten bokstav
      else if((event.key.keysym.unicode >=(Uint16)'a') && (event.key.keysym.unicode <= (Uint16)'z')){
	str += (char)event.key.keysym.unicode;
      }

      else if((event.key.keysym.unicode >=(Uint16)'!') && (event.key.keysym.unicode <= (Uint16)'?')){
	str += (char)event.key.keysym.unicode;
      }

    }
    
    // vid tryck på backspace när strängen inte är tom
    if((event.key.keysym.unicode == SDLK_BACKSPACE) && (str.length() != 0)){
      str.erase(str.length() -1);
    }
  
    if(str != tmp){
      SDL_FreeSurface(text);
      text = TTF_RenderText_Solid(font, str.c_str(), textColor);
    }
  }
}


void StringInput:: showMessage(SDL_Surface *screen){
  if(text != NULL){
    applySurface(10,675, text, screen);
  }
}
