/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** Circuit
*/

#ifndef CIRCUIT_HPP_
    #define CIRCUIT_HPP_
    #include "components/AComponent.hpp"
    #include "components/elementary/AndComponent.hpp"
    #include "components/elementary/NotComponent.hpp"
    #include "components/elementary/OrComponent.hpp"
    #include "components/elementary/XorComponent.hpp"
    #include "components/special/TrueComponent.hpp"
    #include "components/special/FalseComponent.hpp"
    #include "components/special/InputComponent.hpp"
    #include "components/special/OutputComponent.hpp"
    #include "components/special/ClockComponent.hpp"
    #include "components/gates/comp4001.hpp"
    #include "components/gates/comp4011.hpp"
    #include "components/gates/comp4030.hpp"
    #include "components/gates/comp4069.hpp"
    #include "components/gates/comp4071.hpp"
    #include "components/gates/comp4081.hpp"
    #include "components/advanced/comp4040.hpp"
    #include "parser/Parser.hpp"
    #include <memory>
    #include <vector>
    #include <map>
    #include <functional>

namespace nts {

    class CircuitComponent{
        public:
            CircuitComponent();
            ~CircuitComponent();
            std::unique_ptr<IComponent> comp;
            std::string name;
            std::string type;
            Tristate standbystate = Undefined;
            int clock_up = 0;
        private:
    };

    class Circuit {
        public:
            Circuit(Parser &parser);
            ~Circuit();
            void simulate();
            void display();
            std::unique_ptr<IComponent> factory(std::string comp, std::string name);
            void setInput(std::string name, nts::Tristate state);
            char convertState(nts::Tristate state);

            // Main Functions
            static int helper(int returnValue);
            static bool IsAComponent(std::string comp, nts::Parser &parser);
            static bool NumberIsValid(std::string word);
            static void ntsLoop(nts::Parser &parser, nts::Circuit &circuit);
        protected:
        private:
            int _nbtick = 0;
            std::vector<std::unique_ptr<CircuitComponent>> _comps;
            using ComponentFactory = std::function<std::unique_ptr<nts::IComponent>()>;
            std::map<std::string, ComponentFactory> factoryMap = {
                {"input", []() { return std::make_unique<nts::InputComponent>(); }},
                {"output", []() { return std::make_unique<nts::OutputComponent>(); }},
                {"clock", []() { return std::make_unique<nts::ClockComponent>(); }},
                {"true", []() { return std::make_unique<nts::TrueComponent>(); }},
                {"false", []() { return std::make_unique<nts::FalseComponent>(); }},
                {"4001", []() { return std::make_unique<nts::comp4001>(); }},
                {"4011", []() { return std::make_unique<nts::comp4011>(); }},
                {"4030", []() { return std::make_unique<nts::comp4030>(); }},
                {"4069", []() { return std::make_unique<nts::comp4069>(); }},
                {"4071", []() { return std::make_unique<nts::comp4071>(); }},
                {"4081", []() { return std::make_unique<nts::comp4081>(); }},
                {"and", []() { return std::make_unique<nts::AndComponent>(); }},
                {"or", []() { return std::make_unique<nts::OrComponent>(); }},
                {"xor", []() { return std::make_unique<nts::XorComponent>(); }},
                {"not", []() { return std::make_unique<nts::NotComponent>(); }},
                {"4040", []() { return std::make_unique<nts::comp4040>(); }},
            };
    };
}

#endif /* !CIRCUIT_HPP_ */
