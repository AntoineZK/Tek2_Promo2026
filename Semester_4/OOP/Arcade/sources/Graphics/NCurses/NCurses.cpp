/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-antoine.khalidy
** File description:
** NCurses
*/

#include "NCurses.hpp"

extern "C" std::unique_ptr<arcade::IGraphical> GraphEntrypoint()
{
    return std::make_unique<arcade::NCurses>();
}

arcade::NCurses::NCurses()
{
    savetty();
    SCREEN *win = newterm(NULL, stdout, stdin);
    set_term(win);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);
    noecho();
    start_color();
}

arcade::NCurses::~NCurses()
{
    resetty();
    endwin();
}

std::vector<int> arcade::NCurses::getInputs()
{
    std::vector<int> inputs;
    timeout(100);
    int c = getch();
    inputs.push_back(c);
    return inputs;
}

void arcade::NCurses::display(std::shared_ptr<IData> data)
{
    clear();
    mvprintw(0, 45, "Score: %d", data->getScore());
    mvprintw(5, 45, "Lives: %d", data->getLives());
    mvprintw(10, 45, "Level: %d", data->getLevel());
    std::pair<std::size_t, std::size_t> mapSize = data->getMapSize();
    std::size_t pairIndex = 1;

    for (std::size_t i = 0; i < mapSize.first; i++) {
        for (std::size_t j = 0; j < mapSize.second; j++) {
            IEntity &entity = data->getEntities(i, j);
            arcade::IEntity::COLOR colorCharacter = entity.getColorCharacter();
            arcade::IEntity::COLOR colorBackground = entity.getColorBackground();
            std::pair<IEntity::COLOR, IEntity::COLOR> color = std::make_pair(colorCharacter, colorBackground);
            auto it = this->colorMap.find(color);
            int colorPair = 0;
            if (it != this->colorMap.end()) {
                colorPair = it->second;
            } else {
                init_pair(pairIndex, colorCharacter, colorBackground);
                this->colorMap.insert(std::make_pair(color, pairIndex));
                colorPair = pairIndex;
                pairIndex++;
            }
            attron(COLOR_PAIR(colorPair));
            mvprintw(i, j, "%c", entity.getCharacter());
            attroff(COLOR_PAIR(colorPair));
        }
    }
    refresh();
}
