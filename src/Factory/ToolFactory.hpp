/*
** EPITECH PROJECT, 2025
** StoneAnalysis
** File description:
** ToolFactory
*/

#ifndef TOOLFACTORY_HPP_
#define TOOLFACTORY_HPP_

#include <memory>
#include "ITool.hpp"

namespace stone {
    class ToolFactory {
        public:
            static std::unique_ptr<ITool> createFromArgs(int argc, char **argv);
    };
}

#endif /* !TOOLFACTORY_HPP_ */
