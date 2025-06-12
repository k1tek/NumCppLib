#include <iostream>
#include <cassert>
#include <cmath>
#include <stdexcept>
#include "integration.h"

namespace {
    void assertDoubleEqual(double a, double b, double tolerance = 1e-7) {
        assert(std::abs(a - b) < tolerance);
    }
    auto f_const = [](double x){ return 2.0; }; // Calka od 1 do 3 to 4
    auto f_linear = [](double x){ return x; };   // Calka od 0 do 2 to 2
}

void TestRectangleRuleCorrectness() {
    std::cout << "Test: rectangleRule - poprawnosc wyniku... ";
    double result = numeric::integration::rectangleRule(f_const, 1.0, 3.0, 100);
    assertDoubleEqual(result, 4.0);
    std::cout << "OK" << std::endl;
}

void TestRectangleRuleThrowsOnInvalidInput() {
    std::cout << "Test: rectangleRule - niepoprawne N... ";
    try {
        numeric::integration::rectangleRule(f_const, 0.0, 1.0, 0);
        assert(false);
    } catch (const std::invalid_argument&) {
        std::cout << "OK" << std::endl;
    }
}

void TestTrapezoidalRuleCorrectness() {
    std::cout << "Test: trapezoidalRule - poprawnosc wyniku... ";
    double result = numeric::integration::trapezoidalRule(f_linear, 0.0, 2.0, 100);
    assertDoubleEqual(result, 2.0);
    std::cout << "OK" << std::endl;
}

void TestTrapezoidalRuleThrowsOnInvalidInput() {
    std::cout << "Test: trapezoidalRule - niepoprawna funkcja... ";
    try {
        numeric::integration::trapezoidalRule(nullptr, 0.0, 1.0, 10);
        assert(false);
    } catch (const std::invalid_argument&) {
        std::cout << "OK" << std::endl;
    }
}

void TestSimpsonRuleCorrectness() {
    std::cout << "Test: simpsonRule - poprawnosc wyniku... ";
    auto f_cubic = [](double x){ return x*x*x; }; // Calka od -1 do 1 to 0
    double result = numeric::integration::simpsonRule(f_cubic, -1.0, 1.0, 100);
    assertDoubleEqual(result, 0.0);
    std::cout << "OK" << std::endl;
}

void TestSimpsonRuleThrowsOnInvalidInput() {
    std::cout << "Test: simpsonRule - niepoprawne N... ";
    try {
        numeric::integration::simpsonRule(f_linear, 0.0, 1.0, -10);
        assert(false);
    } catch (const std::invalid_argument&) {
        std::cout << "OK" << std::endl;
    }
}

void TestGaussLegendreCorrectness() {
    std::cout << "Test: gaussLegendre - poprawnosc wyniku... ";
    auto f_fifth = [](double x){ return x*x*x*x*x; }; // Calka od -1 do 1 to 0
    double result = numeric::integration::gaussLegendre(f_fifth, -1.0, 1.0, 3);
    assertDoubleEqual(result, 0.0);
    std::cout << "OK" << std::endl;
}

void TestGaussLegendreThrowsOnUnsupportedNodes() {
    std::cout << "Test: gaussLegendre - zla liczba wezlow... ";
    try {
        numeric::integration::gaussLegendre(f_linear, 0, 1, 1);
        assert(false);
    } catch(const std::invalid_argument&) {
        std::cout << "OK" << std::endl;
    }
}

void TestSegmentedGaussLegendreCorrectness() {
    std::cout << "Test: segmentedGaussLegendre - poprawnosc wyniku... ";
    double result = numeric::integration::segmentedGaussLegendre(f_linear, 0.0, 4.0, 2, 2);
    // Calka od 0 do 4 to 8
    assertDoubleEqual(result, 8.0);
    std::cout << "OK" << std::endl;
}

void TestSegmentedGaussLegendreThrowsOnInvalidInput() {
    std::cout << "Test: segmentedGaussLegendre - zle segmenty... ";
    try {
        numeric::integration::segmentedGaussLegendre(f_linear, 0.0, 1.0, 2, 0);
        assert(false);
    } catch (const std::invalid_argument&) {
        std::cout << "OK" << std::endl;
    }
}