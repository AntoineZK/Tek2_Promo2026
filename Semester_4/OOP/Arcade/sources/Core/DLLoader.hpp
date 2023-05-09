/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-antoine.khalidy
** File description:
** DLLoader
*/

#pragma once
#include <memory>
#include <string>
#include <exception>
#include <iostream>
#include <dlfcn.h>

namespace arcade {
    class DLLoader {
        public:
            class DLLoaderException : public std::exception {
                public:
                    DLLoaderException(std::string const &message) : _message(message) {}
                    const char *what() const noexcept { return this->_message.c_str(); }
                private:
                    std::string _message;
            };

            DLLoader(std::string const &path)
            {
                this->_handle = dlopen(path.c_str(), RTLD_LAZY);
                if (!this->_handle)
                    throw DLLoaderException("Error: " + std::string(dlerror()));
            }

            ~DLLoader()
            {
                dlclose(this->_handle);
                this->_handle = nullptr;
            }

            template <typename T>
            T *getInstance(std::string const &entryPoint)
            {
                if (!this->_handle)
                    throw DLLoaderException("Error: library not opened");
                auto ptr = dlsym(this->_handle, entryPoint.c_str());
                T *entryPointFunc = reinterpret_cast<T *>(ptr);
                char *error = dlerror();
                if (entryPointFunc == nullptr && error != nullptr)
                    throw DLLoaderException("Error: " + std::string(error));
                return entryPointFunc;
            }
        private:
            void *_handle;
    };
}
