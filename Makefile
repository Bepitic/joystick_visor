all:
	g++ src\main.cpp -o vjs.exe -DSFML_STATIC -IC:\SFML\SFML\include -LC:\SFML\SFML\lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32 -lfreetype
