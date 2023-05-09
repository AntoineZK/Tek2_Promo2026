/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-antoine.khalidy
** File description:
** SFML
*/

#include "SFML.hpp"

extern "C" std::unique_ptr<arcade::IGraphical> GraphEntrypoint()
{
    return std::make_unique<arcade::SFML>();
}

arcade::SFML::SFML()
{
    this->window.create(sf::VideoMode(1920, 1080), "Arcade SFML");
    this->window.setFramerateLimit(120);
    this->view.reset(sf::FloatRect(0, 0, 1920, 1080));
    this->view.setCenter(550, 535);
    this->window.setView(this->view);
    this->scoreText = this->createText("Score : ", 24, sf::Color::Red, {-350, 0});
    this->scoreValue = this->createText("0", 24, sf::Color::Red, {-250, 0});
    this->livesText = this->createText("Lives : ", 24, sf::Color::Blue, {-350, 40});
    this->livesValue = this->createText("0", 24, sf::Color::Blue, {-250, 40});
    this->levelText = this->createText("Level : ", 24, sf::Color::Yellow, {-350, 80});
    this->levelValue = this->createText("0", 24, sf::Color::Yellow, {-250, 80});
}

arcade::SFML::~SFML()
{
    this->window.close();
}

sf::Text arcade::SFML::createText(std::string text, int size, sf::Color color, std::pair<int, int> pos)
{
    sf::Text newText;

    this->font.loadFromFile("assets/arial.ttf");
    newText.setCharacterSize(size);
    newText.setFillColor(color);
    newText.setPosition(pos.first, pos.second);
    newText.setString(text);
    newText.setFont(this->font);
    return newText;
}

std::vector<int> arcade::SFML::getInputs()
{
    std::vector<int> inputs;

    while (this->window.pollEvent(this->event)) {
        if (this->event.type == sf::Event::KeyPressed) {
            inputs.push_back(this->keyMap[this->event.key.code]);
        }
    }
    return inputs;
}

void arcade::SFML::display(std::shared_ptr<IData> data)
{
    this->scoreValue.setString(std::to_string(data->getScore()));
    this->livesValue.setString(std::to_string(data->getLives()));
    this->levelValue.setString(std::to_string(data->getLevel()));
    this->window.clear(sf::Color::Black);
    this->window.draw(this->scoreText);
    this->window.draw(this->scoreValue);
    this->window.draw(this->livesText);
    this->window.draw(this->livesValue);
    this->window.draw(this->levelText);
    this->window.draw(this->levelValue);
    std::pair<std::size_t, std::size_t> mapSize = data->getMapSize();
    for (std::size_t i = 0; i < mapSize.first; i++) {
        for (std::size_t j = 0; j < mapSize.second; j++) {
            sf::RectangleShape rectangle(sf::Vector2f(34, 34));
            rectangle.setPosition(j * 34, i * 34);
            IEntity &entity = data->getEntities(i, j);
            if (entity.getFilename() != "") {
                sf::Texture texture;
                texture.loadFromFile(entity.getFilename());
                rectangle.setTexture(&texture);
                rectangle.setTextureRect(sf::IntRect(0, 0, 34, 34));
                this->window.draw(rectangle);
            } else {
                arcade::IEntity::COLOR colorCharacter = entity.getColorCharacter();
                arcade::IEntity::COLOR colorBackground = entity.getColorBackground();
                sf::Text text(entity.getCharacter(), this->font, 24);
                text.setFillColor(this->colorMap[colorCharacter]);
                text.setPosition((j * 34) + 13, i * 34);
                rectangle.setFillColor(this->colorMap[colorBackground]);
                this->window.draw(rectangle);
                this->window.draw(text);
            }
        }
    }
    this->window.display();
}
