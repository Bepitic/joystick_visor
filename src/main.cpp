#include <SFML/Graphics.hpp>
#include <SFML/Window/Joystick.hpp>
#include <iostream>
#include <SDL2/SDL.h>

int main(int argv, char** args)
{
  if (SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK ) < 0)
   {
       std::cout << "Couldn't initialize SDL: " << SDL_GetError() << std::endl;
       return 1;
   }
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");


    sf::Texture texture;
    texture.loadFromFile("resources/Boton-D.png");
    sf::Sprite sprite;
    sprite.setTexture(texture);
    while (window.isOpen())
    {

      std::cout << "joysticks han sido encontrados :" << SDL_NumJoysticks() << std::endl;

      for( int i=0; i < SDL_NumJoysticks(); i++ )
      {
        SDL_Joystick *joystick = SDL_JoystickOpen(i);

          std::cout << "joystick" << i << " " << SDL_JoystickName(joystick) << std::endl;
      }
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

    }

    return 0;
}
