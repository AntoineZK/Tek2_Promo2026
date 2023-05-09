/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-antoine.khalidy
** File description:
** Menu
*/

#include "Menu.hpp"

extern "C" std::unique_ptr<arcade::IGame> GameEntrypoint()
{
    return std::make_unique<arcade::Menu>();
}

arcade::Menu::Menu()
{
    this->loadLibs();
    this->updateVector();
    this->score = 0;
    this->selectedGame = 0;
}

arcade::Menu::~Menu()
{
}

int arcade::Menu::manage(std::vector<int> inputs, std::shared_ptr<IData> data, CURRENT_TIME time)
{
    (void)time;
    for (auto &input : inputs) {
        if (input == 'z' || input == 'Z') {
            this->selectedGame--;
            this->selectedGame < 0 ? this->selectedGame = this->gameLibs.size() - 1 : 0;
        }
        if (input == 's' || input == 'S') {
            this->selectedGame++;
            this->selectedGame >= static_cast<int>(this->gameLibs.size()) ? this->selectedGame = 0 : 0;
        }
        if (input == 'p' || input == 'P')
            return this->selectedGame;
    }
    this->createMenuVisual();
    this->updateData(data);
    return -1;
}

std::string arcade::Menu::removeExtension(std::string filename)
{
    std::string name = filename;
    std::string ext = "";
    for (int i = filename.size() - 1; i >= 0; i--) {
        if (filename[i + 1] == '.')
            break;
        ext = filename[i] + ext;
    }
    for (std::size_t i = 0; i < ext.size(); i++)
        name.pop_back();
    return name;
}

std::string arcade::Menu::getAfterLastUnderscore(std::string filename)
{
    size_t pos = filename.rfind('_');
    if (pos != std::string::npos) {
        return filename.substr(pos + 1);
    }
    return filename;
}

std::tuple<int, int> arcade::Menu::getSpaceLeftRight(std::string str)
{
    int maxWindow = 56;
    int left = 0;
    int right = 0;
    if (static_cast<int>(str.size()) < maxWindow) {
        left = (maxWindow - str.size()) / 2;
        right = (maxWindow - str.size()) / 2;
    }
    return std::make_tuple(left, right);
}

std::vector<arcade::EntityGame> arcade::Menu::placeCenter(std::string str, IEntity::COLOR textColor, int y)
{
    std::vector<arcade::EntityGame> line;
    std::tuple<int, int> space = this->getSpaceLeftRight(str);
    for (int i = 0; i < std::get<0>(space); i++)
        line.emplace_back(arcade::EntityGame(' ', "", IEntity::COLOR::ARCADE_BLACK, arcade::IEntity::COLOR::ARCADE_BLACK, std::make_pair(i * 33, y * 33), 0, 0));
    for (size_t i = 0; i < str.size(); i++)
        line.emplace_back(arcade::EntityGame(str[i], "", textColor, arcade::IEntity::COLOR::ARCADE_BLACK, std::make_pair(i * 33, y * 33), 0, 0));
    for (int i = 0; i < std::get<1>(space); i++)
        line.emplace_back(arcade::EntityGame(' ', "", IEntity::COLOR::ARCADE_BLACK, arcade::IEntity::COLOR::ARCADE_BLACK, std::make_pair(i * 33, y * 33), 0, 0));
    return line;
}

std::vector<std::string> arcade::Menu::getLibs()
{
    std::vector<std::string> files;

    for (const auto & entry : std::filesystem::directory_iterator("./lib")) {
        std::string filename = entry.path().filename();
        if (filename.find(".so") != std::string::npos)
            files.push_back(filename);
    }
    return (files);
}

void arcade::Menu::loadLibs()
{
    std::vector<std::string> files = this->getLibs();
    for (auto &file : files) {
        std::string filePath = "./lib/" + file;
        DLLoader loader(filePath);
        try {
            loader.getInstance<std::unique_ptr<IGraphical>()>("GraphEntrypoint");
            this->graphicalLibs.push_back(filePath);
            continue;
        } catch (const std::exception &e) {}
        try {
            loader.getInstance<std::unique_ptr<IGame>()>("GameEntrypoint");
            this->gameLibs.push_back(filePath);
            continue;
        } catch (const std::exception &e) {}
        try {
            loader.getInstance<std::unique_ptr<IAudio>()>("createAudio");
            this->audioLibs.push_back(filePath);
            continue;
        } catch (const std::exception &e) {}
    }
    this->gameLibs.erase(std::remove(this->gameLibs.begin(), this->gameLibs.end(), "./lib/arcade_menu.so"), this->gameLibs.end());
}

void arcade::Menu::updateVector(void)
{
    for (std::size_t i = 0; i < this->graphicalLibs.size(); i++) {
        this->graphicalLibs[i] = this->removeExtension(this->graphicalLibs[i]);
        this->graphicalLibs[i] = this->getAfterLastUnderscore(this->graphicalLibs[i]);
        std::transform(this->graphicalLibs[i].begin(), this->graphicalLibs[i].end(), this->graphicalLibs[i].begin(), ::toupper);
    }
    for (std::size_t i = 0; i < this->gameLibs.size(); i++) {
        this->gameLibs[i] = this->removeExtension(this->gameLibs[i]);
        this->gameLibs[i] = this->getAfterLastUnderscore(this->gameLibs[i]);
        std::transform(this->gameLibs[i].begin(), this->gameLibs[i].end(), this->gameLibs[i].begin(), ::toupper);
    }
    for (std::size_t i = 0; i < this->audioLibs.size(); i++) {
        this->audioLibs[i] = this->removeExtension(this->audioLibs[i]);
        this->audioLibs[i] = this->getAfterLastUnderscore(this->audioLibs[i]);
        std::transform(this->audioLibs[i].begin(), this->audioLibs[i].end(), this->audioLibs[i].begin(), ::toupper);
    }
}

