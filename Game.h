#ifndef Game_h
#define Game_h
#include "SDL/SDL_ttf.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>

int game(SDL_Surface *screen, SDL_Event event, std::string fileName);

#endif
