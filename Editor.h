#ifndef Editor_h
#define Editor_h
#include "SDL/SDL_ttf.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>

int editor(SDL_Surface *screen, SDL_Event event, std::string fileName, std::string imagePath);
std::string helpFunction();
#endif
