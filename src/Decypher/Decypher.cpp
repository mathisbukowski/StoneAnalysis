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

    // Choose first valid fft block
    size_t validFrameIndex = 0;
    bool found = false;
    for (size_t i = 0; i < fftFrames.size(); i++) {
        double energy = 0.0;
        for (const auto& c : fftFrames[i])
            energy += std::abs(c);
        if (energy > 1e-3) {
            validFrameIndex = i;
            found = true;
            break;
        }
    }
    if (!found) {
        std::cerr << "No valid frame found to decode the message." << std::endl;
        return 84;
    }
    std::vector<std::complex<double>>& fftBlock = fftFrames[validFrameIndex];

    std::vector<bool> bits;
    const size_t maxBits = std::min((fftBlock.size() / 2 - 1), static_cast<size_t>(1022));
    size_t k;

    for (size_t i = 0; i < maxBits; i++) {
        k = 1 + i;
        if (k >= fftBlock.size()) break;

        double phase = std::arg(fftBlock[k]);
        if (phase < 0)
            phase += 2 * M_PI;
        const bool bit = std::abs(phase - M_PI) < 0.5;
        bits.push_back(bit);
    }

    // Get message size
    uint16_t msgLen = 0;
    for (int i = 0; i < 16; i++) {
        msgLen = (msgLen << 1) | bits[i];
    }

    if (bits.size() < (size_t)(16 + msgLen * 8)) {
        std::cerr << "Error: not enough byte to decode message." << std::endl;
        return 84;
    }

    std::string result;
    for (size_t i = 0; i < msgLen; i++) {
        uint8_t c = 0;
        for (int b = 0; b < 8; b++) {
            c = (c << 1) | bits[16 + i * 8 + b];
        }
        if (c == '\0') break;
        result += static_cast<char>(c);
    }

    std::cout << result << std::endl;
    return 0;
}