void arcade::Menu::updateData(std::shared_ptr<arcade::IData> data)
{
    if (data->getMapSize().first != (int) menuInterface.size() || data->getMapSize().second != (int) menuInterface[0].size())
        data->setMapSize({menuInterface.size(), menuInterface[0].size()});
    for (std::size_t i = 0; i < menuInterface.size(); i++) {
        for (std::size_t j = 0; j < menuInterface[i].size(); j++) {
            data->setEntityAt({i, j}, menuInterface[i][j]);
        }
    }
    data->setLevel(0);
    data->setLives(0);
    data->setScore(0);
}

std::vector<arcade::EntityGame> arcade::Menu::placeLeft(std::string str, IEntity::COLOR textColor, int y)
{
    int fullSize = 56;
    int spaceSize = fullSize - str.size();
    std::vector<arcade::EntityGame> line;
    for (size_t i = 0; i < str.size(); i++)
        line.emplace_back(arcade::EntityGame(str[i], "", textColor, arcade::IEntity::COLOR::ARCADE_BLACK, std::make_pair(i * 33, y * 33), 0, 0));
    for (int i = 0; i < spaceSize; i++)
        line.emplace_back(arcade::EntityGame(' ', "", IEntity::COLOR::ARCADE_BLACK, arcade::IEntity::COLOR::ARCADE_BLACK, std::make_pair(i * 33, y * 33), 0, 0));
    return line;
}

std::vector<arcade::EntityGame> arcade::Menu::placeRight(std::string str, IEntity::COLOR textColor, int y)
{
    int fullSize = 56;
    int spaceSize = fullSize - str.size();
    std::vector<arcade::EntityGame> line;

    for (int i = 0; i < spaceSize; i++)
        line.emplace_back(arcade::EntityGame(' ', "", IEntity::COLOR::ARCADE_BLACK, arcade::IEntity::COLOR::ARCADE_BLACK, std::make_pair(i * 33, y * 33), 0, 0));
    for (size_t i = 0; i < str.size(); i++)
        line.emplace_back(arcade::EntityGame(str[i], "", textColor, arcade::IEntity::COLOR::ARCADE_BLACK, std::make_pair(0, 0), 0, 0));
    return line;
}

void arcade::Menu::createMenuVisual()
{
    this->menuInterface.clear();
    this->menuInterface.emplace_back(this->placeLeft(" ", IEntity::COLOR::ARCADE_BLACK, 0));
    this->menuInterface.emplace_back(this->placeCenter("Arcade", IEntity::COLOR::ARCADE_BLUE, 1));
    this->menuInterface.emplace_back(this->placeCenter(" ", IEntity::COLOR::ARCADE_BLACK, 2));
    this->menuInterface.emplace_back(this->placeCenter(" ", IEntity::COLOR::ARCADE_BLACK, 3));
    this->menuInterface.emplace_back(this->placeLeft("Select a game:", IEntity::COLOR::ARCADE_WHITE, 4));
    this->menuInterface.emplace_back(this->placeCenter(" ", IEntity::COLOR::ARCADE_BLACK, 5));
    for (size_t i = 0; i < this->gameLibs.size(); i++) {
        if (static_cast<int>(i) == this->selectedGame)
            this->menuInterface.emplace_back(this->placeCenter("> " + this->gameLibs[i] + " <", IEntity::COLOR::ARCADE_RED, 6 + i));
        else
            this->menuInterface.emplace_back(this->placeCenter(this->gameLibs[i], IEntity::COLOR::ARCADE_WHITE, 6 + i));
    }
    this->menuInterface.emplace_back(this->placeCenter(" ", IEntity::COLOR::ARCADE_BLACK, gameLibs.size() + 7));
    this->menuInterface.emplace_back(this->placeCenter(" ", IEntity::COLOR::ARCADE_BLACK, gameLibs.size() + 8));
    this->menuInterface.emplace_back(this->placeCenter("Press P to play", IEntity::COLOR::ARCADE_YELLOW, gameLibs.size() + 9));
    this->menuInterface.emplace_back(this->placeCenter(" ", IEntity::COLOR::ARCADE_BLACK, gameLibs.size() + 10));
    this->menuInterface.emplace_back(this->placeCenter(" ", IEntity::COLOR::ARCADE_BLACK, gameLibs.size() + 11));
    this->menuInterface.emplace_back(this->placeLeft("All graphical libraries:", IEntity::COLOR::ARCADE_WHITE, gameLibs.size() + 12));
    this->menuInterface.emplace_back(this->placeCenter(" ", IEntity::COLOR::ARCADE_BLACK, gameLibs.size() + 13));
    for (size_t i = 0; i < this->graphicalLibs.size(); i++)
        this->menuInterface.emplace_back(this->placeCenter(this->graphicalLibs[i], IEntity::COLOR::ARCADE_GREEN, gameLibs.size() + 14 + i));
    this->menuInterface.emplace_back(this->placeLeft("All Audio libraries:", IEntity::COLOR::ARCADE_WHITE, gameLibs.size() + 14 + graphicalLibs.size()));
    this->menuInterface.emplace_back(this->placeCenter(" ", IEntity::COLOR::ARCADE_BLACK, gameLibs.size() + 15 + graphicalLibs.size()));
    for (size_t i = 0; i < this->audioLibs.size(); i++)
        this->menuInterface.emplace_back(this->placeCenter(this->audioLibs[i], IEntity::COLOR::ARCADE_GREEN, gameLibs.size() + 16 + graphicalLibs.size() + i));
}

std::string arcade::Menu::getMusic() const
{
    return "";
}
