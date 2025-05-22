/*
** EPITECH PROJECT, 2025
** StoneAnalysis
** File description:
** Analyzer
*/

#include "Analyzer.hpp"
#include <iomanip>
#include <iostream>
#include "../Audio/AudioParser.hpp"
#include "../Math.hpp"
#include "ATool.hpp"

namespace stone {

    Analyzer::Analyzer(const std::string& inputFilename, int topN):
        ATool(inputFilename),
        _topN(topN) {}

    int Analyzer::execute() const {
        stone::AudioParser parser;
        if (!parser.load(_inputFilename)) {
            std::cerr << "Error: Unable to load file " << _inputFilename << std::endl;
            return 84;
        }

        const auto& samples = parser.getSamples();

        if (samples.empty()) {
            std::cerr << "Error: No samples found in the file." << std::endl;
            return 84;
        }

        auto complexSamples = stone::Math::sampleToComplex(samples);
        size_t originalSize = complexSamples.size();
        size_t targetSize = stone::Math::nextPow2(complexSamples.size());
        if (targetSize > originalSize)
            complexSamples.resize(targetSize, std::complex<double>(0.0, 0.0));
        auto fftResult = stone::Math::fft(complexSamples);
        uint32_t sampleRate = parser.getSampleRate();
        auto topFrequencies = stone::Math::getTopFrequencies(fftResult, _topN, sampleRate);
        std::cout << "Top " << _topN << " frequencies:" << std::endl;
        for (const auto& [freq, mag] : topFrequencies) {
            std::cout << std::fixed << std::setprecision(1) << freq << " Hz" << std::endl;
        }
        return 0;
    }

    int Analyzer::getTopN() const {
        return _topN;
    }
}