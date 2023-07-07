/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** Include
*/

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <filesystem>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <stack>
#include <queue>
#include <list>
#include <array>
#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <future>
#include <random>
#include <limits>
#include <numeric>
#include <iomanip>
#include <utility>
#include <type_traits>
#include <typeinfo>
#include <typeindex>
#include <stdexcept>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <atomic>
#include <fcntl.h>

#define ES "\033[1;31m!["
#define EE "]!\033[0m"

std::string format_message(const std::string &message);

#define AUTO -1

//? define for message handling

//? client
//? what we can send to the server

#define ASK_MORE "more"
#define WRONG_CONFIG "wrong"
#define I_AM_READY "ready"
#define SEND_PIXEL "pixel"

//? what we can recive from the server

#define THREADS "threads"
#define CONFIG "config"
#define START "start"
#define STOP "stop"
#define AREA "area"
#define SCALING "scaling"
#define END "end"

//? server
//? what we can send to the client

#define START_RENDER START
#define SEND_CONFIG CONFIG
#define SEND_NB_THREADS THREADS
#define SEND_AREA AREA
#define STOP_RENDER STOP
#define SEND_SCALING SCALING
#define END_RENDER END

//? what we can recive from the client

#define CLIENT_NEED_WORK ASK_MORE
#define RECIVE_PIXEL SEND_PIXEL
#define CLIENT_READY I_AM_READY
#define ALL_CLIENT_END END
// #define WRONG_CONFIG (deja defini plus haut)

typedef struct pixel_s {
    int r;
    int g;
    int b;
} pixel_t;

#define ERROR(x) format_message(x)