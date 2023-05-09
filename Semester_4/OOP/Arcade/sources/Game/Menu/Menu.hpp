/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-antoine.khalidy
** File description:
** Menu
*/

#pragma once
// Project includes
#include "../../Interface/IGame.hpp"
#include "../../Core/Core.hpp"

namespace arcade {
    class Menu : public IGame {
        public:
            Menu();
            ~Menu();
            int manage(std::vector<int> inputs, std::shared_ptr<IData>, CURRENT_TIME);
            std::string getMusic() const;
            std::string removeExtension(std::string filename);
            std::string getAfterLastUnderscore(std::string filename);
            std::tuple<int, int> getSpaceLeftRight(std::string str);
            std::vector<EntityGame> placeCenter(std::string str, IEntity::COLOR color, int y);
            std::vector<EntityGame> placeLeft(std::string str, IEntity::COLOR color, int y);
            std::vector<EntityGame> placeRight(std::string str, IEntity::COLOR color, int y);
            void loadLibs();
            std::vector<std::string> getLibs();
            void updateVector(void);
            void updateData(std::shared_ptr<IData> data);
            void createMenuVisual(void);

        private:
            int score;
            std::vector<std::vector<EntityGame>> menuInterface;
            std::vector<std::string> gameLibs;
            std::vector<std::string> audioLibs;
            std::vector<std::string> graphicalLibs;
            int selectedGame;
    };
}
