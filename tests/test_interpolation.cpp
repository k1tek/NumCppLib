#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <stdexcept>
#include "interpolation.h"

namespace {
    void assertDoubleEqual(double a, double b, double tolerance = 1e-9) {
        assert(std::abs(a - b) < tolerance);
    }
}

void TestLagrangeInterpolationCorrectness() {
    std::cout << "Test: lagrangeInterpolation - poprawnosc wyniku... ";
    std::vector<double> x = {0, 1, 2}, y = {1, 2, 5};
    double val = numeric::interpolation::lagrangeInterpolation(x, y, 1.5);
    assertDoubleEqual(val, 3.25);
    std::cout << "OK" << std::endl;
}

void TestLagrangeInterpolationThrowsOnInvalidInput() {
    std::cout << "Test: lagrangeInterpolation - niepoprawne dane... ";
    std::vector<double> x = {0, 1}, y = {1};
    try {
        numeric::interpolation::lagrangeInterpolation(x, y, 1.5);
        assert(false);
    } catch (const std::invalid_argument&) { // Usunieto nazwe zmiennej 'e'
        std::cout << "OK" << std::endl;
    }
}

void TestNewtonInterpolationCorrectness() {
    std::cout << "Test: newtonInterpolation - poprawnosc wyniku... ";
    std::vector<double> x = {0, 1, 2}, y = {1, 2, 5};
    double val = numeric::interpolation::newtonInterpolation(x, y, 1.5);
    assertDoubleEqual(val, 3.25);
    std::cout << "OK" << std::endl;
}

void TestNewtonInterpolationThrowsOnInvalidInput() {
    std::cout << "Test: newtonInterpolation - puste wektory... ";
    std::vector<double> x, y;
    try {
        numeric::interpolation::newtonInterpolation(x, y, 1.5);
        assert(false);
    } catch (const std::invalid_argument&) { // Usunieto nazwe zmiennej 'e'
        std::cout << "OK" << std::endl;
    }
}