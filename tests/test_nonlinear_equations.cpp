#include <iostream>
#include <optional>
#include <cassert>
#include <cmath>
#include "nonlinear_equations.h"

namespace {
    void assertOptionalDoubleEqual(std::optional<double> res, double exp, double tol = 1e-7) {
        assert(res.has_value());
        assert(std::abs(res.value() - exp) < tol);
    }
    auto f_parabola = [](double x){ return x*x - 9; }; // Pierwiastki: -3, 3
    auto df_parabola = [](double x){ return 2*x; };
}

void TestBisectionMethodFindsRoot() {
    std::cout << "Test: bisectionMethod - znajduje pierwiastek... ";
    auto result = numeric::nonlinear::bisectionMethod(f_parabola, 0, 5);
    assertOptionalDoubleEqual(result, 3.0);
    std::cout << "OK" << std::endl;
}

void TestBisectionMethodReturnsNullopt() {
    std::cout << "Test: bisectionMethod - nie znajduje pierwiastka... ";
    auto result = numeric::nonlinear::bisectionMethod(f_parabola, 4, 10);
    assert(!result.has_value());
    std::cout << "OK" << std::endl;
}

void TestSecantMethodFindsRoot() {
    std::cout << "Test: secantMethod - znajduje pierwiastek... ";
    auto result = numeric::nonlinear::secantMethod(f_parabola, 1, 5);
    assertOptionalDoubleEqual(result, 3.0);
    std::cout << "OK" << std::endl;
}

void TestSecantMethodThrowsOnInvalidInput() {
    std::cout << "Test: secantMethod - niepoprawne dane... ";
    try {
        numeric::nonlinear::secantMethod(nullptr, 1, 5);
        assert(false);
    } catch (const std::invalid_argument&) {
        std::cout << "OK" << std::endl;
    }
}

void TestNewtonMethodAnalyticalFindsRoot() {
    std::cout << "Test: newtonMethod (analityczny)... ";
    auto result = numeric::nonlinear::newtonMethod(f_parabola, df_parabola, 5.0);
    assertOptionalDoubleEqual(result, 3.0);
    std::cout << "OK" << std::endl;
}

void TestNewtonMethodNumericalFindsRoot() {
    std::cout << "Test: newtonMethod (numeryczny)... ";
    auto result = numeric::nonlinear::newtonMethod(f_parabola, 5.0);
    assertOptionalDoubleEqual(result, 3.0);
    std::cout << "OK" << std::endl;
}

void TestRegulaFalsiMethodFindsRoot() {
    std::cout << "Test: regulaFalsiMethod - znajduje pierwiastek... ";
    auto result = numeric::nonlinear::regulaFalsiMethod(f_parabola, 1, 5);
    assertOptionalDoubleEqual(result, 3.0);
    std::cout << "OK" << std::endl;
}

void TestRegulaFalsiMethodReturnsNullopt() {
    std::cout << "Test: regulaFalsiMethod - nie znajduje pierwiastka... ";
    auto f_always_pos = [](double x){ return x*x + 1; };
    auto result = numeric::nonlinear::regulaFalsiMethod(f_always_pos, -5, 5);
    assert(!result.has_value());
    std::cout << "OK" << std::endl;
}