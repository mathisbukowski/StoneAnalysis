/*
** EPITECH PROJECT, 2025
** G-CNA-400-LIL-4-1-stoneanalysis-mathis.bukowski
** File description:
** Cypher
*/

#include "./Cypher.hpp"

#include <bitset>
#include <complex>
#include <fstream>
#include <iostream>
#include <list>

#include "../Math.hpp"
#include "../Audio/AudioParser.hpp"

stone::Cypher::Cypher(const std::string& inputFilename, const std::string& outputFilename, const std::string& message): ATool(inputFilename)
{
    this->_outputFilename = outputFilename;
    this->_message = message;
}

std::vector<bool> stringToBits(const std::string& message)
{
    std::vector<bool> bits;

    for (const char c : message) {
        for (int i = 7; i >= 0; i--) {
            bits.push_back((c >> i) & 1);
        }
    }
    return bits;
}

std::vector<bool> intToBits(int nb, int len)
{
    std::vector<bool> bits(len);

    for (int i = 0; i < len; ++i) {
        bits[len - 1 - i] = (nb >> i) & 1;
    }
    return bits;
}

int stone::Cypher::execute() const
{
    AudioParser parser;
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

    // 2: Apply FFT on each frame
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
    if (!found || fftFrames.empty()) {
        std::cerr << "No valid frame found to encode the message." << std::endl;
        return 84;
    }
    std::vector<std::complex<double>>& fftBlock = fftFrames[validFrameIndex];


    // 3: Change bits of each frame

    // Encode message len
    std::vector<bool> lenBits = intToBits(static_cast<uint16_t>(this->_message.size()), 16);
    std::vector<bool> msgBits = stringToBits(this->_message);
    std::vector<bool> bits = lenBits;
    bits.insert(bits.end(), msgBits.begin(), msgBits.end());

    // Encode message
    for (size_t i = 0; i < bits.size(); ++i) {
        const size_t k = 1 + i;
        if (k >= fftBlock.size() / 2) break;

        double magnitude = std::abs(fftBlock[k]);
        double phase = bits[i] ? M_PI : 0.0;

        fftBlock[k] = std::polar(magnitude, phase);

        size_t mirrorIndex = fftBlock.size() - k;
        if (mirrorIndex < fftBlock.size() && mirrorIndex != k)
            fftBlock[mirrorIndex] = std::conj(fftBlock[k]);
    }

    fftFrames[validFrameIndex] = fftBlock;

    // 4: decode with ifft to write the wav
    std::vector<int16_t> outputSamples;
    for (std::vector<std::complex<double>>& frame: fftFrames) {
        std::vector<std::complex<double>> timeDomain = Math::ifft(frame);

        for (const std::complex<double>& c : timeDomain) {
            double value = c.real();
            if (value > 32767) value = 32767;
            if (value < -32768) value = -32768;

            outputSamples.push_back(static_cast<int16_t>(value));
        }
    }

    // 5: Write to file
    std::ofstream outputFile(this->_outputFilename);

    outputFile.write(parser.getHeader().data(), parser.getHeader().size());
    for (int16_t& c : outputSamples) {
        outputFile.write(reinterpret_cast<const char*>(&c), sizeof(int16_t));
    }

    outputFile.close();

    return 0;
}
