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
#include <iostream>


using namespace std;

//Editor lägets funktion
int editor(SDL_Surface *screen, SDL_Event event, string fileName, string imagePath){

  SDL_Surface *background = NULL;
  SDL_Surface *message = NULL;
  SDL_Surface *roomImage = NULL;
  int mx = 0;
  int my = 0;                                                     //mus kordinater
  SDL_Color textColor = {255, 255, 255}; 
  TTF_Font *font = NULL;
  bool quit = false;
  background = IMG_Load("editorBackgroundImage.png");
  font = TTF_OpenFont("arial.ttf", 28);
  int ifStatementToUse = 0;
  int textLength = 330;
  StringInput inputText;
  string text;
  string text3 = "";
  string whatToType = "";                           //Initiering av variabler

  //Editorn lägets while loop, sålänge man är i while loopen så är man i editorn
  while(quit == false){
    applySurface(0,0, background, screen);
    printText(whatToType,10 , 10,textColor,message,font,screen);                                //Skriver ut text
    printText(text, 10, (whatToType.length()/36)*28 + 50,textColor,message,font,screen);        //skriver ut dynamsik text som skiftar i y led beroende på hur lång whatToType är
    //Hantering av mus och tangent tryck i editorn
    while(SDL_PollEvent(&event)){
      inputText.handleInput(event,textLength);

      if((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_RETURN)){

        string cmd = inputText.getStr();                                                         //Lagra inputten från tangentbordet i strängen cmd

	//if satser för alla olika kommandon i editorn
	//alla kommandona har två lägen (if satser) först så letar vi efter en sträng, när denna sträng hittas så skrivs en hjälptext ut och
	// ifStatementToUse sätts till till ett unikt värde som sen triggar igång en till if sats där man får skriva in det som faktiskt kommer hamna i text filen
        if(cmd == "Makeroom" || cmd == "makeroom"){
         whatToType = "Type Id;Name;Description;ImagePath; DoorId;DoorId;DoorId;DoorId;winRoom; Press help for further explanations";
         cout<<"Fil namn:"<< fileName<< endl;
         ifStatementToUse = 1;
        }
        else if(ifStatementToUse == 1){
         if(roomToFile(cmd, imagePath, fileName) == false)
         whatToType = "Wrong input format";
         else
         whatToType = "Creation successful";
         ifStatementToUse = 0;
        }

        else if(cmd == "Makeitem" || cmd == "makeitem") {
         whatToType = "Type roomId;item id;Name;Text;";
         ifStatementToUse = 2;
        }
        else if(ifStatementToUse == 2){
         if(itemToFile(cmd, fileName) == false)
         whatToType = "Wrong input format";
         else
         whatToType = "Creation successful";
         ifStatementToUse = 0;
        }
        else if(cmd == "Makecharacter" || cmd == "makecharacter") {
         whatToType = "Type roomId;character id;Name;Text;";
         ifStatementToUse = 3;
        }
        else if(ifStatementToUse == 3){
         if(characterToFile(cmd, fileName) == false)
         whatToType = "Wrong input format";
         else
         whatToType = "Creation successful";
         ifStatementToUse = 0;
        }
        else if(cmd == "Deleteroom" || cmd == "deleteroom"){
         whatToType = "Type roomId";
         ifStatementToUse = 4;
        }
        else if(ifStatementToUse == 4){
         if(deleteRoom(cmd, fileName) == false)
         whatToType = "Could not delete room";
         else
         whatToType = "Deletion successful";
         ifStatementToUse = 0;
        }
        else if(cmd == "Deleteitem" || cmd == "deleteitem"){
         whatToType = "Type itemId";
         ifStatementToUse = 5;
        }
        else if(ifStatementToUse == 5){
         if(deleteItem(cmd, fileName) == false)
         whatToType = "Could not delete item";
         else
         whatToType = "Deletetion successful";
         ifStatementToUse = 0;
        }
        else if(cmd == "Deletcharacter" || cmd == "deletecharacter"){
         whatToType = "Type characterId";
         ifStatementToUse = 6;
        }
        else if(ifStatementToUse == 6){
         if(deleteCharacter(cmd, fileName) == false)
         whatToType = "Could not delete character";
         else
         whatToType = "Deletion successful";
         ifStatementToUse = 0;
        }

        else{                    //om kommandot inte finns skrivs unknown command ut
         text = "Unknown command";
        }
        inputText.clearString();
        SDL_FreeSurface(message);

      }
      if(event.type == SDL_QUIT){
	setCurrentRoom(fileName);
	return 5;
      }
      if(event.type == SDL_MOUSEBUTTONDOWN){
	if( event.button.button == SDL_BUTTON_LEFT ){
	  mx = event.button.x;
	  my = event.button.y;
	  if((mx > 610) && (mx < 935) && (my > 349) && (my < 435)){   //vid tryck på sav and quit så går man tillbaka till den föregående menyn allternativ den första 
	    setCurrentRoom(fileName);                                 //editor undermenyn ifall det är ett ny skapat äventyr 
	    return 1;                                                 //när man avslutar så sätts även ett current room annars kan saker gå sönder när man försöker starta spelet
	  }
	  else if((mx > 610) && (mx < 935) && (my > 203) && (my < 289)){   //vid tryck på help knappen så skrivs hjälp texten ut
	    text = helpFunction(ifStatementToUse);
	  }
	}
      }
    }
    inputText.showMessage(screen, 10,675);   //skriver ut inputt från tangentbordet på skärmen

    SDL_Flip(screen);                        //uppdaterar skärmen


  }

  cleanUp(background,message,font);//städar upp vid avslut

}

//Funktion för att skriva ut hjälp text i editorn
string helpFunction(const int helpStatus){
  //skriver ut olika strängar beroende på vilket steg i editorn man är i
  string returnString;
  if(helpStatus == 1){
    returnString += "roomId=1XXX, ImagePath=imagename.png, DoorId=<id to a room>1XXX, winRoom=(1 or 0)";
  }
  else if(helpStatus == 2){
    returnString += "roomId=1XXX, itemId=2XXX";
  }
  else if(helpStatus == 3){
    returnString += "roomId=1XXX, characterId=3XXX";
  }
  else{
    returnString += "Commands available: " ;
    returnString += "'Makeroom', 'Makeitem', 'Makecharacter', 'Deleteroom', 'Deleteitem', 'Deletecharacter'";   //om man inte har skrivit in något alls så skrivs de olika kommandona ut som man kan skriva
  }
  return returnString;
}
