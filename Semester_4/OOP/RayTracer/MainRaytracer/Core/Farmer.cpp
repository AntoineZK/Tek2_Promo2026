/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** Farmer
*/

#include "Core.hpp"

void RT::Raytracer::startFarmerThread()
{
    std::cout << "Farmer is starting ..." << std::endl;
    this->_farmerThread = std::thread(&Raytracer::farmerThread, this);
}

void RT::Raytracer::farmerThread()
{
    std::cout << "Farmer is running ..." << std::endl;
    this->waitClient();
    this->startClient();

    while (1) {
        // printf("farmer loop\n");
        this->getMessagesWithSelect(true, 2);

        if (!_graphics) {
            if (!this->_screenNotTreated.size() && !this->_screenInTreatement.size()) {
                break;
            }
        } else if (this->_endOfRender) {
            break;
        }
        std::cerr << "\rarea remaining: "<< std::to_string((int) (this->_nbArea - (int) this->_screenTreated.size())) << std::flush;
        std::unique_lock<std::mutex> lock(this->_mutex);
        // printf("%d\n", (int) (this->_nbArea - (int) this->_screenTreated.size()));
        lock.unlock();
    }
    for (int i = 0; i < this->_nbClient; i++) {
        this->_server->sendMessage(this->_clientListWithSocket[i].second, END_RENDER);
    }
    this->waitClientStopped();
}

void RT::Raytracer::waitClient()
{
    std::cout << "Waiting for client" << std::endl;


    while (this->_nbClientReady != this->_nbClient) {
        printf("waiting ready client\n");
        printf("nb client ready: %d | nb client %d\n", this->_nbClientReady, this->_nbClient);
        this->getMessagesWithSelect(true, 2);
    }
}

void RT::Raytracer::waitClientStopped()
{
    std::cout << "Waiting for client to stop" << std::endl;

    this->_nbClientEnd = 0;
    while (this->_nbClientEnd != this->_nbClient) {
        printf("waiting stopped client\n");
        printf("nb client stopped: %d | nb client %d\n", this->_nbClientEnd, this->_nbClient);
        this->getMessagesWithSelect(true, 2);
    }
}

void RT::Raytracer::startClient()
{
    std::cout << "Sending to client to start calculating" << std::endl;
    std::unique_lock<std::mutex> lock(this->_mutex);
    for (int i = 0; i < this->_nbClient; i++) {
        this->_server->sendMessage(this->_clientListWithSocket[i].second, START_RENDER);
    }
    lock.unlock();
}
