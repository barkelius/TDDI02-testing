#include "SDL/SDL_ttf.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>

const int width = 640;
const int height = 480;
const int bpp = 32;

SDL_Surface *background = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *message = NULL;
SDL_Event event;

TTF_Font *font = NULL;

SDL_Color textColor = {255, 255, 255};

using namespace std;


class StringInput{
private:
  string str;

  SDL_Surface *text;

public:
  StringInput();
  ~StringInput();

  void handleInput();

  void showMessage();
  void clearString();
};

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

void StringInput::handleInput(){
  if(event.type == SDL_KEYDOWN){
    string tmp = str;
    if(str.length() <= 20){
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
    
      //om man trycker ner en stor bokstav
      else if((event.key.keysym.unicode >=(Uint16)'a') && (event.key.keysym.unicode <= (Uint16)'z')){
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

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination) {
 //Holds offsets 
  SDL_Rect offset; 
  
  //Get offsets 
  offset.x = x; 
  offset.y = y; 
  
  //Blit 
  SDL_BlitSurface( source, NULL, destination, &offset ); 
}

void StringInput:: showMessage(){
  if(text != NULL){
    apply_surface((width -text-> w)/ 2, (height - text-> h) /2, text, screen);
  }
}

bool init(){
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

  SDL_WM_SetCaption("bla", NULL);
  
  return true;
}

SDL_Surface *load_image( std::string filename){
  
  SDL_Surface* loadedImage = NULL;
  SDL_Surface* optimizedImage = NULL;
  
  loadedImage = IMG_Load( filename.c_str());
  
  if(loadedImage != NULL){
    optimizedImage = SDL_DisplayFormat(loadedImage);
    SDL_FreeSurface(loadedImage);
  }
  
  return optimizedImage;
}

bool load_files(){
  background = load_image("background.png");

  font = TTF_OpenFont("data-latin.ttf", 28);
  
  if(background == NULL){
    return false;
  }
  
  if(font == NULL){
    return false;
  }
  
  return true;
}



void clean_up(){
  SDL_FreeSurface(background);
  SDL_FreeSurface(message);
 	
  TTF_CloseFont(font);

  TTF_Quit();

  SDL_Quit();
}

int main(int argc, char* args[]){
  bool quit = false;
  
  bool nameEntered = false;

  if(init() == false){
    return 1;
  }

  StringInput name;

  if(load_files() == false){
    return 1;
  }

  message = TTF_RenderText_Solid(font, "Skriv ditt namn: ", textColor);

  while(quit == false){
    while(SDL_PollEvent(&event)){
      // if(nameEntered == false){
	name.handleInput();
	if((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_RETURN)){
	  //nameEntered = true;
	  name.clearString();
	  SDL_FreeSurface(message);
	  message = TTF_RenderText_Solid(font, "Rank: 1st ", textColor);
	}
	// }
      if(event.type == SDL_QUIT){
	quit = true;
      }
    }
    apply_surface(0,0, background, screen);

    apply_surface((width - message->w)/2, ((height/2)- message->h)/2,message, screen );
    
    name.showMessage();
    
    if(SDL_Flip(screen) == -1){
      return 1;
    }
  }
  clean_up();

  return 0;
}
