/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** Sfml
*/

#pragma once
#include <SFML/Graphics.hpp>
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/System.hpp"
#include "SFML/Main.hpp"
#include "../../Include/Include.hpp"

namespace RT {
  namespace Sfml {
      class sfml_class {
          public:
              sfml_class(int x_win, int y_win);
              sfml_class();
              ~sfml_class();
              void display(std::vector<std::vector<pixel_t>> &tab_vertex);
              bool getWindow();
              void event();
              void draw();
          protected:
          private:
              size_t i;
              sf::RenderWindow window;
              sf::Event _event;
              std::vector<std::vector<sf::Color>> _tab_vertex;
              std::vector<sf::Vertex> _vertex;
              sf::Vector2i _mouse_pos;
              sf::View _view;
              bool _mouse_pressed;
        };
    };
};
