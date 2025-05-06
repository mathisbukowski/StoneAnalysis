/*
** EPITECH PROJECT, 2025
** StoneAnalysis
** File description:
** Cypher
*/

#ifndef CYPHER_HPP_
#define CYPHER_HPP_

#include <string>
#include <vector>
#include "ATool.hpp"

namespace stone {
    class Cypher : public ATool {
        public:
            Cypher(const std::string& inputFilename,
                    const std::string& outputFilename,
                    const std::string& message);

            int execute() const override;

        private:
            std::string _outputFilename;
            std::string _message;
    };
}

#endif /* !CYPHER_HPP_ */
