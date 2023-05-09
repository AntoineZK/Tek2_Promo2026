/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-antoine.khalidy
** File description:
** SDL2
*/

#pragma once
// Standard includes
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <map>

// Project includes
#include "../../Interface/IGraphical.hpp"

namespace arcade {
    class SDL2 : public IGraphical {
        public:
            SDL2();
            ~SDL2();
            std::vector<int> getInputs();
            void display(std::shared_ptr<IData>);
            void createText(std::string, SDL_Color, SDL_Rect);
        private:
            SDL_Window *window;
            SDL_Renderer *renderer;
            SDL_Event event;
            TTF_Font *font;
            std::map<IEntity::COLOR, std::tuple<int, int, int, int>> colorMap = {
                {IEntity::COLOR::ARCADE_BLACK, {0, 0, 0, 255}},
                {IEntity::COLOR::ARCADE_WHITE, {255, 255, 255, 255}},
                {IEntity::COLOR::ARCADE_RED, {255, 0, 0, 255}},
                {IEntity::COLOR::ARCADE_GREEN, {0, 255, 0, 255}},
                {IEntity::COLOR::ARCADE_BLUE, {0, 0, 255, 255}},
                {IEntity::COLOR::ARCADE_YELLOW, {255, 255, 0, 255}},
                {IEntity::COLOR::ARCADE_MAGENTA, {255, 0, 255, 255}},
                {IEntity::COLOR::ARCADE_CYAN, {0, 255, 255, 255}},
            };
    };
}