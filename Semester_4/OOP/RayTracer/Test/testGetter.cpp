#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <type_traits>

class MyClass {
public:
    int getA() const { return a; }
    std::string getB() const { return b; }
private:
    int a = 42;
    std::string b = "Hello, world!";
};

template<typename T>
struct is_getter {
    static constexpr bool value = std::is_member_function_pointer<T>::value &&
        std::is_same<typename std::result_of<T()>::type, typename std::remove_cv<typename std::remove_reference<decltype(*(std::declval<T>()) )>::type>::type>::value &&
        std::string( __PRETTY_FUNCTION__ ).find( "get" ) != std::string::npos;
};

template<typename Class>
void print_getters(const Class& obj) {
    std::vector<std::string> getters;
    for (const auto& member : obj) {
        if (is_getter<decltype(&Class::getA)>::value) {
            getters.push_back(member);
        }
    }
    std::cout << "Getters: ";
    for (const auto& getter : getters) {
        std::cout << getter << " ";
    }
    std::cout << std::endl;
}

int main() {
    MyClass obj;
    print_getters(obj);
    return 0;
}
