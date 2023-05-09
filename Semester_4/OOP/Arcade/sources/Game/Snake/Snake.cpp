/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-antoine.khalidy
** File description:
** Snake
*/

#include "Snake.hpp"
#include <unistd.h>
#include <ncurses.h>

extern "C" std::unique_ptr<arcade::IGame> GameEntrypoint()
{
    return std::make_unique<arcade::Snake>();
}

arcade::Snake::Snake()
{
    this->score = 0;
    this->life = 1;
    this->direction = 1;
    this->snake_length = 3;
    this->move_time = 0;
    this->speed = 150;
    this->tmp_speed = -1;
    this->palier = 0;

    this->path_corps = "assets/Snake/snake_corps.png";
    this->path_haut = "assets/Snake/head_haut.png";
    this->path_bas = "assets/Snake/head_bas.png";
    this->path_droite = "assets/Snake/head_droite.png";
    this->path_gauche = "assets/Snake/head_gauche.png";

    for (int i = 0; i < 1; i++) {
        std::vector<EntityGame> line;
        for (int j = 0; j < 20; j++) {
            EntityGame entity('*', "assets/Snake/rocher.png", IEntity::COLOR::ARCADE_BLUE, IEntity::COLOR::ARCADE_BLACK, std::make_pair(j * 33, i * 33), 0, 0);
            line.push_back(entity);
        }
        this->map.push_back(line);
    }
    for (int i = 0; i < 20; i++) {
        std::vector<EntityGame> line;
        for (int j = 0; j < 20; j++) {
            if (j == 0 || j == 19) {
                EntityGame entity('*', "assets/Snake/rocher.png", IEntity::COLOR::ARCADE_BLUE, IEntity::COLOR::ARCADE_BLACK, std::make_pair(j * 33, (i + 1) * 33), 0, 0);
                line.push_back(entity);
            } else if (i == 10 && j == 10) {
                EntityGame entity('O', "assets/Snake/head_haut.png", IEntity::COLOR::ARCADE_YELLOW, IEntity::COLOR::ARCADE_BLACK, std::make_pair(j * 33, (i + 1) * 33), 0, 0);
                line.push_back(entity);
            } else {
                EntityGame entity('.', "assets/Snake/background.png", IEntity::COLOR::ARCADE_BLACK, IEntity::COLOR::ARCADE_BLACK, std::make_pair(j * 33, (i + 1) * 33), 0, 0);
                line.push_back(entity);
            }
        }
        this->map.push_back(line);
    }

    for (int i = 0; i < 1; i++) {
        std::vector<EntityGame> line;
        for (int j = 0; j < 20; j++) {
            EntityGame entity('*', "assets/Snake/rocher.png", IEntity::COLOR::ARCADE_BLUE, IEntity::COLOR::ARCADE_BLACK, std::make_pair(j * 33, (i + 21) * 33), 0, 0);
            line.push_back(entity);
        }
        this->map.push_back(line);
    }

    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            if (this->map[i][j].getCharacter() == 'O') {
                this->snake.push_back(std::make_tuple(i, j));
                break;
            }
        }
    }
}

arcade::Snake::~Snake()
{
}

void arcade::Snake::create_fruit()
{
    int x = rand() % 18 + 1;
    int y = rand() % 18 + 1;

    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            if (this->map[i][j].getCharacter() == 'F') {
                return;
            }
        }
    }

    for (auto it = this->snake.begin(); it != this->snake.end(); it++) {
        if (std::get<0>(*it) == x && std::get<1>(*it) == y) {
            this->create_fruit();
            return;
        }
    }

    this->map[x][y].setCharacter('F');
    this->map[x][y].setFilename("assets/Snake/fruit.png");
    this->map[x][y].setColorCharacter(IEntity::COLOR::ARCADE_RED);
    this->map[x][y].setColorBackground(IEntity::COLOR::ARCADE_BLACK);
    this->map[x][y].setPos({y* 33, x * 33});
    this->map[x][y].setAnimation(0);
    this->map[x][y].setHaveChange(0);


    this->tmp_speed += 1;

    this->score += 1;
    this->snake_length += 1;
}

