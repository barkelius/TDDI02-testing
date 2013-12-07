#include "SDL/SDL_ttf.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "EditorFunctions.h"
#include <string>
#include "StringInput.h"
#include "sdlFunctions.h"
#include "printText.h"
#include "functions.h"
#include "player.h"
#include "character.h"
#include "Editor.h"


using namespace std;


int editor(SDL_Surface *screen, SDL_Event event, string fileName, string imagePath){

  SDL_Surface *background = NULL;
  SDL_Surface *message = NULL;
  SDL_Surface *roomImage = NULL;
  int mx = 0;
  int my = 0;

  SDL_Color textColor = {255, 255, 255};

  TTF_Font *font = NULL;
  bool quit = false;
  


  background = IMG_Load("background_image_black.png");
  // roomImage = IMG_Load(spelare.getRoomImage().c_str());
  font = TTF_OpenFont("Blockstepped.ttf", 28);
  int ifStatementToUse = 0;
  StringInput inputText;
  string text;
  string text3 = "";
  string whatToType = "";
  /*  string roomDescriptionText = "Room: " + spelare.getRoomName();
  for(int x = 0; x < 36-roomDescriptionText.size(); ++x){
        roomDescriptionText += " ";
  }
  roomDescriptionText += "Description: " + spelare.getRoomDescription();
  */
  while(quit == false){
    applySurface(0,0, background, screen);
    //applySurface(515,0, roomImage, screen);
    //  printText(roomDescriptionText,10 , 10,textColor,message,font,screen);
    // printText(text,10 , (roomDescriptionText.length()/36)*20 + 50,
    //	      textColor,message,font,screen );
    printText(whatToType,10 , 10,textColor,message,font,screen);
    printText(text, 10, 200,textColor,message,font,screen);
    while(SDL_PollEvent(&event)){

      inputText.handleInput(event);

      if((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_RETURN)){

	string cmd = inputText.getStr();
	//int pos = tmp.find(";");
	//string cmd = tmp.substr(0,pos);
	//string cmd2 = tmp.substr(pos,tmp.length());

	if(cmd == "Makeroom" || cmd == "makeroom"){
	  whatToType = "Type Id;Name;Description;ImagePath; DoorId;DoorId;DoorId;DoorId;winRoom;";
	  ifStatementToUse = 1;		
	}
	else if(ifStatementToUse == 1){
	  roomToFile(cmd, imagePath, fileName);
	  ifStatementToUse = 0;
	}
	/*else if((cmd == "Make" || cmd == "make") && (cmd2 == "Character" || cmd2 == "character")){
	  whatToType = "Type roomId;characterId;Name;Text;";
	  ifStatementToUse = 1;
	}*/
	else if(ifStatementToUse == 2){
	  text = "Make Character(" + cmd + ")";
	  ifStatementToUse = 0;
	}
	else{
	    text = "Unknown command";
	}
	inputText.clearString();
	SDL_FreeSurface(message);

      }
    if(event.type == SDL_QUIT){
	  return 0;
    }
      if(event.type == SDL_MOUSEBUTTONDOWN){
	if( event.button.button == SDL_BUTTON_LEFT ){
	  mx = event.button.x;
	  my = event.button.y;
	  if((mx > 610) && (mx < 935) && (my > 632) && (my < 700)){
	    return 1;
	  }
	  else if((mx > 610) && (mx < 935) && (my > 383) && (my < 447)){
	    text = helpFunction();
	  }
	}
      }



    }

    inputText.showMessage(screen, 10,675);

    SDL_Flip(screen);


  }

  cleanUp(background,message,font);

}

string helpFunction(){
  string returnString = "Commands available:                 ";
  returnString += "'Makeroom', 'Makeitem', 'Makecharacter'";
  return returnString;
}
