/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-antoine.khalidy
** File description:
** Pacman
*/

#include "Pacman.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <memory>


extern "C" std::unique_ptr<arcade::IGame> GameEntrypoint()
{
    return std::make_unique<arcade::Pacman>();
}

namespace arcade {
    Pacman::Pacman()
    {
        this->map = get_map("./map/pacman_map.txt");
        this->direction = 3;
        this->powerup = 0;
        this->nb_gums = 244;
        this->score = 0;
        this->move_time = 0;
        this->ghosts.resize(4);
        this->pacx = 14;
        this->pacy = 23;
        this->clock_pac_sprite = 0;
        for (int i = 0; i < 4; i++) {
            this->ghosts[i].stase = i * 10000;
            this->ghosts[i].direction = 2;
            this->ghosts[i].move_time = 600;
            this->ghosts[i].x = 10 + (2 * i);
            this->ghosts[i].y = 14;
            this->ghosts[i].stuck = 1;
            this->ghosts[i].memory = ' ';
        }
        this->ghosts[0].stuck = 0;
        this->ghosts[0].x = 14;
        this->ghosts[0].y = 11;
    }

    Pacman::~Pacman()
    {
    }

    std::vector<std::string> Pacman::get_map(std::string path)
    {
        std::ifstream file(path);
        std::string line;
        std::vector<std::string> map;

        if (!file.is_open())
            return map;
        while (getline(file, line))
            map.push_back(line);
        return map;
    }

    void Pacman::back_ghosts(int i, int64_t time)
    {
        this->ghosts[i].stase = time;
        this->ghosts[i].direction = 2;
        this->ghosts[i].move_time = 600;
        this->ghosts[i].stuck = 1;
        this->map[this->ghosts[i].y][this->ghosts[i].x] = this->ghosts[i].memory;
        this->ghosts[i].memory = ' ';
        this->ghosts[i].x = 10;
        this->ghosts[i].y = 14;
        if (i == 0) {
            this->ghosts[0].x = 14;
            this->ghosts[0].y = 11;
            this->ghosts[0].stuck = 0;
        }
        for (; this->map[this->ghosts[i].y][this->ghosts[i].x] != ' '; this->ghosts[i].x += 2);
        this->map[this->ghosts[i].y][this->ghosts[i].x] = 'G';
    }

    void Pacman::move(int input, Pacman &pac)
    {
        int x2 = 0;
        int y2 = 0;
        if (pac.powerup > 0)
            pac.powerup--;

        x2 = this->pacx;
        y2 = this->pacy;
        if (input == 4)
            x2++;
        if (input == 3)
            x2--;
        if (input == 2)
            y2++;
        if (input == 1)
            y2--;
        if (x2 < 0)
            x2 = 27;
        if (x2 > 27)
            x2 = 0;

        if (pac.map[y2][x2] == '*' || pac.map[y2][x2] == ' ' || pac.map[y2][x2] == '0' || pac.map[y2][x2] == 'G') {
            if (pac.map[y2][x2] == '*') {
                pac.score += 10;
                pac.nb_gums--;
            }
            if (pac.map[y2][x2] == '0') {
                pac.score += 50;
                pac.powerup = 20;
                pac.nb_gums--;
            }
            pac.map[this->pacy][this->pacx] = ' ';
            pac.map[y2][x2] = 'P';
            this->pacy = y2;
            this->pacx = x2;
        }
    }

