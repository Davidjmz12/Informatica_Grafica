/**
 * @file constants.hpp
 * @brief Defines multiple constants that will be used in the code.
 *
*/

#pragma once

#include <cmath>
#include <string>
#include <random>

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
 * is less than a predefined threshold value (THRESHOLD_double). It is useful for 
 * comparing doubleing-point numbers where precision errors might occur.
 * 
 * @param a The first doubleing-point number to compare.
 * @param b The second doubleing-point number to compare.
 * @return true if the absolute difference between a and b is less than THRESHOLD_double, false otherwise.
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

inline bool leD(double a, double b)
{
    return a - b < EPSILON;
}

inline bool geD(double a, double b)
{
    return b - a < EPSILON;
}

inline double randomD(double a, double b)
{
    double r2 = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX));
    return a + r2*(b-a);
}