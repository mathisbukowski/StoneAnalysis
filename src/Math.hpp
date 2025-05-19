/*
** EPITECH PROJECT, 2025
** StoneAnalysis
** File description:
** Math.hpp
*/

#ifndef MATH_HPP
#define MATH_HPP

#include <vector>
#include <complex>



namespace stone {
    class Math {
    public:
        static std::vector<std::complex<double>> sampleToComplex(const std::vector<int16_t>& samples);
        static std::vector<std::complex<double>> ifft(const std::vector<std::complex<double>>& input);
        static std::vector<std::complex<double>> fft(std::vector<std::complex<double>>& input);
        static std::vector<std::pair<double, double>> getTopFrequencies(const std::vector<std::complex<double>>& fftResult, int topN, uint32_t sampleRate);
        static size_t nextPow2(size_t n);
    };
}

#endif
