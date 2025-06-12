#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <stdexcept>
#include "differential_equations.h"

namespace {
    void assertDoubleEqual(double a, double b, double tolerance = 1e-5) {
        assert(std::abs(a - b) < tolerance);
    }
    auto f_ode_exp = [](double x, double y){ return y; }; // dy/dx=y -> y=e^x, y(0)=1
    auto f_ode_linear = [](double x, double y){ return 2.0; }; // dy/dx=2 -> y=2x+c, y(0)=1 -> y=2x+1
}

void TestEulerMethodCorrectness() {
    std::cout << "Test: eulerMethod - poprawnosc wyniku... ";
    auto solution = numeric::ode::eulerMethod(f_ode_linear, 0.0, 1.0, 0.01, 2.0);
    assertDoubleEqual(solution.back().y, 5.0, 1e-1); // y(2) = 2*2+1=5
    std::cout << "OK" << std::endl;
}

void TestEulerMethodThrowsOnInvalidInput() {
    std::cout << "Test: eulerMethod - niepoprawny krok h... ";
    try {
        numeric::ode::eulerMethod(f_ode_linear, 0, 1, 0, 1);
        assert(false);
    } catch (const std::invalid_argument&) {
        std::cout << "OK" << std::endl;
    }
}

void TestHeunMethodCorrectness() {
    std::cout << "Test: heunMethod - poprawnosc wyniku... ";
    auto solution = numeric::ode::heunMethod(f_ode_exp, 0.0, 1.0, 0.1, 1.0);
    assertDoubleEqual(solution.back().y, std::exp(1.0), 1e-2);
    std::cout << "OK" << std::endl;
}

void TestHeunMethodThrowsOnInvalidInput() {
    std::cout << "Test: heunMethod - pusty wskaznik na funkcje... ";
    try {
        numeric::ode::heunMethod(nullptr, 0, 1, 0.1, 1);
        assert(false);
    } catch (const std::invalid_argument&) {
        std::cout << "OK" << std::endl;
    }
}

void TestMidpointMethodCorrectness() {
    std::cout << "Test: midpointMethod - poprawnosc wyniku... ";
    auto solution = numeric::ode::midpointMethod(f_ode_exp, 0.0, 1.0, 0.1, 1.0);
    assertDoubleEqual(solution.back().y, std::exp(1.0), 1e-2);
    std::cout << "OK" << std::endl;
}

void TestMidpointMethodThrowsOnInvalidInput() {
    std::cout << "Test: midpointMethod - niepoprawne granice... ";
    try {
        numeric::ode::midpointMethod(f_ode_exp, 1.0, 1.0, 0.1, 0.0);
        assert(false);
    } catch (const std::invalid_argument&) {
        std::cout << "OK" << std::endl;
    }
}

void TestRungeKutta4Correctness() {
    std::cout << "Test: rungeKutta4 - poprawnosc wyniku... ";
    auto solution = numeric::ode::rungeKutta4(f_ode_exp, 0.0, 1.0, 0.1, 1.0);
    assertDoubleEqual(solution.back().y, std::exp(1.0), 1e-2);
    std::cout << "OK" << std::endl;
}

void TestRungeKutta4ThrowsOnInvalidInput() {
    std::cout << "Test: rungeKutta4 - niepoprawne dane... ";
    try {
        numeric::ode::rungeKutta4(f_ode_exp, 0, 1, -0.1, 1);
        assert(false);
    } catch (const std::invalid_argument&) {
        std::cout << "OK" << std::endl;
    }
}