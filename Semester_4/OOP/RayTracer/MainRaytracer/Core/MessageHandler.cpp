/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** MessageHandler
*/

#include "Core.hpp"

//! ---- message handling ----

void RT::Raytracer::getMessagesWithSelect(bool activeTimeout, int timeS, int timeMs)
{
    // setup fd for select and waiting for client response

    FD_ZERO(&this->_readFds);

    if (!this->_maxFd)
        this->_maxFd = this->setMaxFd();
    for (auto &it : _clientListWithSocket) {
        FD_SET(it.second, &this->_readFds);
    }

    int returnSelect = 0;
    if (activeTimeout) {
        this->_timeout.tv_sec = timeS;
        this->_timeout.tv_usec = timeMs;
        returnSelect = ::select(this->_maxFd + 1, &this->_readFds, NULL, NULL, &this->_timeout);

        // print if select timeout
        // if (returnSelect == 0) {
        //     std::cout << "Select timeout" << std::endl;
        // }

    } else {
        ::select(this->_maxFd + 1, &this->_readFds, NULL, NULL, NULL);
    }

    for (auto &it : _clientListWithSocket) {
        if (FD_ISSET(it.second, &this->_readFds)) {
            std::vector<std::string> msg = this->_server->receive(it.second);
            // printf("message received\n");
            // for (auto &it2 : msg) {
            //     std::cout << "Received from " << it.second << ": " << it2 << std::endl;
            // }
            this->handleMessages(msg, it.second);
        }
    }
}

void RT::Raytracer::handleMessages(std::vector<std::string> &messages, int &socket)
{
    int tmpIndex = 0;
    for (int i = 0; i < (int) messages.size(); i++) {
        tmpIndex = i;
        for (auto &it : this->_clientMessageList) {
            if (it.first.first == messages[i]) {
                (this->*(it.second))(messages, i, socket);
                if (i - tmpIndex != it.first.second) {
                    throw std::runtime_error("Error: " + messages[i] + " need " + std::to_string(it.first.second) + " arguments\n");
                }
            }
        }
    }
}

void RT::Raytracer::sendMoreWork(std::vector<std::string> &messages, int &index, int &socket)
{
    (void)messages;
    (void)index;
    // std::cout << "send more work" << std::endl;
    int size = this->_screenNotTreated.size();
    int random = 0;
    if (size) {
        // printf("send not treated area\n");
        random = rand() % (size);
        auto tmp = this->getScreenRange(random, this->_screenNotTreated);
        this->_server->sendMessage(socket, SEND_AREA, tmp);
        this->moveScreenRange(this->_screenNotTreated, this->_screenInTreatement, random);
    } else if ((size = this->_screenInTreatement.size())) {
        printf("send in treatement area\n");
        random = rand() % (size);
        auto tmp = this->getScreenRange(random, this->_screenInTreatement);
        this->_server->sendMessage(socket, SEND_AREA, tmp);
        this->moveScreenRange(this->_screenInTreatement, this->_screenInTreatement, random);
    } else {
        printf("send no area\n");
        this->_server->sendMessage(socket, STOP);
        return;
    }
}

void RT::Raytracer::recivePixel(std::vector<std::string> &messages, int &index, int &socket)
{
    (void)socket;
    // std::cout << "recive pixel" << std::endl;
    // // todo il faudra deserialize le pixel (x, y, color)
    // this->deserializePixel(messages[index + 1]);
    if (index >= (int) messages.size() - 1)
        throw std::runtime_error("Error: not enough arguments\n");
    index += 1;
    std::vector<std::pair<std::pair<int, int>, pixel_t>> tmp = this->deserializePixel(messages[index]);
    // printf("deserialize pixel\n");
    // for (auto &it : tmp)
    //     std::cout << "x: " << it.first.first << " y: " << it.first.second << " r: " << it.second.r << " g: " << it.second.g << " b: " << it.second.b << std::endl;

    // printf("-----------------------------\n");
    for (auto &it : tmp)
        this->insertPixel(it.first, it.second);
        // std::cout << "x: " << it.first.first << " y: " << it.first.second << " r: " << it.second.r << " g: " << it.second.g << " b: " << it.second.b << std::endl;
    // exit(0);
    this->moveScreenRange(this->_screenInTreatement, this->_screenTreated, AUTO, tmp[0].first);
}

