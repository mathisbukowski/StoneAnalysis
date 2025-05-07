/*
** EPITECH PROJECT, 2025
** StoneAnalysis
** File description:
** main
*/

#include <iostream>
#include "Audio/AudioParser.hpp"
#include "Math.hpp"
#include "Factory/ToolFactory.hpp"

size_t nextPow2(size_t n) {
    size_t p = 1;
    while (p < n) p *= 2;
    return p;
}

int main(int ac, char **av)
{

    // stone::AudioParser audio;

    // if (!audio.load("test.wav")) {
    //     std::cerr << "Test failed: could not load WAV file." << std::endl;
    //     return 1;
    // }

    // const auto& samples = audio.getSamples();
    // const auto& header = audio.getHeader();

    // std::cout << "Header size: " << header.size() << " bytes" << std::endl;
    // std::cout << "Number of samples: " << samples.size() << std::endl;

    // const double EPS = 1e-10;

    // auto complexSamples = stone::Math::sampleToComplex(samples);
    // size_t targetSize = nextPow2(complexSamples.size());
    // complexSamples.resize(targetSize, std::complex<double>(0, 0));

    // auto fftResult = stone::Math::fft(complexSamples);
    // auto ifftResult = stone::Math::ifft(fftResult);

    // for (size_t i = 0; i < samples.size(); i++) {
    //     if (std::abs(complexSamples[i] - ifftResult[i]) > EPS) {
    //         std::cout << "Mismatch at index " << i
    //                   << ": " << samples[i]
    //                   << " vs " << ifftResult[i] << "\n";
    //     }
    // }

    // std::cout << "Test passed." << std::endl;
    // return 0;

    auto tool = stone::ToolFactory::createFromArgs(ac, av);
    if (!tool) {
        std::cerr << "Invalid arguments" << std::endl;
        return 84;
    }
    int result = tool->execute();
    if (result != 0) {
        std::cerr << "Error executing tool" << std::endl;
        return result;
    }
    return 0;
}
