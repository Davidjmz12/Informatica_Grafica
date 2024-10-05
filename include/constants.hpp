/**
 * @file constants.hpp
 * @brief Defines multiple constants that will be used in the code.
 *
*/

#pragma once

#include <cmath>
#include <string>

const double EPSILON = 1e-6; // Threshold for comparing double values


// Color constants
const std::string RESET = "\033[0m"; // Reset color
const std::string BLUE = "\033[34m"; // Blue color
const std::string GREEN = "\033[32m"; // Green color
const std::string RED = "\033[31m"; // Red color


/**
 * @brief Compares two doubleing-point numbers for equality within a specified threshold.
 * 
 * This function checks if the absolute difference between two doubleing-point numbers
 * is less than a predefined threshold value (THRESHOLD_FLOAT). It is useful for 
 * comparing doubleing-point numbers where precision errors might occur.
 * 
 * @param a The first doubleing-point number to compare.
 * @param b The second doubleing-point number to compare.
 * @return true if the absolute difference between a and b is less than THRESHOLD_FLOAT, false otherwise.
 */
inline bool eqD(double a, double b)
{
    return (fabs(a - b) < EPSILON);
}

inline bool neqD(double a, double b)
{
    return !eqD(a, b);
}

inline bool ltD(double a, double b)
{
    return a - b < -EPSILON;
}

inline bool gtD(double a, double b)
{
    return b - a < -EPSILON;
}

inline bool leF(double a, double b)
{
    return a - b < EPSILON;
}

inline bool geF(double a, double b)
{
    return b - a < EPSILON;
}