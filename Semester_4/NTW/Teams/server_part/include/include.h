/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** include
*/

#pragma once
//include linux basics lib
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <math.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdarg.h>
#include <time.h>

//include for linux socket
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/select.h>

//include for the thread
#include <pthread.h>
#include <threads.h>

//include for the uuid
#include <uuid/uuid.h>

//* define for the server
#define MAX_CLIENTS 10000
#define MAX_BUFFER 1024
#define MAX_USERNAME 32
#define MAX_PASSWORD 32
#define MAX_COMMAND_SIZE 1024
#define MAX_COMMANDS 10
#define MAX_NAME_LENGTH 32
#define MAX_DESCRIPTION_LENGTH 255
#define MAX_BODY_LENGTH 512

// Project include
#include "../../libs/myteams/logging_server.h"
#include "../../libs/header/header.h"
