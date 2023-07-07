/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** test
*/

#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Définition de la classe personnalisée
class Test {
public:
    Test(std::string name, std::string description)
        : name_(name), description_(description) {}

    std::string getName() const { return name_; }
    std::string getDescription() const { return description_; }

private:
    std::string name_;
    std::string description_;
};


class Test2 {
public:
    Test2(std::string name, std::string description, int value, Test test)
        : name_(name), description_(description), a(value) , test(test) {}

    std::string getName() const { return name_; }
    std::string getDescription() const { return description_; }
    int getA() const { return a; }
    Test getTest() const { return test; }
private:
    std::string name_;
    std::string description_;
    int a;
    Test test;
};

// template <typename... Args>
class header {
    public:
        header() {};
        ~header() {};
        template <typename... Args>
        std::string serializer(std::string separator, Args... args);
        void deserialize() {};
        std::string getBody() const { return _body; }
        void setBody(std::string &body) {_body = body; }
        int getSize() const { return _size; }
        void setSize(int size) { _size = size; }
    private:
        char separator;
        int _size;
        std::string _body;


};
