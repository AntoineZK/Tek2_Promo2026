/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-antoine.khalidy
** File description:
** SFML
*/

#pragma once
// Standard includes
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

// Project includes
#include "../../Interface/IGraphical.hpp"

namespace arcade {
    class SFML : public IGraphical {
        public:
            SFML();
            ~SFML();
            std::vector<int> getInputs();
            void display(std::shared_ptr<IData>);
            sf::Text createText(std::string text, int size, sf::Color color, std::pair<int, int> pos);
        private:
            sf::RenderWindow window;
            sf::Event event;
            sf::Text scoreText;
            sf::Text scoreValue;
            sf::Text livesText;
            sf::Text livesValue;
            sf::Text levelText;
            sf::Text levelValue;
            sf::Font font;
            sf::View view;
            std::map<sf::Keyboard::Key, int> keyMap = {
                {sf::Keyboard::Key::A, 97},
                {sf::Keyboard::Key::B, 98},
                {sf::Keyboard::Key::C, 99},
                {sf::Keyboard::Key::D, 100},
                {sf::Keyboard::Key::E, 101},
                {sf::Keyboard::Key::F, 102},
                {sf::Keyboard::Key::G, 103},
                {sf::Keyboard::Key::H, 104},
                {sf::Keyboard::Key::I, 105},
                {sf::Keyboard::Key::J, 106},
                {sf::Keyboard::Key::K, 107},
                {sf::Keyboard::Key::L, 108},
                {sf::Keyboard::Key::M, 109},
                {sf::Keyboard::Key::N, 110},
                {sf::Keyboard::Key::O, 111},
                {sf::Keyboard::Key::P, 112},
                {sf::Keyboard::Key::Q, 113},
                {sf::Keyboard::Key::R, 114},
                {sf::Keyboard::Key::S, 115},
                {sf::Keyboard::Key::T, 116},
                {sf::Keyboard::Key::U, 117},
                {sf::Keyboard::Key::V, 118},
                {sf::Keyboard::Key::W, 119},
                {sf::Keyboard::Key::X, 120},
                {sf::Keyboard::Key::Y, 121},
                {sf::Keyboard::Key::Z, 122},
                {sf::Keyboard::Key::Num0, 48},
                {sf::Keyboard::Key::Num1, 49},
                {sf::Keyboard::Key::Num2, 50},
                {sf::Keyboard::Key::Num3, 51},
                {sf::Keyboard::Key::Num4, 52},
                {sf::Keyboard::Key::Num5, 53},
                {sf::Keyboard::Key::Num6, 54},
                {sf::Keyboard::Key::Num7, 55},
                {sf::Keyboard::Key::Num8, 56},
                {sf::Keyboard::Key::Num9, 57},
                {sf::Keyboard::Key::Escape, 27},
                {sf::Keyboard::Key::Enter, 10},
                {sf::Keyboard::Key::Space, 32},
            };
            std::map<IEntity::COLOR, sf::Color> colorMap = {
                {IEntity::COLOR::ARCADE_BLACK, sf::Color::Black},
                {IEntity::COLOR::ARCADE_BLUE, sf::Color::Blue},
                {IEntity::COLOR::ARCADE_CYAN, sf::Color::Cyan},
                {IEntity::COLOR::ARCADE_GREEN, sf::Color::Green},
                {IEntity::COLOR::ARCADE_MAGENTA, sf::Color::Magenta},
                {IEntity::COLOR::ARCADE_RED, sf::Color::Red},
                {IEntity::COLOR::ARCADE_WHITE, sf::Color::White},
                {IEntity::COLOR::ARCADE_YELLOW, sf::Color::Yellow}
            };
    };
}
