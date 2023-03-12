/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-tekspice-antoine.khalidy
** File description:
** Parser
*/

#pragma once
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <exception>
#include "GetChipsets.hpp"
#include "GetLinks.hpp"

namespace nts {
    class Parser {
    public:
        Parser(std::string file_path);
        ~Parser() = default;
        void parseFile(void);
        void parseChipsets(void);
        void parseLinks(void);
        static std::vector<std::string> stwa(const std::string &str, const std::string &separators);
        std::vector<GetChipsets> getChipsets(void) { return this->chipsets; };
        std::vector<GetLinks> getLinks(void) { return this->links; };
        bool checkisComponents(std::string comp);
        bool nameIsUsed(std::string name);
        bool nameExist(std::string name);
        static bool isNumber(std::string str);
        void errorChipsets(std::vector<std::string> line);
        void errorLinks(std::vector<std::string> words);
        void printChipsets(void);
        std::string remove_comment(std::string line);
        std::vector<std::string> stream_to_vector(std::string str);
        void printLinks(void);
        void count_clockOutputInput(void);
        int getNbClock(void) { return this->nb_clock; };
        int getNbInput(void) { return this->nb_input; };
        int getNbOutput(void) { return this->nb_output; };

        class ParserException : public std::exception {
        public:
            ParserException(std::string const &message);
            const char *what(void) const noexcept;

        private:
            std::string _message;
        };

    protected:
    private:
        std::ifstream file;
        std::vector<GetChipsets> chipsets;
        std::vector<GetLinks> links;
        std::vector<std::string> name_used;
        int nb_clock = 0;
        int nb_input = 0;
        int nb_output = 0;
        bool have_link = false;
        bool have_chipset = false;
    };
}