std::vector<std::pair<std::pair<int, int>, pixel_t>> RT::Raytracer::deserializePixel(std::string &message)
{
    // printf("deserialize pixel\n");
    std::vector<std::pair<std::pair<int, int>, pixel_t>> result;
    std::vector<std::string> tmp2 = this->_utils->split(message, ',');

    int size = tmp2.size();
    if (size  % 5 != 0)
        throw std::runtime_error("Error: not enough arguments\n");
    for (int i = 0; i < size;) {
        std::pair<std::pair<int, int>, pixel_t> tmp;
        tmp.first.first = std::atoi(tmp2[i + 0].c_str());
        tmp.first.second = std::atoi(tmp2[i + 1].c_str());
        tmp.second.r = std::atoi(tmp2[i + 2].c_str());
        tmp.second.g = std::atoi(tmp2[i + 3].c_str());
        tmp.second.b = std::atoi(tmp2[i + 4].c_str());
        result.push_back(tmp);
        i += 5;
    }
    return result;
}

void RT::Raytracer::insertPixel(std::pair<int, int> &pos, pixel_t &pixel)
{
    // printf("insert pixel %d %d\n", pos.first, pos.second);
    // this->_mutex.lock();
    // printf("insert pixel %d %d\n", pos.first, pos.second);
    if (pos.first < 0 || pos.first >= this->_sizeX || pos.second < 0 || pos.second >= this->_sizeY)
        throw std::runtime_error("Error: pixel out of range\n");
    this->_pixelsToRender[pos.second][pos.first] = pixel;
    // this->_mutex.unlock();
}

void RT::Raytracer::clientReady(std::vector<std::string> &messages, int &index, int &socket)
{
    (void)messages;
    (void)index;
    (void)socket;
    std::cout << "client ready" << std::endl;
    this->_nbClientReady += 1;
}

void RT::Raytracer::wrongConfig(std::vector<std::string> &messages, int &index, int &socket)
{
    (void)messages;
    (void)index;
    (void)socket;
    std::cout << "wrong config" << std::endl;
}

//! ---- message handling ----

std::pair<std::pair<int, int>, std::pair<int, int>> RT::Raytracer::getScreenRange(int &index, std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> &screenList)
{
    if (index >= (int) screenList.size())
        throw std::runtime_error("Error: index out of range\n");
    return screenList[index];
}

void RT::Raytracer::moveScreenRange(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> &screenListsrc, std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> &screenListdest, int index, std::pair<int, int> pos)
{
    // printf("move screen range\n");
    if (index == -1) {
        this->moveAuto(screenListsrc, screenListdest, pos);
        return;
    } else if (index >= (int) screenListsrc.size())
        throw std::runtime_error("Error: index out of range\n");
    screenListdest.push_back(screenListsrc[index]);
    screenListsrc.erase(screenListsrc.begin() + index);
    // printf("print screen list src\n");
    // printf("--------------------------------\n");
    // for (auto &it : screenListsrc) {
    //     printf("x: %d xend: %d y: %d yend: %d\n", it.first.first, it.first.second, it.second.first, it.second.second);
    // }
    // printf("--------------------------------\n");
    // printf("print screen list dest\n");
    // printf("--------------------------------\n");
    // for (auto &it : screenListdest) {
    //     printf("x: %d xend: %d y: %d yend: %d\n", it.first.first, it.first.second, it.second.first, it.second.second);
    // }
    // printf("--------------------------------\n");
}

void RT::Raytracer::moveAuto(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> &screenListsrc, std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> &screenListdest, std::pair<int, int> pos)
{
    //? iterate the screenListsrc to find wich node contain the pos
    // printf("move auto, pos: %d | %d\n", pos.first, pos.second);
    int index = this->_utils->findInList(screenListsrc, pos);
    if (index != -1) {
        screenListdest.push_back(screenListsrc[index]);
        screenListsrc.erase(screenListsrc.begin() + index);
        // printf("print screen list src\n");
        // printf("--------------------------------\n");
        // for (auto &it : screenListsrc) {
        //     printf("x: %d xend: %d y: %d yend: %d\n", it.first.first, it.first.second, it.second.first, it.second.second);
        // }
        // printf("--------------------------------\n");
        // printf("print screen list dest\n");
        // printf("--------------------------------\n");
        // for (auto &it : screenListdest) {
        //     printf("x: %d xend: %d y: %d yend: %d\n", it.first.first, it.first.second, it.second.first, it.second.second);
        // }
        // printf("--------------------------------\n");
        return;
    }
}

void RT::Raytracer::allClientEnd(std::vector<std::string> &messages, int &index, int &socket)
{
    (void)messages;
    (void)index;
    (void)socket;
    std::cout << "all client end" << std::endl;
    this->_nbClientEnd += 1;
}