all:
	g++ src\main.cpp -o vjs.exe -DSFML_STATIC -IC:\SFML\SFML\include -IC:\i686-w64-mingw32\include -LC:\SFML\SFML\lib -LC:\i686-w64-mingw32\lib -w -Wl,-subsystem,console -lmingw32 -lSDL2main -lSDL2 -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32 -lfreetype -lSDL2_image
console:
	g++ src\main.cpp -o vjs.exe -DSFML_STATIC -IC:\SFML\SFML\include -IC:\i686-w64-mingw32\include -LC:\SFML\SFML\lib -LC:\i686-w64-mingw32\lib -w -Wl,-subsystem,console -lmingw32 -lSDL2main -lSDL2 -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32 -lfreetype -lSDL2_image
windows:
	g++ src\main.cpp -o vjs.exe -DSFML_STATIC -IC:\SFML\SFML\include -IC:\i686-w64-mingw32\include -LC:\SFML\SFML\lib -LC:\i686-w64-mingw32\lib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32 -lfreetype -lSDL2_image

vision:
	g++ src\jsVision.cpp -o vjs.exe  -IC:\i686-w64-mingw32\include -LC:\i686-w64-mingw32\lib -w -Wl,-subsystem,console -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
