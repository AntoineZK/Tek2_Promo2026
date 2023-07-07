/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** CreatePlugin
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

std::string name = "";

int createNewInfra(std::string oldPath, std::string newPath)
{
    //verify if old path exist
    if (!std::filesystem::exists(oldPath)) {
        std::cerr << "Error: " << oldPath << " doesn't exist" << std::endl;
        return 84;
    }

    // verify if is a folder
    if (!std::filesystem::is_directory(oldPath)) {
        std::cerr << "Error: " << oldPath << " is not a folder" << std::endl;
        return 84;
    }

    // verify if new path exist
    if (!std::filesystem::exists(newPath)) {
        std::cerr << "Infos: " << newPath << " doesn't exist create it" << std::endl;
        std::filesystem::create_directory(newPath);
    } else {
        std::cerr << "Error: " << newPath << " already exist" << std::endl;
        return 84;
    }

    // verify if is a folder
    if (!std::filesystem::is_directory(newPath)) {
        std::cerr << "Error: " << newPath << " is not a folder" << std::endl;
        return 84;
    }

    // copy recursivly all files from old to new
    std::filesystem::copy(oldPath, newPath, std::filesystem::copy_options::recursive);

    // load MakefileTemplate.txt
    std::ifstream file("./Bin/UpdatePlugins/MakefileTemplate.txt");
    std::string str;
    std::string makefile;

    if (file.is_open()) {
        while (std::getline(file, str))
            makefile += str + "\n";
    } else {
        std::cerr << "Error: can't open MakefileTemplate.txt" << std::endl;
        return 84;
    }

    file.close();

    // replace all occurence of TEST by the name of the folder
    name = newPath.substr(newPath.find_last_of("/") + 1);

    while (makefile.find("TEST") != std::string::npos)
        makefile.replace(makefile.find("TEST"), 4, name);

    // write Makefile in new folder
    std::ofstream newFile(newPath + "/Makefile");
    newFile << makefile;

    newFile.close();

    return 0;
}

int addConfigOnPrincipalMakefile(std::string newPath)
{
    // load Makefile
    std::ifstream file("Makefile");
    std::string str;
    std::string makefile;

    if (file.is_open())
        while (std::getline(file, str))
            makefile += str + "\n";

    file.close();

    // fnd th #insertion point in the makefile
    std::string insertionPoint = "#insertion point";
    std::size_t findPos = makefile.find(insertionPoint);
    if (findPos == std::string::npos) {
        std::cerr << "Error: insertion point not found" << std::endl;
        return 84;
    } else {
        // find the last occurrence of '/'
        size_t pos = newPath.find_last_of('/');

        // extract the sub string until the last occurrence of '/'
        std::string pathToFolder = newPath.substr(0, pos);

        // verify if makefile rule already exist
        if (makefile.find(name) != std::string::npos) {
            std::cerr << "Error: makefile rule already exist" << std::endl;
            return 84;
        }

        // insert the new config
        makefile.insert(findPos, name + ":\n\t@make -C " + pathToFolder + "\n\nclean_" + name + ":\n\t@make clean -C " + pathToFolder + "\n\nfclean_" + name + ":\n\t@make fclean -C " + pathToFolder + "\n\n");
        std::ofstream newFile("Makefile");
        newFile << makefile;
        newFile.close();
    }

    return 0;
}

int main(int ac, char **av)
{
    if (ac != 3) {
        std::cerr << "Usage: ./UpadePlugin [path/to/old/version/!folder!] [path/to/new/version/!folder!]" << std::endl;
        return 84;
    }

    std::string oldPath = av[1];
    std::string newPath = av[2];

    if (createNewInfra(oldPath, newPath) != 0)
        return 84;

    if (addConfigOnPrincipalMakefile(newPath) != 0)
        return 84;

    return 0;
}