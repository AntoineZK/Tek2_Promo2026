/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-antoine.khalidy
** File description:
** DataGame
*/

#include "DataGame.hpp"

arcade::DataGame::DataGame()
{
    this->score = 0;
    this->lives = -1;
    this->level = 0;
    this->username = "";
    this->entities.resize(5);
    for (int i = 0; i < 5; i++)
        this->entities[i].resize(5);
}

arcade::DataGame::~DataGame()
{
}

int arcade::DataGame::getScore() const
{
    return this->score;
}

int arcade::DataGame::getLives() const
{
    return this->lives;
}

int arcade::DataGame::getLevel() const
{
    return this->level;
}

std::string arcade::DataGame::getUsername() const
{
    return this->username;
}

arcade::IEntity& arcade::DataGame::getEntities(int x, int y)
{
    return this->entities[x][y];
}

std::pair<int, int> arcade::DataGame::getMapSize()
{
    if (entities.size() == 0)
        printf("map size is 0\n");
    else
        return std::make_pair(entities.size(), entities[0].size());
    return (std::make_pair(0, 0));
}

void arcade::DataGame::setScore(int score)
{
    this->score = score;
}

void arcade::DataGame::setLives(int lives)
{
    this->lives = lives;
}

void arcade::DataGame::setLevel(int level)
{
    this->level = level;
}

void arcade::DataGame::setUsername(std::string username)
{
    this->username = username;
}

void arcade::DataGame::setMapSize(std::pair<int, int> size)
{
    entities.resize(size.first);
    for (int i = 0; i < size.first; i++)
        entities[i].resize(size.second);
}

void arcade::DataGame::setEntityAt(std::pair<int, int> pos, EntityGame &entity)
{
    this->entities[pos.first][pos.second] = entity;
}
