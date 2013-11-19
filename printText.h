#include "SDL/SDL_ttf.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include <vector>
#include <iostream>
#include "sdlFunctions.h"

void printText(string text, int x, int y){

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
    applySurface(x,(y+(i *20)), message, screen);
  }
}



