CCC	= g++ -std=c++11 
LFLAGS	= -lSDL -lSDL_image -lSDL_ttf -L/sw/gcc-$(GCC4_V)/lib -static-libstdc++


exec: Game.cpp Editor.cpp character.cpp EditorFunctions.cpp functions.cpp item.cpp Menu.cpp player.cpp printText.cpp room.cpp sdlFunctions.cpp searchDirectory.cpp StringInput.cpp
	g++ -std=c++11 -o Game Game.cpp Editor.cpp character.cpp EditorFunctions.cpp functions.cpp item.cpp Menu.cpp player.cpp printText.cpp room.cpp sdlFunctions.cpp searchDirectory.cpp StringInput.cpp -lSDL -lSDL_image -lSDL_ttf


