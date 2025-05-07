/*
** EPITECH PROJECT, 2025
** StoneAnalysis
** File description:
** Analyzer
*/

#include "Analyzer.hpp"

namespace stone {
    
    Analyzer::Analyzer(const std::string& inputFilename, int topN):
        ATool(inputFilename),
        _topN(topN) {}
    
    int Analyzer::execute() const {
        return 0;
    }

    int Analyzer::getTopN() const {
        return _topN;
    }
};