int arcade::Snake::manage(std::vector<int> inputs, std::shared_ptr<IData> data, CURRENT_TIME oldTime)
{
    data->setLives(this->life);
    this->_currentTime = std::chrono::steady_clock::now();
    this->elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(this->_currentTime - oldTime).count();

    for (auto input : inputs) {
        if (input == 'z' || input == 'Z') {
            if (this->direction != 2)
                this->direction = 1;
        }
        if (input == 's' || input == 'S') {
            if (this->direction != 1)
                this->direction = 2;
        }
        if (input == 'q' || input == 'Q') {
            if (this->direction != 4)
                this->direction = 3;
        }
        if (input == 'd' || input == 'D') {
            if (this->direction != 3)
                this->direction = 4;
        }
    }

    if (this->palier >= 5) {
        this->path_bas = "assets/Snake/bas_vener.png";
        this->path_haut = "assets/Snake/haut_vener.png";
        this->path_droite = "assets/Snake/droite_vener.png";
        this->path_gauche = "assets/Snake/gauche_vener.png";
        this->path_corps = "assets/Snake/corps_vener.png";
    }

    if (tmp_speed == 5) {
        this->palier += 1;
        this->speed -= 20;
        this->tmp_speed = 0;
    }

    if (this->elapsed_time - this->move_time >= this->speed) {

        if ((std::get<0>(this->snake[0]) == 1 && this->direction == 1) || (std::get<0>(this->snake[0]) == 20 && this->direction == 2) || (std::get<1>(this->snake[0]) == 1 && this->direction == 3) || (std::get<1>(this->snake[0]) == 18 && this->direction == 4)) {
            game_over(data);
            return (0);
        }

        if (move(this->direction) == 1) {
            game_over(data);
            return (0);
        }
        update_snake();
        create_fruit();
        this->move_time = this->elapsed_time;
    }

    if (data->getMapSize().first != (int) map.size() || data->getMapSize().second != (int) map[0].size())
        data->setMapSize({map.size(), map[0].size()});
    for (std::size_t i = 0; i < map.size(); i++) {
        for (std::size_t j = 0; j < map[i].size(); j++) {
            data->setEntityAt({i, j}, map[i][j]);
        }
    }

    data->setScore(this->score - 1);
    data->setLevel(this->palier);
    data->setLives(this->life);
    return (0);
}

bool arcade::Snake::game_over(std::shared_ptr<IData> data)
{
    data->setLives(0);
    printf("Game Over\n");
    return (true);
}

void arcade::Snake::update_snake()
{
    int tmp_size = 0;
    for (int i = 0; i < 21; i++) {
        for (int j = 0; j < 20; j++) {
            if (this->map[i][j].getCharacter() == 'O') {
                tmp_size += 1;
            }
        }
    }

    if (tmp_size > this->snake_length) {
        int y = std::get<0>(this->snake.back());
        int x = std::get<1>(this->snake.back());
        this->map[y][x].setCharacter('.');
        this->map[y][x].setFilename("assets/Snake/background.png");
        this->map[y][x].setColorCharacter(IEntity::COLOR::ARCADE_BLACK);
        this->map[y][x].setColorBackground(IEntity::COLOR::ARCADE_BLACK);
        this->map[y][x].setAnimation(0);
        this->map[y][x].setHaveChange(0);
        this->map[y][x].setPos({x * 33, y * 33});
        if (this->snake.size() > 1)
            this->snake.pop_back();
    }

    if (this->direction == 1) {
        this->map[std::get<0>(this->snake.front())][std::get<1>(this->snake.front())].setFilename(this->path_haut);
        this->map[std::get<0>(this->snake.front())][std::get<1>(this->snake.front())].setCharacter('A');
    } else if (this->direction == 2) {
        this->map[std::get<0>(this->snake.front())][std::get<1>(this->snake.front())].setFilename(this->path_bas);
        this->map[std::get<0>(this->snake.front())][std::get<1>(this->snake.front())].setCharacter('A');
    } else if (this->direction == 3) {
        this->map[std::get<0>(this->snake.front())][std::get<1>(this->snake.front())].setFilename(this->path_gauche);
        this->map[std::get<0>(this->snake.front())][std::get<1>(this->snake.front())].setCharacter('A');
    } else if (this->direction == 4) {
        this->map[std::get<0>(this->snake.front())][std::get<1>(this->snake.front())].setFilename(this->path_droite);
        this->map[std::get<0>(this->snake.front())][std::get<1>(this->snake.front())].setCharacter('A');
    }

}

