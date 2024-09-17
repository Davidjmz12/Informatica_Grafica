/**
 * @file test.hpp
 * @brief Defines a test class to define tests.
 *
 * This file contains the definition of the Test and Tests class, which represents
 * individual and a set of tests.
*/

#ifndef TEST_HPP
#define TEST_HPP

#include <iostream>
#include <exception>
#include <string>
#include <functional>
#include <sstream>
#include <vector>

/*
const std::string RESET = "\033[0m";
const std::string BLUE = "\033[34m";
const std::string GREEN = "\033[32m";
const std::string RED = "\033[31m";
*/
const std::string RESET = "";
const std::string BLUE = "";
const std::string GREEN = "";
const std::string RED = "";


/**
 * @brief A class for representing an individual test
 */
class Test {
private:

    /**
    * @brief Private constructor for Test class
    */
    Test(std::function<void()> func): testCase(func) {} 
    
    std::function<void()> testCase; // Stores the test case to be executed
public:

    /**
    * @brief Method that evaluates the test.
    */
    void eval() const{
        testCase();
    }

    /**
    * @brief Test that is true if both values are equal.
    * @param a one value.
    * @param b other value.
    * @tparam T must have == operator.
    * @return the resultant test.
    */
    template <typename T>
    static Test EXPECT_EQ(const T& a, const T& b)
    {
        return Test([a, b]() {
            if (!(a == b)) {
                std::ostringstream ss;
                ss << "EXPECT_EQ failed:\n\n\t{EXPECTED}:\n\n" << b << "\n\n\t{GOT}:\n\n" << a << "\n";
                throw std::logic_error(ss.str());
            }
        });
    }

    /**
    * @brief Test that is true if both values are not equal.
    * @param a one value.
    * @param b other value.
    * @tparam T must have == operator.
    * @return the resultant test.
    */
    template <typename T>
    static Test EXPECT_NEQ(const T& a, const T& b)
    {
        return Test([a, b]() {
            if (!(a != b)) {
                std::ostringstream ss;
                ss << "EXPECT_EQ failed:\n\n\t{EXPECTED}:\n\n" << b << "\n\n\t{GOT}:\n\n" << a << "\n";
                throw std::logic_error(ss.str());
            }
        });
    }

    /**
    * @brief Test that is true if the function given throws an exception
    * @param func function to be tested.
    * @return the resultant test.
    */
    static Test EXPECT_EXC(std::function<void()> func)
    {
        return Test([func]() {
            try {
                func();
            } catch (...) {
                return;  // Test passes if an exception is thrown
            }
            throw std::logic_error("EXPECT_EXC failed: Expected an exception but none was thrown.");
        });
    }
};

/**
 * @brief A class for representing a set of tests.
 */
class Tests {
private:
    std::string test_name; // Name of the test
    std::vector<Test> test_set; // Set of all tests.
public:

    /**
    * @brief Method that construct a tests set.
    * @param test the tests to be added.
    */   
    Tests(const std::string& name): test_name(name) {}

    /**
    * @brief Method that adds a test to the test set.
    * @param test the tests to be added.
    */
    void addTest(const Test& test)
    {
        test_set.push_back(test);
    }

    /**
    * @brief Method that runs all the tests.
    * @return 0 if everything is okey, !=0 otherwise.
    */
    int runAll()
    {
        std::cout << "-----------------------------------------------------\n";
        std::cout << BLUE << "TEST NAME: " << test_name << RESET << std::endl;
        std::cout << "-----------------------------------------------------\n";

        int passed = 0;
        std::string results;

        for (size_t i = 0; i < test_set.size(); ++i) {
            try {
                test_set[i].eval();  // Run test
                passed++;
                results += (GREEN + "\tTest " + std::to_string(i + 1) + ": correct." + RESET + "\n");
            } catch (const std::exception& e) {
                results += RED + "\tTest " + std::to_string(i + 1) + ": not correct. " + e.what() + RESET + "\n";
            }
        }

        // Summary
        std::string color = int(test_set.size())==passed?GREEN:RED;
        std::cout << results <<
                    "-----------------------------------------------------\n" <<   
                    BLUE << "SUMMARY: " << color << passed << "/" << test_set.size() << " passed"
                    << RESET << "\n" << 
                    "-----------------------------------------------------\n";
        return int(test_set.size())==passed?0:1;
    }

};

#endif