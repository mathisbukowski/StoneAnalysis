/*
** EPITECH PROJECT, 2025
** StoneAnalysis
** File description:
** AudioParser
*/

#include "AudioParser.hpp"
#include <iostream>
#include <fstream>

namespace stone {
    bool AudioParser::load(const std::string& inputFilename)
    {
        std::ifstream file(inputFilename, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Error: Unable to open file " << inputFilename << std::endl;
            return false;
        }
        _header.resize(44);
        if (!parseHeader(file))
            return false;
        if (!parseSamples(file))
            return false;
        file.close();
        return true;
    }

    bool AudioParser::parseHeader(std::ifstream& file)
    {
        char riff[4], wave[4];
        
        file.read(riff, 4);
        file.ignore(4);
        file.read(wave, 4);
        if (std::string(riff, 4) != "RIFF" || std::string(wave, 4) != "WAVE") {
            std::cerr << "Error: invalid WAV file (incorrect format)" << std::endl;
            return false;
        }
        return true;
    }

    bool AudioParser::parseSamples(std::ifstream& file)
    {
        std::string foundChunk;

        while (file) {
            char id[4];
            uint32_t size = 0;

            if (!file.read(id, 4)) 
                break;
            if (!file.read(reinterpret_cast<char*>(&size), sizeof(size)))
                break;

            std::string chunkId(id, 4);

            if (chunkId == "fmt ") {
                file.seekg(size, std::ios::cur);
            } else if (chunkId == "data") {
                _samples.resize(size / sizeof(int16_t));
                file.read(reinterpret_cast<char*>(_samples.data()), size);
                return true;
            } else {
                file.seekg(size, std::ios::cur);
            }
        }

        std::cerr << "Error: no 'data' chunk found" << std::endl;
        return false;
    }
}
