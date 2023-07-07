/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** Sfml
*/

#include "sfml.hpp"

RT::Sfml::sfml_class::sfml_class(int x_win, int y_win) : i(0), window(sf::VideoMode(x_win, y_win), "Raccoon Window", sf::Style::Default)
, _tab_vertex(0), _vertex(0)
{
    _view = window.getDefaultView();
    _mouse_pressed = false;
    window.setFramerateLimit(120);
}

RT::Sfml::sfml_class::sfml_class() : i(0), window(sf::VideoMode(1920, 1080), "Raccoon Window", sf::Style::Default), _tab_vertex(0), _vertex(0)
{
    _view = window.getDefaultView();
    _mouse_pressed = false;
    window.setFramerateLimit(120);
}

RT::Sfml::sfml_class::~sfml_class()
{
}

void RT::Sfml::sfml_class::event()
{
    while (window.pollEvent(_event)) {
        if (_event.type == sf::Event::Closed)
            window.close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            for (size_t j = 0; j < _vertex.size(); j++) {
                sf::Vector2f pos_vertex = _vertex[j].position;
                _vertex[j].position = sf::Vector2f(pos_vertex.x, pos_vertex.y - 10);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            for (size_t j = 0; j < _vertex.size(); j++) {
                sf::Vector2f pos_vertex = _vertex[j].position;
                _vertex[j].position = sf::Vector2f(pos_vertex.x, pos_vertex.y + 10);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            for (size_t j = 0; j < _vertex.size(); j++) {
                sf::Vector2f pos_vertex = _vertex[j].position;
                _vertex[j].position = sf::Vector2f(pos_vertex.x - 10, pos_vertex.y);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            for (size_t j = 0; j < _vertex.size(); j++) {
                sf::Vector2f pos_vertex = _vertex[j].position;
                _vertex[j].position = sf::Vector2f(pos_vertex.x + 10, pos_vertex.y);
            }
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
            _mouse_pressed = true;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                _mouse_pressed = true;
            }
        }
        if (_event.type == sf::Event::MouseWheelMoved) {
            if (_event.mouseWheel.delta > 0) { // La molette a été tournée vers le haut
                _view.zoom(0.9f);
            }
            else if (_event.mouseWheel.delta < 0) { // La molette a été tournée vers le bas
                _view.zoom(1.1f);
            }
        }
        if (_event.type == sf::Event::MouseButtonReleased) {
            _mouse_pressed = false;
        }
    }
}

void RT::Sfml::sfml_class::draw()
{
    window.clear(sf::Color::Black);
    window.setView(_view);
    window.draw(_vertex.data(), _vertex.size(), sf::Points);
    window.display();
}

void RT::Sfml::sfml_class::display(std::vector<std::vector<pixel_t>> &tab_pixel)
{
    int y = 0;
    int x = 0;
    sf::Color color;
    while (window.isOpen()) {
        _mouse_pos = sf::Mouse::getPosition(window);
        color = sf::Color(tab_pixel[y][x].r, tab_pixel[y][x].g, tab_pixel[y][x].b, 0);
        if (x == (int) tab_pixel[y].size()) {
            x = 0;
            y++;
        }
        if (y == (int) tab_pixel.size()) {
            y = 0;
        }
        // if (_tab_vertex != tab_vertex) {
        //     _tab_vertex = tab_vertex;
        //     std::vector<sf::Vertex> vertex;
        //     for (size_t i = 0; i < _tab_vertex.size(); i++) {
        //         for (size_t j = 0; j < _tab_vertex[i].size(); j++) {
        //             sf::Vertex vertex_tmp;
        //             vertex_tmp.position = sf::Vector2f(i, j);
        //             vertex_tmp.color = _tab_vertex[i][j];
        //             vertex.push_back(vertex_tmp);
        //         }
        //     }
        //     _vertex = vertex;
        //     i = 0;
        // }
        // if (i < _vertex.size())
        //     i++;
        // else
        //     i = 0;
        event();
        if (_mouse_pressed == true) {
            sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
            sf::Vector2f direction = sf::Vector2f(mouse_pos.x - _mouse_pos.x, mouse_pos.y - _mouse_pos.y);
            _vertex.data()->position = sf::Vector2f(_vertex.data()->position + direction * 3.f);
            for (size_t j = 0; j < _vertex.size(); j++) {
                sf::Vector2f pos_vertex = _vertex[j].position;
                _vertex.data()[j].position = sf::Vector2f(pos_vertex + direction * 3.f);
            }
        }
        draw();
    }
}

bool RT::Sfml::sfml_class::getWindow()
{
    return (window.isOpen());
}
