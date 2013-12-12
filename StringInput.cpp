#include "SDL/SDL_ttf.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include "sdlFunctions.h"
#include "StringInput.h"
#include <vector>

using namespace std;

//Konstruktor som initierar en sträng och sätter igång Unicode
StringInput::StringInput(){
  str = "";

  text = NULL;

  SDL_EnableUNICODE(SDL_ENABLE);
}

//Destruktor som tar bort textens sdl pekare och stänger av Unicode
StringInput::~StringInput(){
  SDL_FreeSurface(text);

  SDL_EnableUNICODE(SDL_DISABLE); 
}

//tömmer strängen och sätter sdl pekaren till null
void StringInput::clearString(){
  str= "";
  text = NULL;
}

//hämtar strängen som man skrivit in
string StringInput::getStr(){
  return str;
}

//hanterar knapptryck
void StringInput::handleInput(SDL_Event event,int textLength){
  if(event.type == SDL_KEYDOWN){
    string tmp = str;
    if(str.length() <= textLength){
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
      
      //om man använder shift till sammans med siffer tangenterna
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

//Skriver ut sdl pekaren på skärmen, under 76 tecken från vänster över 76 tecken från höger
void StringInput:: showMessage(SDL_Surface *screen, int x, int y){
  if(text != NULL){
     if(str.size() > 76)
       applySurface((935 - text->w),y, text, screen);
     else{
       applySurface(x,y, text, screen);
     }
  }
}
