#include "SDL/SDL_ttf.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "sdlFunctions.h"
#include "Game.h"
#include "searchDirectory.h"
#include <string>
#include "printText.h"
#include <iostream>
#include "Editor.h"
#include "StringInput.h"
#include <fstream>

using namespace std;

int menu(SDL_Surface *screen,SDL_Event event);
int playChoiceMenu(SDL_Surface *screen, SDL_Event event);
int editChoiceMenu(SDL_Surface *screen, SDL_Event event);
int editAdventureMenu(SDL_Surface *screen, SDL_Event event);
int playAdventureMenu(SDL_Surface *screen, SDL_Event event, string filePath);
int editNewAdventureFile(SDL_Surface *screen, SDL_Event event);
int editNewAdventureImage(SDL_Surface *screen, SDL_Event event, string text);

//Vår main funktion som initierar skärmen och sdl biblioteken och kallar på menu
int main(int argc, char* argv[]){
  SDL_Surface *screen = NULL;
  const int width = 1024;
  const int height = 720;
  const int bpp = 32;
  SDL_Event event;
  SDL_Init(SDL_INIT_EVERYTHING);
  TTF_Init();
  SDL_WM_SetCaption("Adventure", NULL);
  screen = SDL_SetVideoMode(width,height,bpp,SDL_SWSURFACE);
  menu(screen,event);
}

//Funktionen för huvudmenyn
int menu(SDL_Surface *screen, SDL_Event event){
  SDL_Surface *menuImage = NULL;
  bool quit = false;
  int mx = 0;
  int my = 0;
  menuImage = IMG_Load("mainMenu.png");

  //Hanteringen av alla musklick så länge man är i huvudmenyn
  while(quit == false){
    applySurface(0,0, menuImage, screen);
    while(SDL_PollEvent(&event)){
      if(event.type == SDL_MOUSEBUTTONDOWN){
	if( event.button.button == SDL_BUTTON_LEFT ){
	  mx = event.button.x;                              //mus kordinater
	  my = event.button.y;
	  if((mx > 275) && (mx < 718) && (my > 180) && (my < 273)){   //vid tryck på knappen play kallas nästa funktion
	    int returnStatus = playChoiceMenu(screen,event);
	    if(returnStatus == 5)                               //när man får en femma betyder det att man har tryckt på krysset i någon 
	      return 0;                                         //tidigare funktion och proggramet avslutas
	  }
	  else if((mx > 275) && (mx < 718) && (my > 305) && (my < 398)){   //vid tryck på knappen edit kallas nästa funktion
	    int returnStatus = editChoiceMenu(screen,event);
	    if(returnStatus == 5)
	      return 0;
	  }
	  else if((mx > 275) && (mx < 718) && (my > 430) && (my < 523)){   //vid tryck på knappen quit kavslutas programmet
	    quit = true;
	  }
	}
      }
      if(event.type == SDL_QUIT){    // Vid tryck på krysset avslutas programmet
        quit = true;
      }
    }
    SDL_Flip(screen); // uppdaterar skärmen

  }

  return 0;
}

//Funktion för den första edit menyn
int editChoiceMenu(SDL_Surface *screen, SDL_Event event){
  SDL_Surface *menuImage = NULL;
  bool quit = false;
  int mx = 0;
  int my = 0;
  menuImage = IMG_Load("editChoiceMenu.png");
   //Hantering av musklick sålänge man är i menyn
    while(quit == false){
    applySurface(0,0, menuImage, screen);
    while(SDL_PollEvent(&event)){
      if(event.type == SDL_MOUSEBUTTONDOWN){
	if( event.button.button == SDL_BUTTON_LEFT ){
	  mx = event.button.x;
	  my = event.button.y;
	  if((mx > 275) && (mx < 718) && (my > 180) && (my < 273)){  //vid tryck på knappen create new adventure kallas nästa funktion
	    int returnStatus = editNewAdventureFile(screen,event);
	    if(returnStatus == 5)                                  //här returnar man en femma till funktionen ovanför
	      return 5;                                            // för att berätta att krysset har tryckts
	  }
	  else if((mx > 275) && (mx < 718) && (my > 305) && (my < 398)){ //vid tryck på knappen continue edit kallas nästa funktion
	    int returnStatus = editAdventureMenu(screen,event);
	    if(returnStatus == 5)
	      return 5;
	  }
	  else if((mx > 275) && (mx < 718) && (my > 430) && (my < 523)){  //vid tryck på knappen back går man tillbaka till föregående meny
	    return 0;
	  }
	}
      }
      if(event.type == SDL_QUIT){  //krysset returnar en femma till funktionen ovanför
	  return 5;
      }
    }
    SDL_Flip(screen);

  }
  return 0;
}

