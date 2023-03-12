/*
** EPITECH PROJECT, 2023
** B-ASM-400-NCY-4-1-asmminilibc-antoine.khalidy
** File description:
** main
*/

#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

void *handle;
size_t (*_strlen) (const char *);
char *(*_strchr) (const char *, int);
char *(*_strrchr) (const char *, int);
void *(*_memset) (void *, int, size_t);
void *(*_memcpy) (void *, const void *, size_t);
int (*_strcmp) (const char *, const char *);
void *(*_memmove) (void *, const void *, size_t);
int (*_strncmp) (const char *, const char *, size_t);
int (*_strcasecmp) (const char *, const char *);
char *(*_strstr) (const char *, const char *);
char *(*_strpbrk) (const char *, const char *);
size_t (*_strcspn) (const char *, const char *);
size_t (*_strcspn) (const char *, const char *);

void setup(void) {
    handle = dlopen("libasm.so", RTLD_LAZY);
    _strlen = dlsym(handle, "strlen");
    _strchr = dlsym(handle, "strchr");
    _strrchr = dlsym(handle, "strrchr");
    _memset = dlsym(handle, "memset");
    _memcpy = dlsym(handle, "memcpy");
    _strcmp = dlsym(handle, "strcmp");
    _memmove = dlsym(handle, "memmove");
    _strncmp = dlsym(handle, "strncmp");
    _strcasecmp = dlsym(handle, "strcasecmp");
    _strstr = dlsym(handle, "strstr");
    _strpbrk = dlsym(handle, "strpbrk");
    _strcspn = dlsym(handle, "strcspn");
}

int main(void) {
    setup();
    printf("[strlen] => Got: %ld | Excepted: %ld\n", _strlen("Bonjour"), strlen("Bonjour"));
    printf("[strchr] => Got: \"%s\" | Excepted: \"%s\"\n", _strchr("Bonjour", 'o'), strchr("Bonjour", 'o'));
    printf("[strrchr] => Got: \"%s\" | Excepted: \"%s\"\n", _strrchr("Bonjour", 'o'), strrchr("Bonjour", 'o'));
    char *memtest1 = malloc(sizeof(char) * 4);
    char *memtest2 = malloc(sizeof(char) * 4);
    memtest1[3] = '\0';
    memtest2[3] = '\0';
    _memset(memtest1, 'A', 3);
    memset(memtest2, 'A', 3);
    printf("[memset] => Got: \"%s\" | Excepted: \"%s\"\n", memtest1, memtest2);
    _memcpy(memtest1, "Mario", 5);
    memcpy(memtest2, "Mario", 5);
    printf("[memcpy] => Got: \"%s\" | Excepted: \"%s\"\n", memtest1, memtest2);
    printf("[strcmp] => Got: %d | Excepted: %d\n", _strcmp("he", "ha"), strcmp("he", "ha"));
    printf("[strcmp-1] => Got: %d | Excepted: %d\n", _strcmp("Bonjour", "Bznjour"), strcmp("Bonjour", "Bznjour"));
    printf("[strcmp-2] => Got: %d | Excepted: %d\n", _strcmp("Bonjour", "Bonjour"), strcmp("Bonjour", "Bonjour"));
    // _memmove(memtest1, "Cringe", 4);
    // memmove(memtest2, "Cringe", 4);
    // printf("[memmove] => Got: \"%s\" | Excepted: \"%s\"\n", memtest1, memtest2);
    printf("[strncmp] => Got: %d | Excepted: %d\n", _strncmp("Hello World!", "Hello World", 13), strncmp("Hello World!", "Hello World", 13));
    printf("[strncmp-1] => Got: %d | Excepted: %d\n", _strncmp("Bonjour", "Bznjour", 3), strncmp("Bonjour", "Bznjour", 3));
    printf("[strncmp-2] => Got: %d | Excepted: %d\n", _strncmp("Bonjour", "Bonzour", 2), strncmp("  Bonjour", "Bonzour", 2));
    printf("[strcasecmp] => Got: %d | Excepted: %d\n", _strcasecmp("Bonjour", "BOnjour"), strcasecmp("Bonjour", "BOnjour"));
    printf("[strcasecmp-1] => Got: %d | Excepted: %d\n", _strcasecmp("Bonjour", "Bznjour"), strcasecmp("Bonjour", "Bznjour"));
    printf("[strcasecmp-2] => Got: %d | Excepted: %d\n", _strcasecmp("Bonjour", "Bonjour"), strcasecmp("Bonjour", "Bonjour"));
    printf("[strstr] => Got: \"%s\" | Excepted: \"%s\"\n", _strstr("Bonjoura", "jour"), strstr("Bonjoura", "jour"));
    printf("[strpbrk] => Got: \"%s\" | Excepted: \"%s\"\n", _strpbrk("Bonjour", "nor"), strpbrk("Bonjour", "nor"));
    printf("[strcspn] => Got: %ld | Excepted: %ld\n", _strcspn("Boezezezezezoaoooooozzzznjour", "zjr"), strcspn("Boezezezezezoaoooooozzzznjour", "zjr"));
    dlclose(handle);
    return (0);
}
