/*
** EPITECH PROJECT, 2025
** StoneAnalysis
** File description:
** Math.cpp
*/


#include "Math.hpp"

#include <cmath>

namespace stone {
    std::vector<std::complex<double>> Math::fft(const std::vector<std::complex<double>>& input)
    {
        int N = input.size();
        if (N == 1)
            return input;

        std::vector<std::complex<double>> even(N / 2);
        std::vector<std::complex<double>> odd(N / 2);
        for (int i = 0; i < N / 2; ++i) {
            even[i] = input[2 * i];
            odd[i]  = input[2 * i + 1];
        }

        auto eventFFT = fft(even);
        auto oddFFT  = fft(odd);

        std::vector<std::complex<double>> output(N);
        for (int k = 0; k < N / 2; ++k) {
            std::complex<double> w = std::polar(1.0, -2 * M_PI * k / N);
            output[k] = eventFFT[k] + w * oddFFT[k];
            output[k + N/2] = eventFFT[k] - w * oddFFT[k];
        }
        return output;
    }

    std::vector<std::complex<double>> Math::ifft(const std::vector<std::complex<double>>& input) 
    {
        int N = input.size();
        
        std::vector<std::complex<double>> conjugatedInput(N);
        for (int i = 0; i < N; i++)
            conjugatedInput[i] = std::conj(input[i]);
        
        std::vector<std::complex<double>> fftResult = fft(conjugatedInput);

        for (int j = 0; j < N; j++)
            fftResult[j] = std::conj(fftResult[j]) / static_cast<double>(N);
        
        return fftResult;
    }

    std::vector<std::complex<double>> Math::samplesToFFT(const std::vector<int16_t>& samples)
    {
        std::vector<std::complex<double>> complexSamples(samples.size());
        for (size_t i = 0; i < samples.size(); i++) {
            complexSamples[i] = std::complex<double>(samples[i], 0);
        }
        return fft(complexSamples);
    }
}