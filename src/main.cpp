/*
** EPITECH PROJECT, 2025
** StoneAnalysis
** File description:
** main
*/

#include <iostream>
#include "Audio/AudioParser.hpp"
#include "Math.hpp"
#include "Factory/ToolFactory.hpp"


int main(int ac, char **av)
{
    auto tool = stone::ToolFactory::createFromArgs(ac, av);
    if (!tool) {
        std::cerr << "Invalid arguments" << std::endl;
        return 84;
    }
    int result = tool->execute();
    if (result != 0) {
        std::cerr << "Error executing tool" << std::endl;
        return result;
    }
    return 0;
}
