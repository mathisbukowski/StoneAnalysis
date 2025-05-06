/*
** EPITECH PROJECT, 2025
** StoneAnalysis
** File description:
** Decypher
*/

#ifndef DECYPHER_HPP_
#define DECYPHER_HPP_

#include "ATool.hpp"
#include <string>

namespace stone {
    class Decypher : public ATool {
        public:
            Decypher(const std::string& inputFilename);

            int execute() const override;
            std::string _message;
    };
}

#endif /* !DECYPHER_HPP_ */

