/*
** EPITECH PROJECT, 2025
** StoneAnalysis
** File description:
** AudioParser
*/

#ifndef AUDIOPARSER_HPP_
#define AUDIOPARSER_HPP_

#include <string>
#include <vector>
#include <cstdint>

namespace stone {
    class AudioParser {
    public:
        AudioParser() = default;
        ~AudioParser() = default;

        bool load(const std::string& inputFilename);

        const std::vector<int16_t>& getSamples() const { return _samples; };
        uint16_t getNumChannels() const { return _numChannels; };
        uint32_t getSampleRate() const { return _sampleRate; };
        uint16_t getBitsPerSample() const { return _bitsPerSample; };
        [[nodiscard]] std::vector<char> getHeader() const { return _header; };

    private:
        std::vector<int16_t> _samples;
        std::vector<char> _header;

        uint16_t _numChannels = 0;
        uint32_t _sampleRate = 0;
        uint16_t _bitsPerSample = 0;

        bool parseHeaderAndData(std::ifstream& file);
    };
}

#endif /* !AUDIOPARSER_HPP_ */
