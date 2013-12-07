#
# Makefile för vårat spel
#

CCC	= g++ -std=c++11 
LFLAGS	= -lSDL -lSDL_image -lSDL_ttf -L/sw/gcc-$(GCC4_V)/lib -static-libstdc++

exec: Player.o Item.o Character.o Room.o SdlFunctions.o StringInput.o PrintText.o Functions.o
	$(CCC) -o Game Game.o Player.o Item.o Character.o Room.o SdlFunctions.o StringInput.o PrintText.o Functions.o $(LFLAGS)

Game.o: Game.cpp Game.h
	$(CCC) -o Game Game.cpp

Player.o: player.cpp player.h
	$(CCC) -c -o Player.o player.cpp

Item.o:	item.cpp item.h
	$(CCC) -c -o Item.o item.cpp

Character.o: character.cpp character.h
	$(CCC) -c -o Character.o character.cpp

Room.o: room.cpp room.h
	$(CCC) -c -o Room.o room.cpp

SdlFunctions.o: sdlFunctions.cpp sdlFunctions.h
	$(CCC) -c $(LFLAGS) -o SdlFunctions.o sdlFunctions.cpp
	
StringInput.o: StringInput.cpp StringInput.h
	$(CCC) -c $(LFLAGS) -o StringInput.o StringInput.cpp
	
PrintText.o: printText.cpp printText.h 
	$(CCC) -c $(LFLAGS) -o PrintText.o printText.cpp
	
Functions.o: functions.cpp functions.h
	$(CCC) -c -o Functions.o functions.cpp

Editor.o: Editor.cpp Editor.h
	$(CCC) -c -o Editor.o Editor.cpp