//Funktionen för den första play undermenyn
int playChoiceMenu(SDL_Surface *screen, SDL_Event event){
  SDL_Surface *menuImage = NULL;
  bool quit = false;
  int mx = 0;
  int my = 0;
  menuImage = IMG_Load("playChoiceMenu.png");
  //Hantering av musklick så länge man är i menyn
  while(quit == false){
    applySurface(0,0, menuImage, screen);
    while(SDL_PollEvent(&event)){
      if(event.type == SDL_MOUSEBUTTONDOWN){
	if( event.button.button == SDL_BUTTON_LEFT ){
	  mx = event.button.x;
	  my = event.button.y;
	  if((mx > 275) && (mx < 718) && (my > 180) && (my < 273)){  //vid tryck på knappen new adventure kallas nästa funktion
	    int returnStatus = playAdventureMenu(screen,event, "Adventures");	    
	    if(returnStatus == 5)
	      return 5;
	  }
	  else if((mx > 275) && (mx < 718) && (my > 305) && (my < 398)){  //vid tryck på knappen continue adventure kallas nästa funktion
	    int returnStatus = playAdventureMenu(screen,event, "Saved games");
	    if(returnStatus == 5)
	      return 5;
	  }
	  else if((mx > 275) && (mx < 718) && (my > 430) && (my < 523)){  //vid tryck på knappen back går man tillbaka till föregående meny
	    return 0;
	  }
	}
      }
      if(event.type == SDL_QUIT){
	return 5;
      }
    }
    SDL_Flip(screen);
    
  }
  return 0;
}

//Funktionen för continue adventure undermenyn
int playAdventureMenu(SDL_Surface *screen, SDL_Event event, string filePath){
  SDL_Surface *menuImage = NULL;
  SDL_Surface *message = NULL;
  bool quit = false;
  string temp;
  int pos = 0;
  string fileNames = searchD(filePath); //hämtar alla textfilers namn som ligger i rätt mapp
  int mx = 0;
  int my = 0;
  TTF_Font *font = NULL;
  SDL_Color textColor = {255, 255, 255}; 
  font = TTF_OpenFont("arial.ttf", 28);
  menuImage = IMG_Load("playChooseAdventure.png");
  //Hantering av musklick så länge man är i menyn
  while(quit == false){
    applySurface(0,0, menuImage, screen);
    printText(fileNames,292 , 146,textColor,message,font,screen);
    while(SDL_PollEvent(&event)){
      if(event.type == SDL_MOUSEBUTTONDOWN){
        if( event.button.button == SDL_BUTTON_LEFT ){
	  mx = event.button.x;
	  my = event.button.y;
	  for(int i = 0; i < fileNames.length()/36; ++i){   //beroende på hur många filnamn, bestämmer var på skärmen man kan klicka för att
	    if((mx > 282) && (mx < 736) && (my > (146+28*i+3)) && (my < (146+28*(i+1)+3))){  // aktivera de olika filerna
	      pos = fileNames.find(" ", 36*i);
	      temp = fileNames.substr(36*i, pos-36*i);
	      int returnStatus = game(screen,event,filePath + "//" + temp);
	      if(returnStatus == 5)
		return 5;
	    }
	    else if((mx > 278) && (mx < 741) && (my > 603) && (my < 681) ){ //vid tryck på knappen back går man tillbaka till föregående meny
	      quit = true;
	    }
	  }
        }
      }
      if(event.type == SDL_QUIT){
        return 5;
      }
    }
    SDL_Flip(screen);
    
  }
  return 0;
}

