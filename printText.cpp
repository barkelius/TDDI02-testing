#include "SDL/SDL_ttf.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

const int width = 640;
const int height = 480;
const int bpp = 32;

SDL_Surface *background = NULL;
SDL_Surface *message = NULL;
SDL_Surface *screen = NULL;

SDL_Event event;

TTF_Font *font = NULL;

SDL_Color textColor = {255, 255, 255};
SDL_Color bColor;

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

  SDL_WM_SetCaption("TTF Test", NULL);
  
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

  font = TTF_OpenFont("data-latin.ttf", 20);
  
  if(background == NULL){
    return false;
  }
  
  if(font == NULL){
    return false;
  }
  
  return true;
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

void clean_up(){
  SDL_FreeSurface(background);
  SDL_FreeSurface(message);

  TTF_CloseFont(font);

  TTF_Quit();

  SDL_Quit();
}



//template<typename T>
void printText(string text){

  vector<string> lines;
  string temp;
  int length = text.length();
  while(text.length() > 50){
    int pos = text.rfind(" ",50);
    temp = text.substr(pos,length);
    text.resize(pos);
    lines.push_back(text);
    length = text.length();
    text = temp;
   
  }

  //lines.push_back(text);
  //string bla = "hej";
  // lines.push_back(bla);
  
  for(int i = 0; i < lines.size(); ++i){
    message = TTF_RenderText_Solid(font,lines[i].c_str(),textColor);
    apply_surface(0,(150+(i *20)), message, screen);
  }
}


int main(int argc, char* args[]){
  bool quit = false;

  if(init() == false){
    return 1;
  }

  if(load_files() == false){
    return 1;
  }

  string text = "123456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789 ";
  string text2 = "skit"; 
  
  apply_surface(0,0, background, screen);
  printText(text);
  //printText(text2);
  if(SDL_Flip(screen) == -1){
    return 1;
  }

  while(quit == false){
    while(SDL_PollEvent(&event)){
      if(event.type == SDL_QUIT){
	quit = true;
      }
    }
  }

  clean_up();
  return 0;
}
