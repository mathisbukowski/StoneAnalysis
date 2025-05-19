/*
** EPITECH PROJECT, 2025
** StoneAnalysis
** File description:
** Math.cpp
*/


#include "Math.hpp"

#include <cmath>
#include <algorithm>

namespace stone {
    std::vector<std::complex<double>> Math::fft(std::vector<std::complex<double>>& input)
    {
        const size_t N = input.size();
        const double PI = std::acos(-1);

        size_t j = 0;
        for (size_t i = 1; i < N; ++i) {
            size_t bit = N >> 1;
            while (j & bit) {
                j ^= bit;
                bit >>= 1;
            }
            j ^= bit;

            if (i < j)
                std::swap(input[i], input[j]);
        }
        for (size_t len = 2; len <= N; len <<= 1) {
            double angle = -2 * PI / len;
            std::complex<double> wlen(std::cos(angle), std::sin(angle));
            for (size_t i = 0; i < N; i += len) {
                std::complex<double> w(1.0, 0.0);
                for (size_t j = 0; j < len / 2; ++j) {
                    std::complex<double> u = input[i + j];
                    std::complex<double> v = input[i + j + len / 2] * w;
                    input[i + j] = u + v;
                    input[i + j + len / 2] = u - v;
                    w *= wlen;
                }
            }
        }
        return input;
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


    std::vector<std::complex<double>> Math::sampleToComplex(const std::vector<int16_t>& samples)
    {
        std::vector<std::complex<double>> complexSamples(samples.size());
        for (size_t i = 0; i < samples.size(); i++) {
            complexSamples[i] = std::complex<double>(samples[i], 0);
        }
        return complexSamples;
    }

    std::vector<std::pair<double, double>> Math::getTopFrequencies(
        const std::vector<std::complex<double>>& fftResult,
        int topN)
    {
        std::vector<std::pair<double, double>> frequencies;
        size_t N = fftResult.size();
    
        for (size_t i = 0; i < N / 2; ++i) {
            double magnitude = std::abs(fftResult[i]);
            double frequency = static_cast<double>(i) * 48000 / N;
            frequencies.emplace_back(frequency, magnitude);
        }
        std::sort(frequencies.begin(), frequencies.end(), [](const auto& a, const auto& b) {
            return a.second > b.second;
        });
        if (frequencies.size() > static_cast<size_t>(topN))
            frequencies.resize(topN);
        return frequencies;
    }

    size_t Math::nextPow2(size_t n) {
        size_t p = 1;
        while (p < n) p *= 2;
        return p;
    }
}
