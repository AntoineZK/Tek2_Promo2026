/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-tekspice-antoine.khalidy
** File description:
** Parser
*/

#include "Parser.hpp"

nts::Parser::Parser(std::string file_path)
{
    this->file.open(file_path);
    this->parseFile();
}

void nts::Parser::parseFile(void)
{
    try {
        std::string line;
        while (std::getline(this->file, line)) {
            line = remove_comment(line);
            std::stringstream ss(line);
            ss >> line;
            if (line == ".chipsets:") {
                this->parseChipsets();
                this->have_chipset = true;
            } else if (line == ".links:") {
                this->parseLinks();
                this->have_link = true;
            }
        }
        if (!this->have_chipset)
            throw ParserException("No chipset");
        if (!this->have_link)
            throw ParserException("No link");
    } catch (ParserException &e) {
        std::cerr << e.what() << std::endl;
        exit(84);
    }
}

std::vector<std::string> nts::Parser::stwa(const std::string& str, const std::string& separators)
{
    std::vector<std::string> words;
    size_t start = 0;
    size_t end = 0;

    while ((end = str.find_first_of(separators, start)) != std::string::npos) {
        if (end > start)
            words.push_back(str.substr(start, end - start));
        start = end + 1;
    }
    if (start < str.length())
        words.push_back(str.substr(start));
    return words;
}

bool nts::Parser::checkisComponents(std::string comp)
{
    std::vector<std::string> gates_components = {"4001", "4011", "4030", "4069", "4071", "4081"};
    std::vector<std::string> special_components = {"input", "output", "clock", "true", "false"};
    std::vector<std::string> elementary_components = {"and", "or", "xor", "not"};
    std::vector<std::string> advanced_components = {"4040"};

    for (std::size_t i = 0; i < gates_components.size(); i++) {
        if (comp == gates_components[i])
            return true;
    }
    for (std::size_t i = 0; i < special_components.size(); i++) {
        if (comp == special_components[i])
            return true;
    }
    for (std::size_t i = 0; i < elementary_components.size(); i++) {
        if (comp == elementary_components[i])
            return true;
    }
    for (std::size_t i = 0; i < advanced_components.size(); i++) {
        if (comp == advanced_components[i])
            return true;
    }
    return false;
}

bool nts::Parser::nameIsUsed(std::string name)
{
    for (std::size_t i = 0; i < this->name_used.size(); i++) {
        if (name == this->name_used[i])
            return true;
    }
    return false;
}

void nts::Parser::errorChipsets(std::vector<std::string> words)
{
    if (words.size() != 2)
        throw ParserException("Invalid number of arguments");
    if (!checkisComponents(words[0]))
        throw ParserException("Invalid component");
    if (nameIsUsed(words[1]))
        throw ParserException("Name already used");
    this->name_used.push_back(words[1]);
    this->chipsets.push_back(GetChipsets(words[0], words[1]));
}

void nts::Parser::count_clockOutputInput(void)
{
    for (std::size_t i = 0; i < this->chipsets.size(); i++) {
        if (this->chipsets[i].getComp() == "clock")
            this->nb_clock++;
        if (this->chipsets[i].getComp() == "output")
            this->nb_output++;
        if (this->chipsets[i].getComp() == "input")
            this->nb_input++;
    }
}

std::string nts::Parser::remove_comment(std::string line)
{
    std::string new_line = "";
    for (std::size_t i = 0; i < line.length(); i++) {
        if (line[i] == '#')
            break;
        new_line += line[i];
    }
    return new_line;
}

std::vector<std::string> nts::Parser::stream_to_vector(std::string line)
{
    std::stringstream ss(line);
    std::vector<std::string> word;
    while (ss >> line)
        word.push_back(line);
    return word;
}

void nts::Parser::parseChipsets(void)
{
    std::string line;
    std::string comp;
    std::string name;
    while (std::getline(this->file, line)) {
        line = remove_comment(line);
        std::vector<std::string> words = stream_to_vector(line);
        if (words.size() == 0)
            break;
        this->errorChipsets(words);
    }
    this->count_clockOutputInput();
}

void nts::Parser::printChipsets(void)
{
    for (auto it = this->chipsets.begin(); it != this->chipsets.end(); it++)
        std::cout << it->getComp() << " " << it->getName() << std::endl;
}

bool nts::Parser::nameExist(std::string name)
{
    for (std::size_t i = 0; i < this->chipsets.size(); i++) {
        if (name == this->chipsets[i].getName())
            return true;
    }
    return false;
}

bool nts::Parser::isNumber(std::string str)
{
    for (std::size_t i = 0; i < str.length(); i++) {
        if (isdigit(str[i]) == false)
            return false;
    }
    return true;
}

void nts::Parser::errorLinks(std::vector<std::string> words)
{
    if (words.size() != 2)
        throw ParserException("Invalid number of arguments");
    std::vector<std::string> comp1 = stwa(words[0], ":");
    std::vector<std::string> comp2 = stwa(words[1], ":");
    if (comp1.size() != 2 || comp2.size() != 2)
        throw ParserException("Invalid number of arguments for links");
    if (!nameExist(comp1[0]) || !nameExist(comp2[0]))
        throw ParserException("Name doesn't exist");
    if (!isNumber(comp1[1]) || !isNumber(comp2[1]))
        throw ParserException("Pin is not a number");
    this->links.push_back(GetLinks(comp1[0], comp1[1], comp2[0], comp2[1]));
}

void nts::Parser::parseLinks(void)
{
    std::string line;
    while (std::getline(this->file, line)) {
        line = remove_comment(line);
        std::vector<std::string> words = stream_to_vector(line);
        if (words.size() == 0)
            break;
        this->errorLinks(words);
    }
}

void nts::Parser::printLinks(void)
{
    for (auto it = this->links.begin(); it != this->links.end(); it++) {
        std::cout << it->getComp1() << " " << it->getPin1() << " " <<
        it->getComp2() << " " << it->getPin2() << std::endl;
    }
}

nts::Parser::ParserException::ParserException(const std::string &message) : _message(message)
{
}

const char *nts::Parser::ParserException::what() const noexcept
{
    return _message.c_str();
}
