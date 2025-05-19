/*
** EPITECH PROJECT, 2025
** StoneAnalysis
** File description:
** AudioParser
*/

#include "AudioParser.hpp"
#include <iostream>
#include <fstream>
#include <cstring>

namespace stone {
    bool AudioParser::load(const std::string& inputFilename)
    {
        std::ifstream file(inputFilename, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Error: Unable to open file " << inputFilename << std::endl;
            return false;
        }

        bool success = parseHeaderAndData(file);
        file.close();
        return success;
    }

    bool AudioParser::parseHeaderAndData(std::ifstream& file)
    {
        char buffer[4];

        file.read(buffer, 4);
        if (std::string(buffer, 4) != "RIFF") {
            std::cerr << "Error: Missing RIFF header" << std::endl;
            return false;
        }
        file.ignore(4);
        file.read(buffer, 4);
        if (std::string(buffer, 4) != "WAVE") {
            std::cerr << "Error: Missing WAVE format" << std::endl;
            return false;
        }

        bool fmtFound = false, dataFound = false;
        uint32_t dataSize = 0;
        while (file.read(buffer, 4)) {
            uint32_t chunkSize = 0;
            file.read(reinterpret_cast<char*>(&chunkSize), sizeof(chunkSize));
            std::string chunkId(buffer, 4);

            if (chunkId == "fmt ") {
                uint16_t audioFormat;
                file.read(reinterpret_cast<char*>(&audioFormat), sizeof(audioFormat));
                file.read(reinterpret_cast<char*>(&_numChannels), sizeof(_numChannels));
                file.read(reinterpret_cast<char*>(&_sampleRate), sizeof(_sampleRate));
                file.ignore(6);
                file.read(reinterpret_cast<char*>(&_bitsPerSample), sizeof(_bitsPerSample));
                if (audioFormat != 1) {
                    std::cerr << "Error: Unsupported format (not PCM)" << std::endl;
                    return false;
                }
                if (chunkSize > 16)
                    file.ignore(chunkSize - 16);
                fmtFound = true;
            }
            else if (chunkId == "data") {
                dataSize = chunkSize;
                _samples.resize(dataSize / sizeof(int16_t));
                file.read(reinterpret_cast<char*>(_samples.data()), dataSize);
                dataFound = true;
                break;
            }
            else {
                file.seekg(chunkSize, std::ios::cur);
            }
        }

        if (!fmtFound) {
            std::cerr << "Error: Missing 'fmt ' chunk" << std::endl;
            return false;
        }
        if (!dataFound) {
            std::cerr << "Error: Missing 'data' chunk" << std::endl;
            return false;
        }
        if (_numChannels != 1 || _sampleRate != 48000 || _bitsPerSample != 16) {
            std::cerr << "Error: Unsupported WAV format (expected 16bit, mono, 48kHz)" << std::endl;
            return false;
        }
        return true;
    }
}

