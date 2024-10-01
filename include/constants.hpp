/**
 * @file constants.hpp
 * @brief Defines multiple constants that will be used in the code.
 *
*/

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <cmath>

const float THRESHOLD_FLOAT = 1e-6; // Threshold for comparing float values


// Color constants
const std::string RESET = "\033[0m"; // Reset color
const std::string BLUE = "\033[34m"; // Blue color
const std::string GREEN = "\033[32m"; // Green color
const std::string RED = "\033[31m"; // Red color


/**
 * @brief Compares two floating-point numbers for equality within a specified threshold.
 * 
 * This function checks if the absolute difference between two floating-point numbers
 * is less than a predefined threshold value (THRESHOLD_FLOAT). It is useful for 
 * comparing floating-point numbers where precision errors might occur.
 * 
 * @param a The first floating-point number to compare.
 * @param b The second floating-point number to compare.
 * @return true if the absolute difference between a and b is less than THRESHOLD_FLOAT, false otherwise.
 */
inline bool eqFloat(float a, float b)
{
    return fabs(a - b) < THRESHOLD_FLOAT;
}


#endif