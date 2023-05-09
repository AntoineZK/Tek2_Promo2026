/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-antoine.khalidy
** File description:
** IEnti
*/

#pragma once
#include <string>
#include <vector>
#include <memory>

namespace arcade {
    /**
     * @brief This class is used to store one entity of the map (a wall, a player, a monster, etc...)
     * It is used to display the game
     * For example one IEntity can be a wall, it will have a character (like a '#'), a color (like ARCADE_WHITE), a position (like 0, 0)
     * It can also have a filename (like "wall.png")
     */
    class IEntity {
        public:
            enum COLOR {ARCADE_BLACK, ARCADE_RED, ARCADE_GREEN, ARCADE_YELLOW, ARCADE_BLUE, ARCADE_MAGENTA, ARCADE_CYAN, ARCADE_WHITE};
            virtual ~IEntity() = default;
            virtual char getCharacter() const = 0;
            virtual std::string getFilename() const = 0;
            virtual COLOR getColorCharacter() const = 0;
            virtual COLOR getColorBackground() const = 0;
            virtual std::pair<int, int> getPos() const = 0;
            virtual int getAnimation() const = 0;
            virtual int getHaveChange() const = 0;

            virtual void setCharacter(char character) = 0;
            virtual void setHaveChange(int haveChange) = 0;
            virtual void setFilename(std::string filename) = 0;
            virtual void setAnimation(int animation) = 0;
            virtual void setPos(std::pair<int, int> pos) = 0;
            virtual void setColorCharacter(COLOR color) = 0;
            virtual void setColorBackground(COLOR color) = 0;
    };
}
