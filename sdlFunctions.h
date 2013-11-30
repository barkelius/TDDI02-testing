#ifndef sdlFunctions_h
#define sdlFunctions_h

void applySurface( int x, int y, SDL_Surface* source, SDL_Surface* destination);

void cleanUp(SDL_Surface* background, SDL_Surface* message, TTF_Font* font);

#endif