    void ghost_move(Pacman &pac, int gn)
    {
        int nb_pos = 0;
        char charac = ' ';
        std::vector<int> posx;
        std::vector<int> posy;
        std::vector<int> dir;
        posx.resize(3);
        posy.resize(3);
        dir.resize(3);
        if (pac.ghosts[gn].direction != 1) {
            charac = pac.map[pac.ghosts[gn].y + 1][pac.ghosts[gn].x];
            if (charac == ' ' || charac == 'P' || charac == '0' || charac == '*')  {
                posx[nb_pos] = pac.ghosts[gn].x;
                posy[nb_pos] = pac.ghosts[gn].y + 1;
                dir[nb_pos] = 2;
                nb_pos++;
            }
        }
        if (pac.ghosts[gn].direction != 2) {
            charac = pac.map[pac.ghosts[gn].y - 1][pac.ghosts[gn].x];
            if (charac == ' ' || charac == 'P' || charac == '0' || charac == '*') {
                posx[nb_pos] = pac.ghosts[gn].x;
                posy[nb_pos] = pac.ghosts[gn].y - 1;
                dir[nb_pos] = 1;
                nb_pos++;
            }
        }
        if (pac.ghosts[gn].direction != 3) {
            if (pac.ghosts[gn].x == 27) {
                charac = pac.map[pac.ghosts[gn].y][0];
                if (charac == ' ' || charac == 'P' || charac == '0' || charac == '*') {
                    posx[nb_pos] = 0;
                    posy[nb_pos] = pac.ghosts[gn].y;
                    dir[nb_pos] = 4;
                    nb_pos++;
                }
            } else {
                charac = pac.map[pac.ghosts[gn].y][pac.ghosts[gn].x + 1];
                if (charac == ' ' || charac == 'P' || charac == '0' || charac == '*') {
                    posx[nb_pos] = pac.ghosts[gn].x + 1;
                    posy[nb_pos] = pac.ghosts[gn].y;
                    dir[nb_pos] = 4;
                    nb_pos++;
                }
            }
        }
        if (pac.ghosts[gn].direction != 4) {
            if (pac.ghosts[gn].x == 0) {
                charac = pac.map[pac.ghosts[gn].y][27];
                if (charac == ' ' || charac == 'P' || charac == '0' || charac == '*') {
                    posx[nb_pos] = 27;
                    posy[nb_pos] = pac.ghosts[gn].y;
                    dir[nb_pos] = 3;
                    nb_pos++;
                }
            } else {
                charac = pac.map[pac.ghosts[gn].y][pac.ghosts[gn].x - 1];
                if (charac == ' ' || charac == 'P' || charac == '0' || charac == '*') {
                    posx[nb_pos] = pac.ghosts[gn].x - 1;
                    posy[nb_pos] = pac.ghosts[gn].y;
                    dir[nb_pos] = 3;
                    nb_pos++;
                }
            }
        }
        if (nb_pos == 0) {
            pac.ghosts[gn].direction = rand() % 4 + 1;
            return;
        }
        std::srand(std::time(nullptr));
        int r = rand() % nb_pos;
        pac.map[pac.ghosts[gn].y][pac.ghosts[gn].x] = pac.ghosts[gn].memory;
        pac.ghosts[gn].y = posy[r];
        pac.ghosts[gn].x = posx[r];
        pac.ghosts[gn].direction = dir[r];
        pac.ghosts[gn].memory = pac.map[pac.ghosts[gn].y][pac.ghosts[gn].x];
        pac.map[pac.ghosts[gn].y][pac.ghosts[gn].x] = 'G';
    }

    void Pacman::gcollision(int i, int64_t time)
    {
        if (this->powerup > 0) {
            this->ghosts[i].time_stock = time;
            this->back_ghosts(i, 10000);
            this->map[this->ghosts[i].y][this->ghosts[i].x] = '"';
            this->score += 200;
        } else {
            this->life--;
            for (int i = 0; i < 4; i++) {
                this->back_ghosts(i, i * 10000);
                this->ghosts[i].time_stock = time;
            }
            this->map[this->pacy][this->pacx] = ' ';
            this->pacx = 14;
            this->pacy = 23;
            this->map[this->pacy][this->pacx] = 'P';
        }
    }

    void ghost_action(Pacman &pac, int64_t time)
    {
        for (int i = 0; i < 4; i++) {
            if (pac.ghosts[i].stuck == 1) {
                if (time - pac.ghosts[i].time_stock > pac.ghosts[i].stase) {
                    pac.ghosts[i].stuck = 0;
                    pac.ghosts[i].time_stock = time;
                    pac.map[pac.ghosts[i].y][pac.ghosts[i].x] = ' ';
                    pac.ghosts[i].x = 14;
                    pac.ghosts[i].y = 11;
                    pac.map[pac.ghosts[i].y][pac.ghosts[i].x] = 'G';
                }
            } else {
                if (time - pac.ghosts[i].time_stock >= pac.ghosts[i].move_time) {
                    if (pac.map[pac.ghosts[i].y][pac.ghosts[i].x] == 'P')
                        pac.gcollision(i, time);
                    ghost_move(pac, i);
                    if (pac.ghosts[i].memory == 'P')
                        pac.gcollision(i, time);
                    pac.ghosts[i].time_stock = time;
                }
            }
        }
    }