int arcade::Snake::move(int input)
{
    if (input == 1) {
        //check if snake eat his tail
        for (size_t i = 1; i < this->snake.size(); i++) {
            if (std::get<0>(this->snake[0]) - 1 == std::get<0>(this->snake[i]) && std::get<1>(this->snake[0]) == std::get<1>(this->snake[i])) {
                return (1);
            }
        }
        int y1 = std::get<0>(this->snake.front());
        int x1 = std::get<1>(this->snake.front());
        int y2 = std::get<0>(this->snake.front()) - 1;
        this->snake.insert(this->snake.begin() + 1, std::make_tuple(y1, x1));
        this->map[y1][x1].setCharacter('O');
        this->map[y1][x1].setFilename(this->path_corps);
        this->map[y1][x1].setColorCharacter(IEntity::COLOR::ARCADE_BLUE);
        this->map[y1][x1].setColorBackground(IEntity::COLOR::ARCADE_BLACK);
        this->map[y1][x1].setAnimation(0);
        this->map[y1][x1].setHaveChange(0);
        this->map[y1][x1].setPos({x1 * 33, y1 * 33});
        this->map[y2][x1].setCharacter('O');
        this->map[y2][x1].setFilename(this->path_corps);
        this->map[y2][x1].setColorCharacter(IEntity::COLOR::ARCADE_BLUE);
        this->map[y2][x1].setColorBackground(IEntity::COLOR::ARCADE_BLACK);
        this->map[y2][x1].setAnimation(0);
        this->map[y2][x1].setHaveChange(0);
        this->map[y2][x1].setPos({x1 * 33, y2 * 33});
        this->snake.front() = std::make_tuple(y2, x1);
    }

    if (input == 2) {
        //check if snake eat his tail
        for (size_t i = 1; i < this->snake.size(); i++) {
            if (std::get<0>(this->snake[0]) + 1 == std::get<0>(this->snake[i]) && std::get<1>(this->snake[0]) == std::get<1>(this->snake[i])) {
                return (1);
            }
        }
        int y1 = std::get<0>(this->snake.front());
        int x1 = std::get<1>(this->snake.front());
        int y2 = std::get<0>(this->snake.front()) + 1;

        this->snake.insert(this->snake.begin() + 1, std::make_tuple(y1, x1));
        this->map[y1][x1].setCharacter('O');
        this->map[y1][x1].setFilename(this->path_corps);
        this->map[y1][x1].setColorCharacter(IEntity::COLOR::ARCADE_BLUE);
        this->map[y1][x1].setColorBackground(IEntity::COLOR::ARCADE_BLACK);
        this->map[y1][x1].setAnimation(0);
        this->map[y1][x1].setHaveChange(0);
        this->map[y1][x1].setPos({x1 * 33, y1 * 33});
        this->map[y2][x1].setCharacter('O');
        this->map[y2][x1].setFilename(this->path_corps);
        this->map[y2][x1].setColorCharacter(IEntity::COLOR::ARCADE_BLUE);
        this->map[y2][x1].setColorBackground(IEntity::COLOR::ARCADE_BLACK);
        this->map[y2][x1].setAnimation(0);
        this->map[y2][x1].setHaveChange(0);
        this->map[y2][x1].setPos({x1 * 33, y2 * 33});
        this->snake.front() = std::make_tuple(y2, x1);
    }

    if (input == 3) {
        //check if snake eat his tail
        for (size_t i = 1; i < this->snake.size(); i++) {
            if (std::get<0>(this->snake[0]) == std::get<0>(this->snake[i]) && std::get<1>(this->snake[0]) - 1 == std::get<1>(this->snake[i])) {
                return (1);
            }
        }
        int y1 = std::get<0>(this->snake.front());
        int x1 = std::get<1>(this->snake.front());
        int x2 = std::get<1>(this->snake.front()) - 1;
        this->snake.insert(this->snake.begin() + 1, std::make_tuple(y1, x1));
        this->map[y1][x1].setCharacter('O');
        this->map[y1][x1].setFilename(this->path_corps);
        this->map[y1][x1].setColorCharacter(IEntity::COLOR::ARCADE_BLUE);
        this->map[y1][x1].setColorBackground(IEntity::COLOR::ARCADE_BLACK);
        this->map[y1][x1].setAnimation(0);
        this->map[y1][x1].setHaveChange(0);
        this->map[y1][x1].setPos({x1 * 33, y1 * 33});
        this->map[y1][x2].setCharacter('O');
        this->map[y1][x2].setFilename(this->path_corps);
        this->map[y1][x2].setColorCharacter(IEntity::COLOR::ARCADE_BLUE);
        this->map[y1][x2].setColorBackground(IEntity::COLOR::ARCADE_BLACK);
        this->map[y1][x2].setAnimation(0);
        this->map[y1][x2].setHaveChange(0);
        this->map[y1][x2].setPos({x2 * 33, y1 * 33});
        this->snake.front() = std::make_tuple(y1, x2);
    }

    if (input == 4) {
        //check if snake eat his tail
        for (size_t i = 1; i < this->snake.size(); i++) {
            if (std::get<0>(this->snake[0]) == std::get<0>(this->snake[i]) && std::get<1>(this->snake[0]) + 1 == std::get<1>(this->snake[i])) {
                return (1);
            }
        }
        int y1 = std::get<0>(this->snake.front());
        int x1 = std::get<1>(this->snake.front());
        int x2 = std::get<1>(this->snake.front()) + 1;
        this->snake.insert(this->snake.begin() + 1, std::make_tuple(std::get<0>(this->snake.front()), std::get<1>(this->snake.front())));
        this->map[y1][x1].setCharacter('O');
        this->map[y1][x1].setFilename(this->path_corps);
        this->map[y1][x1].setColorCharacter(IEntity::COLOR::ARCADE_BLUE);
        this->map[y1][x1].setColorBackground(IEntity::COLOR::ARCADE_BLACK);
        this->map[y1][x1].setAnimation(0);
        this->map[y1][x1].setHaveChange(0);
        this->map[y1][x1].setPos({x1 * 33, y1 * 33});
        this->map[y1][x2].setCharacter('O');
        this->map[y1][x2].setFilename(this->path_corps);
        this->map[y1][x2].setColorCharacter(IEntity::COLOR::ARCADE_BLUE);
        this->map[y1][x2].setColorBackground(IEntity::COLOR::ARCADE_BLACK);
        this->map[y1][x2].setAnimation(0);
        this->map[y1][x2].setHaveChange(0);
        this->map[y1][x2].setPos({x2 * 33, y1 * 33});
        this->snake.front() = std::make_tuple(std::get<0>(this->snake.front()), std::get<1>(this->snake.front()) + 1);
    }
    return (0);
}

std::string arcade::Snake::getMusic() const
{
    return "./assets/Snake/snake_song.ogg";
}
