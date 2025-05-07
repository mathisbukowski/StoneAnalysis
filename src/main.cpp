/*
** EPITECH PROJECT, 2025
** StoneAnalysis
** File description:
** main
*/

#include <iostream>
#include "Audio/AudioParser.hpp"
#include "Math.hpp"

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

    auto fftResult = stone::Math::samplesToFFT(samples);
    auto ifftResult = stone::Math::ifft(fftResult);

    for (size_t i = 0; i < fftResult.size() / 2; ++i) {
        std::cout << "FFT[" << i << "]: " << fftResult[i].real()
                  << " | IFFT[" << i << "]: " << ifftResult[i].real() << std::endl;
    }

    
    std::cout << "Test passed." << std::endl;
    return 0;
}
