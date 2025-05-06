/*
** EPITECH PROJECT, 2025
** StoneAnalysis
** File description:
** main
*/

#include <iostream>
#include "Audio/AudioParser.hpp"

int main(void)
{
    stone::AudioParser audio;

    if (!audio.load("test.wav")) {
        std::cerr << "Test failed: could not load WAV file." << std::endl;
        return 1;
    }

    const auto& samples = audio.getSamples();
    const auto& header = audio.getHeader();

    std::cout << "Header size: " << header.size() << " bytes" << std::endl;
    std::cout << "Number of samples: " << samples.size() << std::endl;

    for (size_t i = 0; i < std::min(samples.size(), size_t(10)); ++i) {
        std::cout << "Sample[" << i << "]: " << samples[i] << std::endl;
    }

    std::cout << "Test passed." << std::endl;
    return 0;
}
