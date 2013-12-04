#include "SDL/SDL_ttf.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include <vector>
#include "sdlFunctions.h"
#include "printText.h"

using namespace std;

void printText(string text, int x, int y, SDL_Color textColor,SDL_Surface* message,TTF_Font* font,SDL_Surface* screen){

  vector<string> lines;
  string temp;
  while(text.length() > 37){
    int pos = text.rfind(" ",37);
    temp = text.substr(pos+1,text.length());
    text.resize(pos);
    lines.push_back(text);;
    text = temp;
  }

  lines.push_back(text);

  for(int i = 0; i < lines.size(); ++i){
    message = TTF_RenderText_Solid(font,lines[i].c_str(),textColor);
    applySurface(x,(y+(i *28)), message, screen);
  }

}