//Funktion för continue edit undermeny
int editAdventureMenu(SDL_Surface *screen, SDL_Event event){
  SDL_Surface *menuImage = NULL;
  SDL_Surface *message = NULL;
  bool quit = false;
  string temp;
  int pos = 0;
  string fileNames = searchD("Adventures");  //hämtar namn från mappen Adventures
  int mx = 0;
  int my = 0;
  TTF_Font *font = NULL;
  SDL_Color textColor = {255, 255, 255};
  font = TTF_OpenFont("arial.ttf", 28);
  menuImage = IMG_Load("editorChooseAdventure.png");
  //Hantering av musklick så länge man är i menyn
  while(quit == false){
    applySurface(0,0, menuImage, screen);
    printText(fileNames,292 , 146,textColor,message,font,screen);
    while(SDL_PollEvent(&event)){
      if(event.type == SDL_MOUSEBUTTONDOWN){
	if( event.button.button == SDL_BUTTON_LEFT ){
	  mx = event.button.x;
	  my = event.button.y;
	  for(int i = 0; i < fileNames.length()/36; ++i){  //beroende på hur många filnamn, bestämmer var på skärmen man kan klicka för att
	    if((mx > 282) && (mx < 736) && (my > (146+28*i+3)) && (my < (146+28*(i+1)+3))){  // aktivera de olika filerna
	      pos = fileNames.find(" ", 36*i);
	      temp = fileNames.substr(36*i, pos-36*i);
	      int returnStatus = editor(screen,event,temp,"");
	      if(returnStatus == 5)
		return 5;
	    }
	    else if((mx > 278) && (mx < 741) && (my > 603) && (my < 681) ){ //vid tryck på knappen back går man tillbaka till föregående meny
	      quit = true;
	    }
	  }
	}
      }
      if(event.type == SDL_QUIT){
	return 5;
      }
    }
    SDL_Flip(screen);  
  }
  return 0;
}

//Funktion för create new adventure undermeny
int editNewAdventureFile(SDL_Surface *screen, SDL_Event event){
  SDL_Surface *menuImage = NULL;
  bool quit = false;
  int textLength = 20;
  int mx = 0;
  int my = 0;
  StringInput inputText;
  string text;
  menuImage = IMG_Load("newAdventureFilename.png");
  //Hantering av mus och tangent tryck så länge man är i menyn
  while(quit == false){
    applySurface(0,0, menuImage, screen);
    while(SDL_PollEvent(&event)){
      inputText.handleInput(event,textLength);      
      if((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_RETURN)){
	text = inputText.getStr();     //lägger in den inskrivda texten i strängen text
	ofstream newFile;
	newFile.open("Adventures//" + text + ".txt");     //Skapar den nya filen i mappen Adventures
	if(!newFile.is_open())
	  cerr << "couldn't create: " << text << "\n"; 
	newFile.close();
	int returnStatus = editNewAdventureImage(screen,event,text);
	if(returnStatus == 1)    // om man får tillbaka en etta ska man gå tillbaka till föregående menyn 
	  return 0;
	else if(returnStatus == 5)
	  return 5;
	inputText.clearString();
      }
      if(event.type == SDL_MOUSEBUTTONDOWN){
	if( event.button.button == SDL_BUTTON_LEFT ){
	  mx = event.button.x;
	  my = event.button.y;
	  
	  if((mx > 275) && (mx < 718) && (my > 430) && (my < 523)){ //vid tryck på knappen back går man tillbaka till föregående meny
	    return 0;
	  }
	}
      }
      if(event.type == SDL_QUIT){
	  return 5;
      }
    }

    inputText.showMessage(screen, 400, 350); //visar den inskrivna texten på skärmen
    SDL_Flip(screen);

  }
  return 0;
}

//Funktion för standardbilden som man kommer till efter create new adventure undermeny
int editNewAdventureImage(SDL_Surface *screen, SDL_Event event, string text){
  SDL_Surface *menuImage = NULL;
  bool quit = false;
  int textLength = 20;
  int mx = 0;
  int my = 0;
  StringInput inputText;
  string imagePath;
  menuImage = IMG_Load("defaultImageName.png");
  //Hantering av mus och tangent tryck så länge man är i menyn
  while(quit == false){
    applySurface(0,0, menuImage, screen);
    while(SDL_PollEvent(&event)){
      inputText.handleInput(event,textLength);
      if((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_RETURN)){
	imagePath = inputText.getStr();              //lägger in det inskrivna bildnamnet i strängen imagePath
	int returnStatus = editor(screen,event,text,"Adventures//" + imagePath + ".png"); 
	if(returnStatus == 1)
	  return 1;
	else if(returnStatus == 5)
	  return 5;
      }
      if(event.type == SDL_MOUSEBUTTONDOWN){
	if( event.button.button == SDL_BUTTON_LEFT ){
	  mx = event.button.x;
	  my = event.button.y;
	  
	  if((mx > 275) && (mx < 718) && (my > 430) && (my < 523)){ //vid tryck på back knappen går tillbaka till den första edit undermenyn
	    return 1;
	  }
	}
      }
      if(event.type == SDL_QUIT){
	  return 5;
      }
    }

    inputText.showMessage(screen, 400, 350);
    SDL_Flip(screen);

  }
  return 0;
}
