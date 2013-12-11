#ifndef StringInput_h
#define StringInput_h

#include <string>
#include <SDL/SDL.h>
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_image.h"

class StringInput{
public:
  StringInput();
  ~StringInput();
  
  void handleInput(SDL_Event event, int textLength);
  std::string getStr();
  void showMessage(SDL_Surface *screen, int x, int y);
  void clearString();
private:
  std::string str;
  SDL_Surface *text;

  SDL_Color textColor = {255, 255, 255};
  TTF_Font *font = TTF_OpenFont("arial.ttf", 28);
};



#endif
