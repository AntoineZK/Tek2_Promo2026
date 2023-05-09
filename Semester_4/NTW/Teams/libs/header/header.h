/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** header
*/

#pragma once

typedef enum BODY_TYPE {
    TEXT,
    FILE_IMAGE,
    VIDEO,
    AUDIO
} BODY_TYPE;

#pragma pack(1)
typedef struct header_s {
    BODY_TYPE type;
    size_t size;
    char body[0];
} header_t;
