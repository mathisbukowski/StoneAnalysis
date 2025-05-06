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

            const std::vector<uint16_t>& getSamples() const { return _samples; };

            const std::vector<uint16_t>& getHeader() const { return _header; };

            bool load(const std::string& inputFilename);

        private:
            std::vector<uint16_t> _samples;
            std::vector<uint16_t> _header;

            bool parseHeader(std::ifstream& file);

            bool parseSamples(std::ifstream& file);
    };
}

#endif /* !AUDIOPARSER_HPP_ */
