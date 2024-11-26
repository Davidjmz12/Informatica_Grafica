#pragma once

#include <cmath>
#include <array>

/**
 * @brief Computes the x component of the CIE 1931 color matching function for a given wavelength.
 * 
 * @param wave The wavelength of light in nanometers.
 * @return The x component of the CIE 1931 color matching function.
 */
inline float xFit_1931(float wave)
{
    return 0.398*exp(-1250*pow(log((wave+570.1)/1014),2)) + 1.132*exp(-234*pow(log((1338-wave)/743.5),2));
}

/**
 * @brief Computes the y component of the CIE 1931 color matching function for a given wavelength.
 * 
 * @param wave The wavelength of light in nanometers.
 * @return The y component of the CIE 1931 color matching function.
 */
inline float yFit_1931(float wave)
{
    return 1.011*exp(-0.5*pow((wave-556.1)/46.14,2));
}

/**
 * @brief Computes the z component of the CIE 1931 color matching function for a given wavelength.
 * 
 * @param wave The wavelength of light in nanometers.
 * @return The z component of the CIE 1931 color matching function.
 */
inline float zFit_1931(float wave)
{
    return 2.060*exp(-32*pow(log((wave-265.8)/180.4),2));
}

/**
 * @brief Computes the CIE 1931 color matching functions (x, y, z) for a given wavelength.
 * 
 * @param lambda The wavelength of light in nanometers.
 * @return An array containing the x, y, and z components of the CIE 1931 color matching functions.
 */
inline std::array<double,3> CIE_1931_curves(double lambda)
{
    return {xFit_1931(lambda),yFit_1931(lambda),zFit_1931(lambda)};
}

/**
 * @brief Applies gamma correction to a given value.
 * 
 * @param value The value to be gamma corrected.
 * @return The gamma-corrected value.
 */
inline double gamma_correction(double value)
{
    if(value <= 0.0031308)
        return 12.92*value;
    return 1.055*pow(value,1/2.4)-0.055;
}