#ifndef printText_h
#define printText_h
#include "SDL/SDL_ttf.h"
#include "SDL/SDL.h"
#include <string>
#include "sdlFunctions.h"

using namespace std;

void printText(string text, int x, int y, SDL_Color textColor,SDL_Surface* message,TTF_Font* font,SDL_Surface* screen);


#endif
