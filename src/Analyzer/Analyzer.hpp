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

namespace stone {
    class Analyzer : public ATool {
        public:
            Analyzer(const std::string& inputFilename, int topN);

            int execute() const override;

            std::vector<std::pair<double, double>> getData() const;

            void setData(const std::vector<std::pair<double, double>>& data);

            int getTopN() const;

        private:
            int _topN;
            std::vector<std::pair<double, double>> _data;
    };
}

#endif /* !ANALYZER_HPP_ */
