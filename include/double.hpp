#include <iostream>
#include <cmath>
#include <stdexcept>
#include "constants.hpp"

const Double EPSILON = 1e-8; // Threshold for comparing Double values

class Double {
private:
    double value;

public:
    // Constructors
    Double() : value(0.0) {}
    Double(double val) : value(val) {}
    Double(int val) : value(static_cast<double>(val)) {}

    // Getter and Setter
    double getValue() const {
        return value;
    }

    void setValue(double val) {
        value = val;
    }

    // Operator overloading for basic arithmetic operations
    Double operator+(const double& other) const {
        return Double(value + other);
    }

    Double operator-(const double& other) const {
        return Double(value - other);
    }

    Double operator*(const double& other) const {
        return Double(value * other);
    }

    Double operator/(const double& other) const {
        if (std::fabs(other) < EPSILON) {
            throw std::runtime_error("Division by zero error");
        }
        return Double(value / other);
    }

    // Comparison operators
    bool operator==(const double& other) const {
        return std::fabs(value - other) < EPSILON;
    }

    bool operator!=(const double& other) const {
        return !(*this == other);
    }

    bool operator<(const double& other) const {
        return value-other < -EPSILON;
    }

    bool operator<=(const double& other) const {
        return value-other < EPSILON;
    }

    bool operator>(const double& other) const {
        return other-value < -EPSILON ;
    }

    bool operator>=(const double& other) const {
        return other-value < EPSILON ;
    }


    // Conversion operators
    operator double() const {
        return value;
    }

    operator int() const {
        return static_cast<int>(value);
    }

    operator std::string() const {
        return std::to_string(value);
    }   


    // Friend function to overload stream output
    friend std::ostream& operator<<(std::ostream& os, const Double& obj) {
        os << obj.value;
        return os;
    }
};

// Additional utility functions
Double abs(Double a){
    return Double(std::fabs(a.getValue()));
}

Double sqrt(Double a){
    if (a.getValue() < 0) {
        throw std::runtime_error("Cannot take square root of a negative number");
    }
    return Double(std::sqrt(a.getValue()));
}

Double pow(Double base, double exponent){
    return Double(std::pow(base.getValue(), exponent));
}