/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-antoine.khalidy
** File description:
** SDL2
*/

#include "SDL2.hpp"

extern "C" std::unique_ptr<arcade::IGraphical> GraphEntrypoint()
{
    return std::make_unique<arcade::SDL2>();
}

arcade::SDL2::SDL2()
{
    SDL_Init(SDL_INIT_VIDEO);
    this->window = SDL_CreateWindow("Arcade SDL", 0, 0, 1920, 1080, SDL_WINDOW_SHOWN);
    this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Rect viewport = {0, 0, 1920, 1080};
    SDL_RenderSetViewport(renderer, &viewport);
    TTF_Init();
    this->font = TTF_OpenFont("assets/arial.ttf", 24);
}

arcade::SDL2::~SDL2()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

std::vector<int> arcade::SDL2::getInputs()
{
    std::vector<int> inputs;

    while (SDL_PollEvent(&this->event)) {
        if (this->event.type == SDL_KEYDOWN)
            inputs.push_back(this->event.key.keysym.sym);
    }
    return inputs;
}

void arcade::SDL2::createText(std::string str, SDL_Color color, SDL_Rect rect)
{
    SDL_Surface *surface = TTF_RenderText_Solid(this->font, str.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(this->renderer, surface);
    SDL_FreeSurface(surface);
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(this->renderer, &rect);
    SDL_RenderCopy(this->renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}

void arcade::SDL2::display(std::shared_ptr<IData> data)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    std::string score = "Score: " + std::to_string(data->getScore());
    std::string level = "Level: " + std::to_string(data->getLevel());
    std::string lives = "Lives: " + std::to_string(data->getLives());
    this->createText(score, {255, 0, 0, 255}, {1400, 0, 200, 100});
    this->createText(level, {0, 0, 255, 255}, {1400, 100, 200, 100});
    this->createText(lives, {0, 255, 0, 255}, {1400, 200, 200, 100});
    std::pair<std::size_t, std::size_t> mapSize = data->getMapSize();
    for (std::size_t i = 0; i < mapSize.first; i++) {
        for (std::size_t j = 0; j < mapSize.second; j++) {
            SDL_Rect rect = {static_cast<int>(j * 30), static_cast<int>(i * 30), 30, 30};
            SDL_Texture *texture = NULL;
            IEntity& entity = data->getEntities(i, j);
            if (entity.getFilename() != "") {
                texture = IMG_LoadTexture(renderer, entity.getFilename().c_str());
                SDL_RenderCopy(renderer, texture, NULL, &rect);
                SDL_DestroyTexture(texture);
            } else {
                IEntity::COLOR colorCharacter = entity.getColorCharacter();
                IEntity::COLOR colorBackground = entity.getColorBackground();
                SDL_Color color = {static_cast<Uint8>(std::get<0>(colorMap[colorCharacter])), static_cast<Uint8>(std::get<1>(colorMap[colorCharacter])), static_cast<Uint8>(std::get<2>(colorMap[colorCharacter])), static_cast<Uint8>(std::get<3>(colorMap[colorCharacter]))};
                char text[] = {entity.getCharacter(), '\0'};
                SDL_Surface* surface = TTF_RenderText_Solid(this->font, text, color);
                texture = SDL_CreateTextureFromSurface(renderer, surface);
                SDL_FreeSurface(surface);
                SDL_SetRenderDrawColor(renderer, std::get<0>(colorMap[colorBackground]), std::get<1>(colorMap[colorBackground]), std::get<2>(colorMap[colorBackground]), std::get<3>(colorMap[colorBackground]));
                SDL_RenderFillRect(renderer, &rect);
                SDL_RenderCopy(renderer, texture, NULL, &rect);
                SDL_DestroyTexture(texture);
            }
        }
    }
    SDL_RenderPresent(renderer);
}
