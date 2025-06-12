// tests/test_linear_algebra.cpp

#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <stdexcept>
#include "linear_algebra.h"

namespace {
    void assertVectorsEqual(const std::vector<double>& a, const std::vector<double>& b, double tolerance = 1e-9) {
        assert(a.size() == b.size());
        for (size_t i = 0; i < a.size(); ++i) {
            assert(std::abs(a[i] - b[i]) < tolerance);
        }
    }
}

void TestGaussEliminationSolvable() {
    std::cout << "Test: gaussElimination - uklad rozwiazywalny... ";
    std::vector<std::vector<double>> A = {{2, 1, -1}, {-3, -1, 2}, {-2, 1, 2}};
    std::vector<double> b = {8, -11, -3};
    std::vector<double> expected = {2, 3, -1};
    assertVectorsEqual(numeric::linear_algebra::gaussElimination(A, b), expected);
    std::cout << "OK" << std::endl;
}

// POPRAWIONA NAZWA FUNKCJI
void TestGaussEliminationThrowsOnInvalidInput() {
    std::cout << "Test: gaussElimination - macierz osobliwa... ";
    std::vector<std::vector<double>> A = {{1, 1}, {1, 1}};
    std::vector<double> b = {1, 2};
    try {
        numeric::linear_algebra::gaussElimination(A, b);
        assert(false); // Powinien rzucic wyjatek
    } catch (const std::runtime_error&) {
        // Zlapano oczekiwany wyjatek
        std::cout << "OK" << std::endl;
    }
}

void TestLuDecompositionSolvable() {
    std::cout << "Test: luDecomposition - uklad rozwiazywalny... ";
    std::vector<std::vector<double>> A = {{1, 4, 1}, {1, 6, -1}, {2, -1, 2}};
    std::vector<double> b = {7, 13, 5};
    std::vector<double> expected = {5, 1, -2};
    assertVectorsEqual(numeric::linear_algebra::luDecomposition(A, b), expected);
    std::cout << "OK" << std::endl;
}

// POPRAWIONA NAZWA FUNKCJI
void TestLuDecompositionThrowsOnInvalidInput() {
    std::cout << "Test: luDecomposition - macierz osobliwa... ";
    std::vector<std::vector<double>> A = {{1, 2}, {2, 4}};
    std::vector<double> b = {1, 2};
    try {
        numeric::linear_algebra::luDecomposition(A, b);
        assert(false);
    } catch (const std::runtime_error&) {
        std::cout << "OK" << std::endl;
    }
}