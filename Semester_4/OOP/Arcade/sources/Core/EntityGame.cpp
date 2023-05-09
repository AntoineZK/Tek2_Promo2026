/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-antoine.khalidy
** File description:
** EntityGame
*/

#include "EntityGame.hpp"

arcade::EntityGame::EntityGame()
{
    this->character = ' ';
    this->filename = "";
    this->colorCharacter = arcade::IEntity::COLOR::ARCADE_WHITE;
    this->colorBackground = arcade::IEntity::COLOR::ARCADE_BLACK;
    this->pos = std::make_pair(0, 0);
    this->animation = 0;
    this->haveChange = 0;
}

arcade::EntityGame::EntityGame(char character, std::string filename, arcade::IEntity::COLOR colorCharacter, arcade::IEntity::COLOR colorBackground, std::pair<int, int> pos, int animation, int haveChange)
{
    this->character = character;
    std::ifstream file(filename);
    if (file.is_open()) {
        this->filename = filename;
    } else {
        this->filename = "";
    }
    this->colorCharacter = colorCharacter;
    this->colorBackground = colorBackground;
    this->pos = pos;
    this->animation = animation;
    this->haveChange = haveChange;
}

arcade::EntityGame::~EntityGame()
{
}

char arcade::EntityGame::getCharacter() const
{
    return this->character;
}

std::string arcade::EntityGame::getFilename() const
{
    return this->filename;
}

arcade::IEntity::COLOR arcade::EntityGame::getColorCharacter() const
{
    return this->colorCharacter;
}

arcade::IEntity::COLOR arcade::EntityGame::getColorBackground() const
{
    return this->colorBackground;
}

std::pair<int, int> arcade::EntityGame::getPos() const
{
    return this->pos;
}

int arcade::EntityGame::getAnimation() const
{
    return this->animation;
}

int arcade::EntityGame::getHaveChange() const
{
    return this->haveChange;
}

void arcade::EntityGame::setCharacter(char character)
{
    this->character = character;
}

void arcade::EntityGame::setHaveChange(int haveChange)
{
    this->haveChange = haveChange;
}

void arcade::EntityGame::setFilename(std::string filename)
{
    std::ifstream file(filename);
    if (file.is_open()) {
        this->filename = filename;
    } else {
        this->filename = "";
    }
}

void arcade::EntityGame::setAnimation(int animation)
{
    this->animation = animation;
}

void arcade::EntityGame::setColorCharacter(arcade::IEntity::COLOR color)
{
    this->colorCharacter = color;
}

void arcade::EntityGame::setPos(std::pair<int, int> pos)
{
    this->pos = pos;
}

void arcade::EntityGame::setColorBackground(arcade::IEntity::COLOR color)
{
    this->colorBackground = color;
}
