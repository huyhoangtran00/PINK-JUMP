all:
	g++ -Isrc/include -Lsrc/lib -o main main.cpp Object.cpp Player.cpp Rock.cpp Map.cpp Menu.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer 