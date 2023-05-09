/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-antoine.khalidy
** File description:
** Core
*/

#include "Core.hpp"

arcade::Core::Core()
{
    this->actualLib = -1;
    this->in_value = IN::MENU;
    data = std::make_shared<DataGame>();
    data->setMapSize({1, 1});
}

arcade::Core::~Core()
{
}

int arcade::Core::helper(int retVal)
{
    std::cout << "USAGE" << std::endl;
    std::cout << "\t./arcade lib" << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "\tlib\t\tthe graphical library you want to use" << std::endl;
    return (retVal);
}

void arcade::Core::runGame(char *lib)
{
    this->initCore(lib);
    std::vector<int> inputs;
    CURRENT_TIME currentTime = std::chrono::steady_clock::now();
    while (1) {
        inputs = this->graphicalLib->getInputs();
        if (this->manageCore(inputs) == -1)
            break;
        int returnValue = this->gameLib->manage(inputs, data, currentTime);
        if (in_value == IN::MENU && returnValue != -1) {
            in_value = IN::GAME;
            this->actualGame = returnValue;
            this->gameLib.reset();
            this->loaderGame.reset();
            this->loaderGame = std::make_unique<DLLoader>(this->gameLibs[this->actualGame]);
            this->gameLib = this->loaderGame->getInstance<std::unique_ptr<IGame>()>("GameEntrypoint")();
            this->audioLib = this->loaderAudio->getInstance<std::unique_ptr<IAudio>()>("createAudio")();
            this->audioLib->playMusic(this->gameLib->getMusic());
        }
        inputs.clear();
        this->graphicalLib->display(data);
        if (in_value == IN::GAME && data->getLives() == 0) {
            this->resetGame();
        }
    }
    this->graphicalLib.reset();
    this->gameLib.reset();
    this->audioLib.reset();
}

int arcade::Core::manageCore(std::vector<int> inputs)
{
    for (auto &input : inputs) {
        if (input == 27)
            return (-1);
        if (input == 'n')
            this->nextGraphicalLib();
        if (input == 'b' && in_value == IN::GAME)
            this->nextGame();
        if (input == 'm' && in_value == IN::GAME)
            this->returnToMenu();
        if (input == 'r' && in_value == IN::GAME)
            this->resetGame();
        if (input == 'a' && in_value == IN::GAME)
            this->nextAudioLib();
    }
    return (0);
}

std::vector<std::string> arcade::Core::getLibs()
{
    std::vector<std::string> files;

    for (const auto & entry : std::filesystem::directory_iterator("./lib")) {
        std::string filename = entry.path().filename();
        if (filename.find(".so") != std::string::npos)
            files.push_back(filename);
    }
    return (files);
}

void arcade::Core::loadLibs()
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

void arcade::Core::getActualLib(char *lib)
{
    for (size_t i = 0; i < this->graphicalLibs.size(); i++) {
        if (this->graphicalLibs[i].find(lib) != std::string::npos) {
            this->actualLib = i;
            return;
        }
    }
}

void arcade::Core::resetGame()
{
    this->gameLib.reset();
    this->gameLib = this->loaderGame->getInstance<std::unique_ptr<IGame>()>("GameEntrypoint")();
    this->audioLib.reset();
    this->audioLib = this->loaderAudio->getInstance<std::unique_ptr<IAudio>()>("createAudio")();
    std::string audioLib = this->gameLib->getMusic();
    this->audioLib->playMusic(this->gameLib->getMusic());
}

void arcade::Core::returnToMenu()
{
    this->in_value = IN::MENU;
    this->gameLib.reset();
    this->loaderGame.reset();
    this->loaderGame = std::make_unique<DLLoader>("./lib/arcade_menu.so");
    this->gameLib = this->loaderGame->getInstance<std::unique_ptr<IGame>()>("GameEntrypoint")();
    this->audioLib.reset();
}

void arcade::Core::nextGame()
{
    this->gameLib.reset();
    this->loaderGame.reset();
    this->actualGame == static_cast<int>(this->gameLibs.size()) - 1 ? this->actualGame = 0 : this->actualGame++;
    this->loaderGame = std::make_unique<DLLoader>(this->gameLibs[this->actualGame]);
    this->gameLib = this->loaderGame->getInstance<std::unique_ptr<IGame>()>("GameEntrypoint")();
    this->audioLib.reset();
    this->audioLib = this->loaderAudio->getInstance<std::unique_ptr<IAudio>()>("createAudio")();
    std::string audioPath = this->gameLib->getMusic();
    this->audioLib->playMusic(audioPath);
}

void arcade::Core::nextGraphicalLib()
{
    this->graphicalLib.reset();
    this->loaderGraphical.reset();
    this->actualLib == static_cast<int>(this->graphicalLibs.size()) - 1 ? this->actualLib = 0 : this->actualLib++;
    this->loaderGraphical = std::make_unique<DLLoader>(this->graphicalLibs[this->actualLib]);
    this->graphicalLib = this->loaderGraphical->getInstance<std::unique_ptr<IGraphical>()>("GraphEntrypoint")();
}

void arcade::Core::nextAudioLib()
{
    this->audioLib.reset();
    this->loaderAudio.reset();
    this->actualAudio == static_cast<int>(this->audioLibs.size()) - 1 ? this->actualAudio = 0 : this->actualAudio++;
    this->loaderAudio = std::make_unique<DLLoader>(this->audioLibs[this->actualAudio]);
    this->audioLib = this->loaderAudio->getInstance<std::unique_ptr<IAudio>()>("createAudio")();
    std::string audioPath = this->gameLib->getMusic();
    this->audioLib->playMusic(audioPath);
}

void arcade::Core::initCore(char *lib)
{
    this->getActualLib(lib);
    this->loaderGraphical = std::make_unique<DLLoader>(lib);
    this->loaderGame = std::make_unique<DLLoader>("./lib/arcade_menu.so");
    this->loaderAudio = std::make_unique<DLLoader>("./lib/arcade_sdl2audio.so");
    this->graphicalLib = this->loaderGraphical->getInstance<std::unique_ptr<IGraphical>()>("GraphEntrypoint")();
    this->gameLib = this->loaderGame->getInstance<std::unique_ptr<IGame>()>("GameEntrypoint")();
    this->actualAudio = 0;
}
