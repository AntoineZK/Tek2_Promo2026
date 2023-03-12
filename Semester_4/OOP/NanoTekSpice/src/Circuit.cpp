/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** Circuit
*/

#include "Circuit.hpp"

nts::Circuit::Circuit(Parser &parser)
{
    this->_comps.resize(parser.getChipsets().size());
    for (std::size_t i = 0; i < parser.getChipsets().size(); i++) {
        this->_comps[i] = std::make_unique<nts::CircuitComponent>();
        this->_comps[i]->comp = this->factory(parser.getChipsets()[i].getComp(), parser.getChipsets()[i].getName());
        this->_comps[i]->name = parser.getChipsets()[i].getName();
        this->_comps[i]->type = parser.getChipsets()[i].getComp();
    }
    for (std::size_t i = 0; i < parser.getLinks().size(); i++) {
        std::size_t comp1 = 0;
        std::size_t comp2 = 0;
        for (; comp1 < this->_comps.size(); comp1++) {
            if (this->_comps[comp1]->name == parser.getLinks()[i].getComp1())
                break;
        }
        for (; comp2 < this->_comps.size(); comp2++) {
            if (this->_comps[comp2]->name == parser.getLinks()[i].getComp2())
                break;
        }
        this->_comps[comp1]->comp->setLink(parser.getLinks()[i].getPin1(), *this->_comps[comp2]->comp, parser.getLinks()[i].getPin2());
    }
}

nts::Circuit::~Circuit()
{
}

std::unique_ptr<nts::IComponent> nts::Circuit::factory(std::string comp, std::string name)
{
    for (auto &compo : this->factoryMap) {
        if (compo.first == comp)
            return compo.second();
    }
    return nullptr;
}

void nts::Circuit::setInput(std::string name, nts::Tristate state)
{
    for (std::size_t i = 0; i < _comps.size(); i++) {
        if (_comps[i]->name == name) {
            _comps[i]->standbystate = state;
            if (_comps[i]->type == "clock")
                _comps[i]->clock_up = 1;
            return;
        }
    }
}

void nts::Circuit::simulate()
{
    this->_nbtick++;
    for (std::size_t i = 0; i < _comps.size(); i++) {
        if (_comps[i]->type == "input") {
            nts::InputComponent *derivedPtr = dynamic_cast<nts::InputComponent*>(_comps[i]->comp.get());
            derivedPtr->setState(_comps[i]->standbystate);
        }
        if (_comps[i]->type == "clock") {
            nts::ClockComponent *derivedPtr = dynamic_cast<nts::ClockComponent*>(_comps[i]->comp.get());
            if (_comps[i]->clock_up == 1) {
                derivedPtr->setState(_comps[i]->standbystate);
                _comps[i]->clock_up = 0;
            } else {
                if (derivedPtr->getState() == nts::Tristate::True)
                    derivedPtr->setState(nts::Tristate::False);
                else if (derivedPtr->getState() == nts::Tristate::False)
                    derivedPtr->setState(nts::Tristate::True);
                else
                    derivedPtr->setState(_comps[i]->standbystate);
            }
        }
        if (_comps[i]->type == "4040") {
            _comps[i]->comp->simulate(0);
        }
    }
}

char nts::Circuit::convertState(nts::Tristate state)
{
    if (state == nts::Tristate::True)
        return '1';
    if (state == nts::Tristate::False)
        return '0';
    return 'U';
}

void nts::Circuit::display()
{
    std::cout << "tick: " << this->_nbtick << std::endl;
    std::cout << "input(s):" << std::endl;
    for (std::size_t i = 0; i < _comps.size(); i++) {
        if (_comps[i]->type == "input") {
            nts::InputComponent *derivedPtr = dynamic_cast<nts::InputComponent*>(_comps[i]->comp.get());
            std::cout << "  " << _comps[i]->name << ": " << this->convertState(derivedPtr->getState()) << std::endl;
        }
        if (_comps[i]->type == "clock") {
            nts::ClockComponent *derivedPtr = dynamic_cast<nts::ClockComponent*>(_comps[i]->comp.get());
            std::cout << "  " << _comps[i]->name << ": " << this->convertState(derivedPtr->getState()) << std::endl;
        }
    }
    std::cout << "output(s):" << std::endl;
    for (std::size_t j = 0; j < _comps.size(); j++) {
        if (_comps[j]->type == "output")
            std::cout << "  " << _comps[j]->name << ": " << this->convertState(_comps[j]->comp->compute(1)) << std::endl;
    }
}

nts::CircuitComponent::CircuitComponent()
{
}

nts::CircuitComponent::~CircuitComponent()
{
}

// Main Function

int nts::Circuit::helper(int returnValue)
{
    std::cout << "USAGE" << std::endl;
    std::cout << "\t./nanotekspice file.nts" << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "\tfile.nts\tfile describing the circuit" << std::endl;
    return returnValue;
}

bool nts::Circuit::IsAComponent(std::string comp, nts::Parser &parser)
{
    for (auto &chipset : parser.getChipsets()) {
        if (chipset.getName() == comp)
            return true;
    }
    return false;
}

bool nts::Circuit::NumberIsValid(std::string word)
{
    if (word.size() == 1 && word[0] == 'U')
        return true;
    if (nts::Parser::isNumber(word) == false)
        return false;
    int number = std::stoi(word);
    if (number != 0 && number != 1)
        return false;
    return true;
}

void nts::Circuit::ntsLoop(nts::Parser &parser, nts::Circuit &circuit)
{
    std::string line;
    std::cout << "> ";
    while (std::getline(std::cin, line)) {
        if (line == "display") {
            circuit.display();
            std::cout << "> ";
            continue;
        }
        if (line == "simulate") {
            circuit.simulate();
            std::cout << "> ";
            continue;
        }
        if (line == "exit")
            break;
        std::vector<std::string> words = nts::Parser::stwa(line, " =");

        if (words.size() == 2 && nts::Circuit::IsAComponent(words[0], parser) && nts::Circuit::NumberIsValid(words[1])) {
            if (words[1] == "0")
                circuit.setInput(words[0], nts::Tristate::False);
            else if (words[1] == "1")
                circuit.setInput(words[0], nts::Tristate::True);
            else
                circuit.setInput(words[0], nts::Tristate::Undefined);
            std::cout << "> ";
            continue;
        }
        std::cout << "> ";
    }
}
