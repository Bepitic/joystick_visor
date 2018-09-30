#include <SFML/Graphics.hpp>
#include <SFML/Window/Joystick.hpp>
#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <fstream>
#include <iomanip>
#include "json.hpp"
using json = nlohmann::json;

int main(int argv, char** args)
{
  if (SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK ) < 0){
    std::cout << "Couldn't initialize SDL: " << SDL_GetError() << std::endl;
    return 1;
  }
  SDL_Joystick *joy;
  json j;

  j["w"] = 800;
  j["h"] = 600;
  j["title"] = "JoystickVision";

  SDL_InitSubSystem(SDL_INIT_JOYSTICK);

  if (SDL_NumJoysticks() > 0) {
    joy = SDL_JoystickOpen(0);
    std::string line;

    if (joy) {
      std::ifstream f ( std::string(SDL_JoystickNameForIndex(0)) +".json" );

      if (f.is_open()) {
        f >> j;
        std::cout << j << '\n';
        f.close();

      } else {
        std::cout <<  std::string(SDL_JoystickNameForIndex(0)) +".json : Unable to open file, creating one.";

        //std::ofstream myfile (std::string(SDL_JoystickNameForIndex(0)) +".json");


        for (int i = 0; i < SDL_JoystickNumButtons( joy); i++) {
          j["Button"][i]["x"] = 0.0;
          j["Button"][i]["y"] = 0.0;
          j["Button"][i]["scale"] = 1.0;
          j["Button"][i]["pathButtonPresed"] = "resources/b"+ std::to_string(i) + "_pressed.png";
          j["Button"][i]["pathButtonReleased"] = "resources/b"+ std::to_string(i) + "_released.png";
        }
        for (int i = 0; i < SDL_JoystickNumAxes( joy); i++) {
          j["Axis"][i]["x"] = 0.0;
          j["Axis"][i]["y"] = 0.0;
          j["Axis"][i]["scale"] = 1.0;
          j["Axis"][i]["isButton"] = true;
          j["Axis"][i]["isTrigger"] = false;
          j["Axis"][i]["pathButtonPresed"] = "resources/a"+ std::to_string(i) + "_pressed.png";
          j["Axis"][i]["pathButtonReleased"] = "resources/a"+ std::to_string(i) + "_released.png";
        }
        for (int i = 0; i < SDL_JoystickNumHats(joy); i++) {

          j["Hat"][i]["x"] = 0.0;
          j["Hat"][i]["y"] = 0.0;
          j["Hat"][i]["scale"] = 1.0;
          j["Hat"][i]["pathLEFTUP"] = "resources/b"+ std::to_string(i) + "_LEFTUP.png";
          j["Hat"][i]["pathUP"] = "resources/b"+ std::to_string(i) + "_UP.png";
          j["Hat"][i]["pathRIGHTUP"] = "resources/b"+ std::to_string(i) + "_RIGHTUP.png";
          j["Hat"][i]["pathLEFT"] = "resources/b"+ std::to_string(i) + "_LEFT.png";
          j["Hat"][i]["pathCENTERED"] = "resources/b"+ std::to_string(i) + "_CENTERED.png";
          j["Hat"][i]["pathRIGHT"] = "resources/b"+ std::to_string(i) + "_RIGHT.png";
          j["Hat"][i]["pathLEFTDOWN"] = "resources/b"+ std::to_string(i) + "_LEFTDOWN.png";
          j["Hat"][i]["pathDOWN"] = "resources/b"+ std::to_string(i) + "_DOWN.png";
          j["Hat"][i]["pathRIGHTDOWN"] = "resources/b"+ std::to_string(i) + "_RIGHTDOWN.png";
          j["Hat"][i]["pathBase"] = "resources/b"+ std::to_string(i) + "_base.png";
        }
        std::ofstream f (std::string(SDL_JoystickNameForIndex(0)) +".json");
        f << std::setw(4) << j << std::endl;
        f.close();
      }
      std::string titulo = j["title"];
      sf::RenderWindow window(sf::VideoMode(j["w"], j["h"]), titulo );

      std::vector<sf::Texture> text_vector_button(j["Button"].size()*2);
      std::vector<sf::Texture> text_vector_axis(j["Axis"].size()*2);
      std::vector<sf::Texture> text_vector_hat(j["Hat"].size()*10);

      std::vector<sf::Sprite> sprite_vector_button(j["Button"].size()*2);
      std::vector<sf::Sprite> sprite_vector_axis(j["Axis"].size()*2);
      std::vector<sf::Sprite> sprite_vector_hat(j["Hat"].size()*10);


      if (SDL_NumJoysticks() > 0) {
        // Open joystick
        joy = SDL_JoystickOpen(0);
      }

      for( int i = 0; i < j["Button"].size(); i++){
        text_vector_button[i*2].loadFromFile(j["Button"].at(i)["pathButtonPresed"]);
        text_vector_button[i*2+1].loadFromFile(j["Button"].at(i)["pathButtonReleased"]);
        sprite_vector_button[i*2].setTexture(text_vector_button[i*2]);
        sprite_vector_button[i*2+1].setTexture(text_vector_button[i*2+1]);
        sprite_vector_button[i*2].setPosition(sf::Vector2f(j["Button"].at(i)["x"],j["Button"].at(i)["y"]));
        sprite_vector_button[i*2+1].setPosition(sf::Vector2f(j["Button"].at(i)["x"],j["Button"].at(i)["y"]));
        sprite_vector_button[i*2].setScale(sf::Vector2f(j["Button"].at(i)["scale"],j["Button"].at(i)["scale"]));
        sprite_vector_button[i*2+1].setScale(sf::Vector2f(j["Button"].at(i)["scale"],j["Button"].at(i)["scale"]));
      }

      for( int i = 0; i < j["Axis"].size(); i++){
        text_vector_axis[i*2].loadFromFile(j["Axis"].at(i)["pathButtonPresed"]);
        text_vector_axis[i*2+1].loadFromFile(j["Axis"].at(i)["pathButtonReleased"]);
        sprite_vector_axis[i*2].setTexture(text_vector_axis[i*2]);
        sprite_vector_axis[i*2+1].setTexture(text_vector_axis[i*2+1]);
        sprite_vector_axis[i*2].setPosition(sf::Vector2f(j["Axis"].at(i)["x"],j["Axis"].at(i)["y"]));
        sprite_vector_axis[i*2+1].setPosition(sf::Vector2f(j["Axis"].at(i)["x"],j["Axis"].at(i)["y"]));
        sprite_vector_axis[i*2].setScale(sf::Vector2f(j["Axis"].at(i)["scale"],j["Axis"].at(i)["scale"]));
        sprite_vector_axis[i*2+1].setScale(sf::Vector2f(j["Axis"].at(i)["scale"],j["Axis"].at(i)["scale"]));
      }

      for( int i = 0; i < j["Hat"].size(); i++){

        text_vector_hat[i*10].loadFromFile(j["Hat"].at(i)["pathLEFTUP"]);
        text_vector_hat[i*10+1].loadFromFile(j["Hat"].at(i)["pathUP"]);
        text_vector_hat[i*10+2].loadFromFile(j["Hat"].at(i)["pathRIGHTUP"]);
        text_vector_hat[i*10+3].loadFromFile(j["Hat"].at(i)["pathLEFT"]);
        text_vector_hat[i*10+4].loadFromFile(j["Hat"].at(i)["pathCENTERED"]);
        text_vector_hat[i*10+5].loadFromFile(j["Hat"].at(i)["pathRIGHT"]);
        text_vector_hat[i*10+6].loadFromFile(j["Hat"].at(i)["pathLEFTDOWN"]);
        text_vector_hat[i*10+7].loadFromFile(j["Hat"].at(i)["pathDOWN"]);
        text_vector_hat[i*10+8].loadFromFile(j["Hat"].at(i)["pathRIGHTDOWN"]);
        text_vector_hat[i*10+9].loadFromFile(j["Hat"].at(i)["pathBase"]);

        sprite_vector_hat[i*10].setTexture(text_vector_hat[i*10]);
        sprite_vector_hat[i*10+1].setTexture(text_vector_hat[i*10+1]);
        sprite_vector_hat[i*10+2].setTexture(text_vector_hat[i*10+2]);
        sprite_vector_hat[i*10+3].setTexture(text_vector_hat[i*10+3]);
        sprite_vector_hat[i*10+4].setTexture(text_vector_hat[i*10+4]);
        sprite_vector_hat[i*10+5].setTexture(text_vector_hat[i*10+5]);
        sprite_vector_hat[i*10+6].setTexture(text_vector_hat[i*10+6]);
        sprite_vector_hat[i*10+7].setTexture(text_vector_hat[i*10+7]);
        sprite_vector_hat[i*10+8].setTexture(text_vector_hat[i*10+8]);
        sprite_vector_hat[i*10+9].setTexture(text_vector_hat[i*10+9]);

        sprite_vector_hat[i*10].setPosition(sf::Vector2f(j["Hat"].at(i)["x"],j["Hat"].at(i)["y"]));
        sprite_vector_hat[i*10+1].setPosition(sf::Vector2f(j["Hat"].at(i)["x"],j["Hat"].at(i)["y"]));
        sprite_vector_hat[i*10+2].setPosition(sf::Vector2f(j["Hat"].at(i)["x"],j["Hat"].at(i)["y"]));
        sprite_vector_hat[i*10+3].setPosition(sf::Vector2f(j["Hat"].at(i)["x"],j["Hat"].at(i)["y"]));
        sprite_vector_hat[i*10+4].setPosition(sf::Vector2f(j["Hat"].at(i)["x"],j["Hat"].at(i)["y"]));
        sprite_vector_hat[i*10+5].setPosition(sf::Vector2f(j["Hat"].at(i)["x"],j["Hat"].at(i)["y"]));
        sprite_vector_hat[i*10+6].setPosition(sf::Vector2f(j["Hat"].at(i)["x"],j["Hat"].at(i)["y"]));
        sprite_vector_hat[i*10+7].setPosition(sf::Vector2f(j["Hat"].at(i)["x"],j["Hat"].at(i)["y"]));
        sprite_vector_hat[i*10+8].setPosition(sf::Vector2f(j["Hat"].at(i)["x"],j["Hat"].at(i)["y"]));
        sprite_vector_hat[i*10+9].setPosition(sf::Vector2f(j["Hat"].at(i)["x"],j["Hat"].at(i)["y"]));

        sprite_vector_hat[i*10].setScale(sf::Vector2f(j["Hat"].at(i)["scale"],j["Hat"].at(i)["scale"]));
        sprite_vector_hat[i*10+1].setScale(sf::Vector2f(j["Hat"].at(i)["scale"],j["Hat"].at(i)["scale"]));
        sprite_vector_hat[i*10+2].setScale(sf::Vector2f(j["Hat"].at(i)["scale"],j["Hat"].at(i)["scale"]));
        sprite_vector_hat[i*10+3].setScale(sf::Vector2f(j["Hat"].at(i)["scale"],j["Hat"].at(i)["scale"]));
        sprite_vector_hat[i*10+4].setScale(sf::Vector2f(j["Hat"].at(i)["scale"],j["Hat"].at(i)["scale"]));
        sprite_vector_hat[i*10+5].setScale(sf::Vector2f(j["Hat"].at(i)["scale"],j["Hat"].at(i)["scale"]));
        sprite_vector_hat[i*10+6].setScale(sf::Vector2f(j["Hat"].at(i)["scale"],j["Hat"].at(i)["scale"]));
        sprite_vector_hat[i*10+7].setScale(sf::Vector2f(j["Hat"].at(i)["scale"],j["Hat"].at(i)["scale"]));
        sprite_vector_hat[i*10+8].setScale(sf::Vector2f(j["Hat"].at(i)["scale"],j["Hat"].at(i)["scale"]));
        sprite_vector_hat[i*10+9].setScale(sf::Vector2f(j["Hat"].at(i)["scale"],j["Hat"].at(i)["scale"]));

      }
//---------------- ventana

      while (window.isOpen()){
        window.clear(sf::Color::Magenta);
        std::cout << "joysticks han sido encontrados :" << SDL_NumJoysticks() << std::endl;

        if (joy) {

          for (int i = 0; i < SDL_JoystickNumButtons( joy); i++) {
            switch (SDL_JoystickGetButton(joy,i)) {
              case SDL_PRESSED:
                window.draw(sprite_vector_button[i*2]);
                break;
              case SDL_RELEASED:
                window.draw(sprite_vector_button[i*2+1]);
                break;
            }

          }

          for (int i = 1; i < SDL_JoystickNumAxes(joy); i++) {
            if( SDL_JoystickGetAxis(joy,i) < 0){
              //sin apretar
                window.draw(sprite_vector_axis[i*2+1]);
            }else{
              //apretado
                window.draw(sprite_vector_axis[i*2]);
            }
          }

          for (int i = 0; i < SDL_JoystickNumHats(joy); i++) {
            window.draw(sprite_vector_hat[i*10+9]);
            switch (SDL_JoystickGetHat(joy,i)) {
              case SDL_HAT_LEFTUP:
                window.draw(sprite_vector_hat[i*10]);
                break;
              case SDL_HAT_UP:
                window.draw(sprite_vector_hat[i*10+1]);
                break;
              case SDL_HAT_RIGHTUP:
                window.draw(sprite_vector_hat[i*10+2]);
                break;
              case SDL_HAT_LEFT:
                window.draw(sprite_vector_hat[i*10+3]);
                break;
              case SDL_HAT_CENTERED:
                window.draw(sprite_vector_hat[i*10+4]);
                break;
              case SDL_HAT_RIGHT:
                window.draw(sprite_vector_hat[i*10+5]);
                break;
              case SDL_HAT_LEFTDOWN:
                window.draw(sprite_vector_hat[i*10+6]);
                break;
              case SDL_HAT_DOWN:
                window.draw(sprite_vector_hat[i*10+7]);
                break;
              case SDL_HAT_RIGHTDOWN:
                window.draw(sprite_vector_hat[i*10+8]);
                break;

            }
          }
        } else {
          printf("Couldn't open Joystick 0\n");
        }
        SDL_JoystickUpdate();
        // Close if opened

        sf::Event event;
        while (window.pollEvent(event)){
          if (event.type == sf::Event::Closed){
            if (SDL_JoystickGetAttached(joy)) {
              SDL_JoystickClose(joy);
            }
            window.close();
          }
        }

        window.display();
      }

    } else {
      printf("Couldn't open Joystick 0\n");
    }
  }

  return 0;
}
