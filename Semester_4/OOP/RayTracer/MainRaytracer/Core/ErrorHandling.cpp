/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** ErrorHandling
*/

#include "Core.hpp"

//! ---- fonctions for config and errot handling ----

void RT::Raytracer::errorHandling(int ac, char **av)
{
    int indexDiff = 0;
    int isFibd = 0;
    for (int i = 1; i < ac; i++) {
        indexDiff = i;
        isFibd = 0;
        for (auto &arg : this->_authorizedArgList) {
            if (arg.first.first == av[i]) {
                try {
                    (this->*arg.second)(av, i);
                    if (i - indexDiff != arg.first.second)
                        throw std::invalid_argument(ERROR("Invalid parameters : " + std::string(av[i])));
                } catch (const std::exception &e) {
                    // std::cerr << e.what() << std::endl;
                    throw;
                }
                isFibd = 1;
            }
        }
        if (isFibd == 0)
            throw std::invalid_argument(ERROR("Invalid argument : " + std::string(av[i])));
    }
    this->settingsVerification();
}

void RT::Raytracer::settingsVerification()
{
    if (this->_configFile == "" || !std::filesystem::exists(this->_configFile))
        throw std::invalid_argument(ERROR("No or wrong config file specified"));
    if (this->_saveFile == "" && !_graphics)
        throw std::invalid_argument(ERROR("No save file specified"));
    if ((this->_sizeX <= 0 || this->_sizeY <= 0) && this->_graphics == false)
        throw std::invalid_argument(ERROR("Invalid size"));
    else if (this->_graphics == false){
        this->_sizeX ? this->_sizeX : this->_sizeX = 1920;
        this->_sizeY ? this->_sizeY : this->_sizeY = 1080;
    }

}

void RT::Raytracer::help(char **args, int &index)
{
    (void) args;
    (void) index;
    std::cout << "USAGE: ./raytracer [OPTIONS]" << std::endl;
    std::cout << "OPTIONS:" << std::endl;
    std::cout << "\t-h\t\t\tDisplay this help" << std::endl;
    std::cout << "\t-f [configFile]\t\tSet the config file" << std::endl;
    std::cout << "\t-s [saveFile]\t\tSet the save file" << std::endl;
    std::cout << "\t--help\t\t\tDisplay this help" << std::endl;
    std::cout << "\t--threads [nbThreads]\tSet the number of threads" << std::endl;
    std::cout << "\t--file [configFile]\tSet the config file" << std::endl;
    std::cout << "\t--save [saveFile]\tSet the save file" << std::endl;
    std::cout << "\t--preview\t\tActivate preview mode" << std::endl;
    std::cout << "\t--graphics\t\tActivate Sfml mode" << std::endl;
    std::cout << "\t--sizeX [sizeX]\t\tSet the size X of the window" << std::endl;
    std::cout << "\t--sizeY [sizeY]\t\tSet the size Y of the window" << std::endl;
    exit(0);
}

void RT::Raytracer::setConfigFile(char **args, int &index)
{
    if (!(index + 1))
        throw std::invalid_argument(ERROR("Invalid parameters : " + std::string(args[index])));
    this->_configFile = args[index + 1];
    ++index;
}

void RT::Raytracer::setSaveFile(char **args, int &index)
{
    if (!(index + 1))
        throw std::invalid_argument(ERROR("Invalid parameters : " + std::string(args[index])));
    this->_saveFile = args[index + 1];
    ++index;
}

void RT::Raytracer::setNbThreads(char **args, int &index)
{
    if (!(index + 1))
        throw std::invalid_argument(ERROR("Invalid parameters : " + std::string(args[index])));
    this->_nbThreads = std::stoi(args[index + 1]);
    if (this->_nbThreads < 1)
        throw std::invalid_argument(ERROR("Invalid parameters : " + std::string(args[index])));
    ++index;
}

void RT::Raytracer::setPreview(char **args, int &index)
{
    (void) args;
    (void) index;
    this->_preview = true;
}

void RT::Raytracer::setGraphics(char **args, int &index)
{
    (void) args;
    (void) index;
    this->_graphics = true;
    this->_renderingFunction = std::bind(&RT::Raytracer::sfmlRender, this);
}

void RT::Raytracer::setSizeX(char **args, int &index)
{

    if ((args[index + 1]) == nullptr)
        throw std::invalid_argument(ERROR("Invalids parameters : " + std::string(args[index])));
    this->_sizeX = std::atoi(args[index + 1]);
    if (this->_sizeX < 1)
        throw std::invalid_argument(ERROR("Invalid parameters : " + std::string(args[index])));
    ++index;
    if (this->_sizeX && this->_sizeY) {
        this->reserveVectorSize();
        this->initScreenRange();
    }
}

void RT::Raytracer::setSizeY(char **args, int &index)
{
    if ((args[index + 1]) == nullptr)
        throw std::invalid_argument(ERROR("Invalid parameters : " + std::string(args[index])));
    this->_sizeY = std::atoi(args[index + 1]);
    if (this->_sizeY < 1)
        throw std::invalid_argument(ERROR("Invalid parameters : " + std::string(args[index])));
    ++index;
    if (this->_sizeX && this->_sizeY) {
        this->reserveVectorSize();
        this->initScreenRange();
    }
}

void RT::Raytracer::reserveVectorSize()
{
    // printf("sizeX : %d, sizeY : %d\n", this->_sizeX, this->_sizeY);
    this->_pixelsToRender.reserve(this->_sizeY);
    for (int i = 0; i < this->_sizeY; i++) {
        std::vector<pixel_t> tmp;
        // this->_pixelsToRender[i].reserve(this->_sizeX);
        for (int j = 0; j < this->_sizeX; j++) {
            tmp.push_back({0, 0, 0});
        }
        this->_pixelsToRender.push_back(tmp);
    }
    // int incrY = 0;
    // int incrX = 0;
    // for (auto &i : this->_pixelsToRender) {
    //     for (auto &j : i) {
    //         printf(".");
    //         incrX++;
    //     }
    //     incrY++;
    //     printf("\n");
    // }
    // exit(0);
}

//! ---- fonctions for config and errot handling ----