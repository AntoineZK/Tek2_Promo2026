#include <iostream>
#include <sstream>

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

// Surcharge de la fonction stringify pour la classe personnalisée
std::string stringify(const Test& test) {
    std::stringstream ss;
    ss << "{name: " << test.getName() << ", description: " << test.getDescription() << "}";
    return ss.str();
}

// Surcharge de la fonction stringify pour la classe personnalisée 2
std::string stringify(const Test2& test) {
    std::stringstream ss;
    ss << "{name: " << test.getName() << ", description: " << test.getDescription() << ", a: " << test.getA() << stringify(test.getTest()) << "}" << std::endl;
    return ss.str();
}

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

// Fonction template variadique pour concaténer les éléments, y compris les objets de la classe personnalisée
template <typename... Args>
std::string concatenate(Args... args) {
    std::stringstream ss;
    std::string separator = ", ";
    ((ss << stringify(args) << separator), ...);  // Utilisation du "fold expression" C++17
    std::string result = ss.str();
    if (!result.empty()) {
        result.erase(result.length() - separator.length());
    }
    return result;
}

int main() {
    Test test("my test", "this is a test object");
    Test test2("my test2", "this is a test object2");
    Test2 test4("my test3", "this is a test object3", 42, test2);
    std::string test3 = "test3";
    std::cout << concatenate(1, test3, 2.3, test, test2, test4) << std::endl;
    return 0;
}
