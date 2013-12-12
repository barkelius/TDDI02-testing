#include "SDL/SDL_ttf.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include "StringInput.h"
#include "sdlFunctions.h"
#include "printText.h"
#include "functions.h"
#include "player.h"
#include "character.h"
#include "Game.h"
#include <iostream>

using namespace std;

//Funktionen för spel läget
int game(SDL_Surface *screen, SDL_Event event, string fileName){

  SDL_Surface *background = NULL;
  SDL_Surface *message = NULL;
  SDL_Surface *roomImage = NULL;
  int mx = 0;                                                //initierar allt som man behöver i början av funktionen
  int my = 0;
  int textLength = 36;
  SDL_Color textColor = {255, 255, 255};

  TTF_Font *font = NULL;
  bool quit = false;
  Player player(fileName);                                   //skapar spelaren med korrekt fil
  player.moveFile();                                         //flytar den filen som man börjat på från Adventures mappen till saved games mappen

  background = IMG_Load("background_image_black.png");
  roomImage = IMG_Load(player.getRoomImage().c_str());
  if(roomImage == NULL){
    roomImage = IMG_Load(player.getDefaultImage().c_str());  //om rummbilden inte finns så laddas standardbilden in
  }
  font = TTF_OpenFont("arial.ttf", 28);

  StringInput inputText;
  string text;
  string text3 = "";
  string roomDescriptionText = "Room: " + player.getRoomName();
  for(int x = 0; x < 36-roomDescriptionText.size(); ++x){
        roomDescriptionText += " ";
  }
  roomDescriptionText += "Description: " + player.getRoomDescription();
  //While loopen för spelläget, här är man sålänge man är inne i spelläget 
  while(quit == false){
    applySurface(0,0, background, screen);
    applySurface(515,0, roomImage, screen);
    printText(roomDescriptionText,10 , 10,textColor,message,font,screen);
    printText(text,10 , (roomDescriptionText.length()/36)*28 + 50,textColor,message,font,screen );                      //Dynamiska texter som skrivs ut på olika y kordinater beroende på hur lång
    printText(text3, 10, ((text.length() + roomDescriptionText.length())/36)*28 + 50,textColor,message,font,screen);    //den nuvarande rumm beskrivningen är

    while(SDL_PollEvent(&event)){

      inputText.handleInput(event,textLength);

      if((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_RETURN)){

        string tmp = inputText.getStr();
        int pos = tmp.find(" ");
        string cmd = tmp.substr(0,pos);
        string cmd2 = tmp.substr(pos+1,tmp.length());                              //uppdelning av den inskrivna texten i 2 commandon så att man kan aktivera en funtione med den ena och skicka med den andra

	//if satser för alla kommandonan i spelläget, deras funktioner kallas på med det andra kommandot
        if(cmd == "Talk" || cmd == "talk"){
         text = player.talk();
        }
        else if(cmd == "Use" || cmd == "use"){
         text = player.useItem(cmd2);
        }
        else if(cmd == "Inventory" || cmd == "inventory"){
         text = player.printInventory();
        }
        else if(cmd == "Walk" || cmd == "walk"){
         roomDescriptionText = player.walk(cmd2);
         text3 = "";
         roomImage = IMG_Load(player.getRoomImage().c_str());
         if(roomImage == NULL){
	   roomImage = IMG_Load(player.getDefaultImage().c_str());            //hämtar standardbilden ifall rummet inte har någon bild
         }
         text = "";
        }
        else if(cmd == "Pickup" || cmd == "pickup"){
         text = player.pickUpItem(cmd2);
        }
        else{
         text = "Unknown command";
        }
        inputText.clearString();
        SDL_FreeSurface(message);

      }
      if(player.isGameOver()){              //kollar efter när man vinner spelet och laddar in den korrekta bilden och tömmer alla strängar på skärmen
        text = "";
        roomDescriptionText = "";
        text3 ="";
        background = IMG_Load("gameOver.png");
        roomImage = NULL;
        if(event.type == SDL_QUIT){
         return 5;
        }
      }

      if(event.type == SDL_QUIT){
        return 5;
      }
      //hanterar musklick för meny knapparna på höger sida
      if(event.type == SDL_MOUSEBUTTONDOWN){
        if( event.button.button == SDL_BUTTON_LEFT ){
	  mx = event.button.x;
	  my = event.button.y;
	  if((mx > 610) && (mx < 935) && (my > 632) && (my < 700)){
	    return 4;
	  }
	  else if((mx > 610) && (mx < 935) && (my > 383) && (my < 447)){
	    text3 = player.helpFunction();
	  }
	  else if((mx > 610) && (mx < 935) && (my > 507) && (my < 571)){
	    text = player.printInventory();
	  }
        }
      } 
    }

    inputText.showMessage(screen,10,675);    //Visar den inskrivna strängen från tangentbordet på skärmen

    SDL_Flip(screen);

  }

  cleanUp(background,message,font); // rensar upp när man stänger ner

}
