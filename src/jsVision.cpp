#include <SDL2/SDL.h>

#include <SDL2/SDL_image.h>
#include <iostream>



int main(int argv, char** args){
  SDL_Window* gWindow = NULL;
  bool success = true;
  SDL_Surface* gScreenSurface = NULL;
  if (SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | IMG_INIT_JPG | IMG_INIT_PNG) < 0)
  {
     std::cout << "Couldn't initialize SDL: " << SDL_GetError() << std::endl;
     return 1;
  }else { //Create window
    gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN );
    if( gWindow == NULL ) {
      printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
      success = false;
    } else {
      //Initialize PNG loading
      int imgFlags = IMG_INIT_PNG;
      if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        success = false;
      } else {
        //Get window surface
        gScreenSurface = SDL_GetWindowSurface( gWindow );
      }
    }
  }
  return success;

  SDL_Window *window = SDL_CreateWindow("sdl",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 800,600,SDL_WINDOW_SHOWN);

  return 0;
}
