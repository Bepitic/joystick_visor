#include <SFML/Graphics.hpp>
#include <SFML/Window/Joystick.hpp>
#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <fstream>

template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

int main(int argv, char** args)
{
  if (SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK ) < 0){
       std::cout << "Couldn't initialize SDL: " << SDL_GetError() << std::endl;
       return 1;
  }
   SDL_Joystick *joy;
   SDL_InitSubSystem(SDL_INIT_JOYSTICK);
   if (SDL_NumJoysticks() > 0) {
       // Open joystick
       joy = SDL_JoystickOpen(0);
       std::string line;
       if (joy) {

        std::ifstream myfile ( std::string(SDL_JoystickNameForIndex(0)) +".txt" );
        if (myfile.is_open()) {
          while ( std::getline (myfile,line) )
          {
            std::cout << line << '\n';
          }
          myfile.close();
        } else {
          std::cout <<  std::string(SDL_JoystickNameForIndex(0)) +".txt : Unable to open file, creating one.";

          std::ofstream myfile (std::string(SDL_JoystickNameForIndex(0)) +".txt");
          if (myfile.is_open())
          {
            for (int i = 0; i < SDL_JoystickNumButtons( joy); i++) {
              myfile << std::string("B") << i << "|posx|posy|scale|pathButton|pathButtonPressed|pathButtonReleased." << std::endl;
            }
            for (int i = 0; i < SDL_JoystickNumAxes( joy); i++) {
              myfile << std::string("A") << i << "|posx|posy|scale|pathButton|pathButtonPressed|pathButtonReleased." << std::endl;
            }


            myfile.close();
          }
          else
          {
            std::cout << "Unable to open file";
          }
        }
           printf("Name: %s\n", SDL_JoystickNameForIndex(0));
           printf("Number of Axes: %d\n", SDL_JoystickNumAxes(joy));
           printf("Number of Buttons: %d\n", SDL_JoystickNumButtons(joy));
           printf("Number of Balls: %d\n", SDL_JoystickNumBalls(joy));
       } else {
           printf("Couldn't open Joystick 0\n");
       }

  }




    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");


    sf::Texture texture;

    if (!texture.loadFromFile("resources/Boton-D.png")){
      return 1;
    }


    // Initialize the joystick subsystem


    // Check for joystick

    if (SDL_NumJoysticks() > 0) {
        // Open joystick
        joy = SDL_JoystickOpen(0);
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(110,0));
    while (window.isOpen())
    {
      std::cout << "joysticks han sido encontrados :" << SDL_NumJoysticks() << std::endl;

          if (joy) {
              printf("Opened Joystick 0\n");
              printf("Name: %s\n", SDL_JoystickNameForIndex(0));
              printf("Number of Axes: %d\n", SDL_JoystickNumAxes(joy));
              printf("Number of Buttons: %d\n", SDL_JoystickNumButtons(joy));
              printf("Number of Balls: %d\n", SDL_JoystickNumBalls(joy));
              for (int i = 0; i < SDL_JoystickNumButtons( joy); i++) {
                std::cout << "B" << i  <<  SDL_JoystickGetButton(joy,i) << std::endl;
              }
              for (int i = 0; i < SDL_JoystickNumAxes( joy); i++) {
                std::cout << "A" << i << SDL_JoystickGetAxis(joy,i) << std::endl;
              }
          } else {
              printf("Couldn't open Joystick 0\n");
          }
          SDL_JoystickUpdate();
          // Close if opened


        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                if (SDL_JoystickGetAttached(joy)) {
                    SDL_JoystickClose(joy);
                }
                window.close();
            }
        }
        window.clear(sf::Color::Black);
        window.draw(sprite);
        window.display();
    }


    return 0;
}
