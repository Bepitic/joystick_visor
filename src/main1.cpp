#include <SFML/Graphics.hpp>
#include <SFML/Window/Joystick.hpp>
#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <fstream>
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
  SDL_InitSubSystem(SDL_INIT_JOYSTICK);

  if (SDL_NumJoysticks() > 0) {
    joy = SDL_JoystickOpen(0);
    std::string line;

    if (joy) {
      std::ifstream f ( std::string(SDL_JoystickNameForIndex(0)) +".txt" );

      if (f.is_open()) {
        f >> j;
        std::cout << j << '\n';
        f.close();

      } else {
        std::cout <<  std::string(SDL_JoystickNameForIndex(0)) +".txt : Unable to open file, creating one.";

        //std::ofstream myfile (std::string(SDL_JoystickNameForIndex(0)) +".txt");


        for (int i = 0; i < SDL_JoystickNumButtons( joy); i++) {
          j["Button"][i]["x"] = 0.0;
          j["Button"][i]["y"] = 0.0;
          j["Button"][i]["scale"] = 1.0;
          j["Button"][i]["pathButtonPresed"] = "/resources/b"+ std::to_string(i) + "_pressed.png";
          j["Button"][i]["pathButtonReleased"] = "/resources/b"+ std::to_string(i) + "_released.png";
        }
        for (int i = 0; i < SDL_JoystickNumAxes( joy); i++) {
          myfile << std::string("A") << i << "|posx|posy|scale|button|pathButtonPressed" << std::endl;
          myfile << std::string("A") << i << "|posx|posy|scale|button|pathButtonReleased" << std::endl;
          j["Axis"][i]["x"] = 0.0;
          j["Axis"][i]["y"] = 0.0;
          j["Axis"][i]["scale"] = 1.0;
          j["Axis"][i]["isButton"] = true;
          j["Axis"][i]["isTrigger"] = false;
          j["Axis"][i]["pathButtonPresed"] = "/resources/b"+ std::to_string(i) + "_pressed.png";
          j["Axis"][i]["pathButtonReleased"] = "/resources/b"+ std::to_string(i) + "_released.png";
        }
        for (int i = 0; i < SDL_JoystickNumHats(joy); i++) {

          j["Hat"][i]["x"] = 0.0;
          j["Hat"][i]["y"] = 0.0;
          j["Hat"][i]["scale"] = 1.0;
          j["Hat"][i]["pathLEFTUP"] = "/resources/b"+ std::to_string(i) + "_LEFTUP.png";
          j["Hat"][i]["pathUP"] = "/resources/b"+ std::to_string(i) + "_UP.png";
          j["Hat"][i]["pathRIGHTUP"] = "/resources/b"+ std::to_string(i) + "_RIGHTUP.png";
          j["Hat"][i]["pathLEFT"] = "/resources/b"+ std::to_string(i) + "_LEFT.png";
          j["Hat"][i]["pathCENTERED"] = "/resources/b"+ std::to_string(i) + "_CENTERED.png";
          j["Hat"][i]["pathRIGHT"] = "/resources/b"+ std::to_string(i) + "_RIGHT.png";
          j["Hat"][i]["pathLEFTDOWN"] = "/resources/b"+ std::to_string(i) + "_LEFTDOWN.png";
          j["Hat"][i]["pathDOWN"] = "/resources/b"+ std::to_string(i) + "_DOWN.png";
          j["Hat"][i]["pathRIGHTDOWN"] = "/resources/b"+ std::to_string(i) + "_RIGHTDOWN.png";

        }
        std::ofstream f (std::string(SDL_JoystickNameForIndex(0)) +".txt");
        f << std::setw(4) << j << std::endl;
        f.close();
      }
    } else {
      printf("Couldn't open Joystick 0\n");
    }
  }
}