    EntityGame Pacman::add_color(char c, int x, int y)
    {
        EntityGame tmp;
        tmp.setCharacter(c);
        if (c == 'P') {
            tmp.setColorCharacter(IEntity::COLOR::ARCADE_YELLOW);
            if (this->direction == 1 && this->clock_pac_sprite != 1)
                tmp.setFilename("assets/Pacman/pac_haut_1.png");
            else if (this->direction == 2 && this->clock_pac_sprite != 1)
                tmp.setFilename("assets/Pacman/pac_bas.png");
            else if (this->direction == 3 && this->clock_pac_sprite != 1)
                tmp.setFilename("assets/Pacman/pac_gauche.png");
            else if (this->direction == 4 && this->clock_pac_sprite != 1)
                tmp.setFilename("assets/Pacman/pac_droite.png");
            else
                tmp.setFilename("assets/Pacman/full.png");
        } else if (c == '|' || c == '-' || c == '_') {
            tmp.setColorCharacter(IEntity::COLOR::ARCADE_BLUE);
            tmp.setFilename("assets/Pacman/mur.png");
        } else if (c == '0') {
            tmp.setColorCharacter(IEntity::COLOR::ARCADE_RED);
            tmp.setFilename("assets/Pacman/big.png");
        } else if (c == '*') {
            tmp.setColorCharacter(IEntity::COLOR::ARCADE_GREEN);
            tmp.setFilename("assets/Pacman/piece.png");
        } else if (c == ' ') {
            tmp.setColorCharacter(IEntity::COLOR::ARCADE_BLACK);
            tmp.setFilename("assets/Pacman/vide.png");
        } else if (c == '"') {
            tmp.setColorCharacter(IEntity::COLOR::ARCADE_WHITE);
            tmp.setFilename("assets/Pacman/dead.png");
        } else if (c == 'G') {
            if (this->powerup > 0) {
                tmp.setColorCharacter(IEntity::COLOR::ARCADE_MAGENTA);
                tmp.setFilename("assets/Pacman/ghost_flip.png");
            } else {
                tmp.setColorCharacter(IEntity::COLOR::ARCADE_CYAN);
                tmp.setFilename("assets/Pacman/ghost.png");
            }
        }
        tmp.setPos({x, y});
        tmp.setColorBackground(IEntity::COLOR::ARCADE_BLACK);
        tmp.setAnimation(0);
        tmp.setHaveChange(0);
        return tmp;
    }

    void Pacman::reset()
    {
        this->score += 10000;
        this->level++;
        this->map = get_map("./map/pacman_map.txt");
        this->direction = 3;
        this->powerup = 0;
        this->nb_gums = 244;
        this->move_time = 0;
        this->ghosts.resize(4);
        this->pacx = 14;
        this->pacy = 23;
        for (int i = 0; i < 4; i++) {
            this->ghosts[i].stase = i * 10000;
            this->ghosts[i].direction = 2;
            this->ghosts[i].move_time = 630 - (this->level * 30);
            this->ghosts[i].x = 10 + (2 * i);
            this->ghosts[i].y = 14;
            this->ghosts[i].stuck = 1;
            this->ghosts[i].memory = ' ';
        }
        this->ghosts[0].stuck = 0;
        this->ghosts[0].x = 14;
        this->ghosts[0].y = 11;
    }

    int Pacman::manage(std::vector<int> inputs, std::shared_ptr<IData> data, CURRENT_TIME oldTime)
    {
        this->_currentTime = std::chrono::steady_clock::now();
        this->elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(this->_currentTime - oldTime).count();
        if (this->move_time == 0) {
            this->move_time = this->elapsed_time;
            for (int i = 0; i < 4; i++)
                this->ghosts[i].time_stock = this->elapsed_time;
        }
        for (auto input : inputs) {
            if (input == 'z' || input == 'Z')
                this->direction = 1;
            if (input == 's' || input == 'S')
                this->direction = 2;
            if (input == 'q' || input == 'Q')
                this->direction = 3;
            if (input == 'd' || input == 'D')
                this->direction = 4;
        }

        if (this->elapsed_time - this->move_time >= 200) {
            move(this->direction, *this);
            this->move_time = this->elapsed_time;
            if (this->clock_pac_sprite == 0)
                this->clock_pac_sprite = 1;
            else
                this->clock_pac_sprite = 0;
        }
        ghost_action(*this, this->elapsed_time);
        std::vector<std::vector<EntityGame>> entities;
        for (std::size_t i = 0; i < this->map.size(); i++) {
            std::vector<EntityGame> entity;
            for (std::size_t j = 0; j < this->map[i].size(); j++) {
                entity.push_back(add_color(this->map[i][j], j * 33, i * 33));
            }
            entities.push_back(entity);
        }
        if (data->getMapSize().first != (int) entities.size() || data->getMapSize().second != (int) entities[0].size())
            data->setMapSize({entities.size(), entities[0].size()});
        for (std::size_t i = 0; i < entities.size(); i++) {
            for (std::size_t j = 0; j < entities[i].size(); j++) {
                data->setEntityAt({i, j}, entities[i][j]);
            }
        }
        data->setScore(this->score);
        data->setLives(this->life);
        data->setLevel(this->level);
        if (this->nb_gums == 0)
            this->reset();
        return (0);
    }
}

std::string arcade::Pacman::getMusic() const
{
    return "./assets/Pacman/Pac-man-theme-remix-By-Arsenic1987.ogg";
}
