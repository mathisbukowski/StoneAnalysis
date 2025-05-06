/*
** EPITECH PROJECT, 2025
** StoneAnalysis
** File description:
** ITool
*/

#ifndef ITOOL_HPP_
#define ITOOL_HPP_

#include <string>

namespace stone {
    class ITool {
        public:
            virtual ~ITool() = default;

            virtual int execute() const = 0;
    };
}

#endif /* !ITOOL_HPP_ */
