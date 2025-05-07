/*
** EPITECH PROJECT, 2025
** StoneAnalysis
** File description:
** ToolFactory
*/

#include "ITool.hpp"
#include "ToolFactory.hpp"

#include "../Analyzer/Analyzer.hpp"
#include "../Cypher/Cypher.hpp"
#include "../Decypher/Decypher.hpp"

namespace stone {
    std::unique_ptr<ITool> ToolFactory::createFromArgs(int argc, char **argv)
    {
        if (argc < 2) {
            return nullptr;
        }
        std::string toolType = argv[1];
        if (toolType == "--analyzer") {
            if (argc != 4) {
                return nullptr;
            }
            return std::make_unique<Analyzer>(argv[2], std::stoi(argv[3]));
        }
        // } else if (toolType == "--cypher") {
        //     if (argc != 5) {
        //         return nullptr;
        //     }
        //     return std::make_unique<Cypher>(argv[2], argv[3], argv[4]);
        // } else if (toolType == "--decypher") {
        //     if (argc != 3) {
        //         return nullptr;
        //     }
        //     return std::make_unique<Decypher>(argv[2]);
        // }
        return nullptr;
    }
}
