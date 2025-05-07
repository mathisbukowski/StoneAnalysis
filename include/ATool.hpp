/*
** EPITECH PROJECT, 2025
** StoneAnalysis
** File description:
** ATool
*/

#ifndef ATOOL_HPP_
#define ATOOL_HPP_

#include <string>
#include <vector>

#include "ITool.hpp"

namespace stone {
    class ATool : public ITool {
        public:
            explicit ATool(const std::string &inputFilename): _inputFilename(inputFilename) {};
            ~ATool() = default;

            virtual int execute() const override = 0;
            
        protected:
            std::string _inputFilename;
    };
}

#endif /* !ATOOL_HPP_ */
