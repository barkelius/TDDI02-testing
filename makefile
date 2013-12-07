#
# Makefile för vårat spel
# Sparar filen som Game
#

CCC	= g++ -std=c++11 
LFLAGS	= -lSDL -lSDL_image -lSDL_ttf -L/sw/gcc-$(GCC4_V)/lib -static-libstdc++


exec: Game.cpp Editor.cpp character.cpp EditorFunctions.cpp functions.cpp item.cpp Menu.cpp player.cpp printText.cpp room.cpp sdlFunctions.cpp searchDirectory.cpp StringInput.cpp
	$(CCC) $(LFLAGS) -o Game Game.cpp sdlFunctions.cpp printText.cpp StringInput.cpp functions.cpp character.cpp item.cpp room.cpp player.cpp Menu.cpp searchDirectory.cpp Editor.cpp EditorFunctions.cpp
