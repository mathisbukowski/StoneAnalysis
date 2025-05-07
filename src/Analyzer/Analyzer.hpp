/*
** EPITECH PROJECT, 2025
** StoneAnalysis
** File description:
** Analyzer
*/

#ifndef ANALYZER_HPP_
#define ANALYZER_HPP_

#include <vector>
#include "ATool.hpp"
#include <string>
#include <complex>

namespace stone {
    class Analyzer : public ATool {
        public:
            Analyzer(const std::string& inputFilename, int topN);

            int execute() const override;

            int getTopN() const;

        private:
            int _topN;
    };
}

#endif /* !ANALYZER_HPP_ */
