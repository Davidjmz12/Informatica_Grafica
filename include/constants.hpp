/**
 * @file constants.hpp
 * @brief Defines multiple constants that will be used in the code.
 *
*/

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

const float THRESHOLD_FLOAT = 1e-6; // Threshold for comparing float values
const float THRESHOLD_COLOR = 1e-3; // Threshold for comparing color values
const float RANGE_RGB = 1.0F; // Range of RGB system
const float RANGE_H = 6.0F; // Range of Hue system
const float RANGE_SV = 1.0F; // Range of Saturation and Value system


// Color constants
const std::string RESET = "\033[0m";
const std::string BLUE = "\033[34m";
const std::string GREEN = "\033[32m";
const std::string RED = "\033[31m";

#endif