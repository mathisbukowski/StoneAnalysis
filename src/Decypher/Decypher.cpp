/*
** EPITECH PROJECT, 2025
** StoneAnalysis
** File description:
** Decypher
*/

#include "Decypher.hpp"

#include <complex>
#include <iostream>

#include "../Math.hpp"
#include "../Audio/AudioParser.hpp"

stone::Decypher::Decypher(const std::string& inputFilename): ATool(inputFilename)
{}


int stone::Decypher::execute() const
{
    stone::AudioParser parser;
    if (!parser.load(_inputFilename)) {
        std::cerr << "Error: Unable to load file " << _inputFilename << std::endl;
        return 84;
    }

    const std::vector<int16_t>& samples = parser.getSamples();

    if (samples.empty()) {
        std::cerr << "Error: No samples found in the file." << std::endl;
        return 84;
    }

    const size_t nbFrame = samples.size() / 1024;
    const size_t remain = samples.size() % 1024;

    // 1: Divide data into frames of 1024 samples
    std::vector<std::vector<int16_t>> frames;
    size_t sampleIndex = 0;
    for (size_t i = 0; i < nbFrame; i++) {
        frames.emplace_back();
        for (size_t y = 0; y < 1024; y++) {
            sampleIndex = i * 1024 + y;
            frames[i].push_back(samples[sampleIndex]);
        }
    }
    if (remain > 0) {
        frames.emplace_back();
        for (size_t i = 0; i < remain; i++) {
            frames[nbFrame].push_back(samples[samples.size() - (remain - i)]);
        }
    }

    std::vector<std::vector<std::complex<double>>> fftFrames;
    for (const auto& frame : frames) {
        std::vector<std::complex<double>> complexSamples = Math::sampleToComplex(frame);

        size_t targetSize = Math::nextPow2(complexSamples.size());
        complexSamples.resize(targetSize, std::complex<double>(0, 0));

        fftFrames.push_back(Math::fft(complexSamples));
    }

    std::vector<std::complex<double>> fftBlock = fftFrames[0];
    std::vector<bool> bits;
    for (size_t i = 0; i < 33; i++) {
        size_t k = 1 + i;
        if (k >= fftBlock.size()) break;

        double phase = std::arg(fftBlock[k]);
        if (phase < 0) phase += 2 * M_PI;
            bool bit = std::abs(phase - M_PI) < 0.5;
        bits.push_back(bit);
    }

    std::string result;
    for (size_t i = 0; i + 7 < bits.size(); i += 8) {
        uint8_t c = 0;
        for (int b = 0; b < 8; ++b) {
            c = (c << 1) | bits[i + b];
        }
        if (c == '\0') break;
        result += static_cast<char>(c);
    }
    std::cout << "Message caché : " << result << std::endl;
    return 0;
}
