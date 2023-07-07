/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** INetwork
*/

#pragma once
    #include "../../MainRaytracer/Include/Include.hpp"
    #include "../../ExternClient/src/Raytracing/Math/Vector3D.hpp"

// Surcharge de la fonction stringify pour les types intégraux
template <typename T, typename std::enable_if<std::is_integral<T>::value>::type* = nullptr>
std::string stringify(const T& value) {
    std::stringstream ss;
    ss << value;
    return ss.str();
}

// Surcharge de la fonction stringify pour les chaînes de caractères
template <typename T, typename std::enable_if<std::is_same<T, std::string>::value>::type* = nullptr>
std::string stringify(const T& value) {
    return value;
}

// Surcharge de la fonction stringify pour les types flottants
template <typename T, typename std::enable_if<std::is_floating_point<T>::value>::type* = nullptr>
std::string stringify(const T& value) {
    std::stringstream ss;
    ss << value;
    return ss.str();
}

// Surcharge de la fonction stringify pour les const char *
template <typename T, typename std::enable_if<std::is_same<T, const char *>::value>::type* = nullptr>
std::string stringify(const T& value) {
    std::stringstream ss;
    ss << value;
    return ss.str();
}

// Surcharge de la fonction stringify pour les std::vector<int>
template <typename T, typename std::enable_if<std::is_same<T, std::vector<int>>::value>::type* = nullptr>
std::string stringify(const T& value) {
    std::stringstream ss;
    for (int i = 0; i < (int) value.size(); i++) {
        ss << value[i] << ",";
    }
    return ss.str();
}

// Surcharge de la fonction stringify pour les std::pair<std::pair<int, int>, std::pair<int, int>>
template <typename T, typename std::enable_if<std::is_same<T, std::pair<std::pair<int, int>, std::pair<int, int>>>::value>::type* = nullptr>
std::string stringify(const T& value) {
    std::stringstream ss;
    ss << value.first.first << "," << value.first.second << "," << value.second.first << "," << value.second.second;
    return ss.str();
}

// Surcharge de la fonction stringify pour les std::vector<std::pair<std::pair<int, int>, Color>>
template <typename T, typename std::enable_if<std::is_same<T, std::vector<std::pair<std::pair<int, int>, Color>>>::value>::type* = nullptr>
std::string stringify(const T& value) {
    std::stringstream ss;
    for (auto &i : value) {
        ss << i.first.first << "," << i.first.second << "," << i.second.getR() << "," << i.second.getG() << "," << i.second.getB() << ",";
    }
    return ss.str();
}

#pragma pack(push, 1)
class Packet{
    public:
        Packet();
        ~Packet();
        template <typename... Args>
        void serialize(char separator, Args... args) {
            std::stringstream ss;
            ((ss << stringify(args) << separator), ...);
            std::string result = ss.str();
            if (!result.empty()) {
                result.erase(result.length() - 1);
            }
            _size = result.length();
            _separator = separator;
            for (int i = 0; i < (int) result.length(); i++) {
                _body[i] = result[i];
            }
            _body[result.length()] = '\0';
            // fill le rest du body avec des \0
            for (int i = result.length() + 1; i < (int) sizeof(_body); i++) {
                _body[i] = '\0';
            }
        }
        std::vector<std::string> deserialize();
        void clearBody();
        void addToBody(std::string &body);
        std::string getBody() const;
        int getSize() const;
        void addLetterToBody(char c, int index);
    protected:
    private:
        char _separator;
        int _size;
        char _body[2048];
};
#pragma pack(pop)

class INetwork {
    public:
        ~INetwork() = default;
        // virtual void init() = 0;
        virtual void init(const char *, int) = 0;
        virtual std::vector<std::string> receive(int) = 0;
        virtual void closefd(int) = 0;
    protected:
    private:
};
