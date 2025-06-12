#include "approximation.h"
#include <stdexcept>
#include <numeric> // Dla std::inner_product
#include <cmath>
#include <iostream>
#include "linear_algebra.h" // Dla solve_gauss

namespace numeric {
namespace approximation {

   double approximateValueAtPoint(const std::function<double(double)>& f, double a, double b, int N, double eval_point) {
    
    // ========================================================================
    // KROK 1: WEWNĘTRZNA LOGIKA CAŁKOWANIA (GAUSS-LEGENDRE)
    // Ta część jest całkowicie ukryta przed użytkownikiem.
    // ========================================================================
    auto internal_gauss_legendre = [](const std::function<double(double)>& func_to_integrate, double lower, double upper, int nodes) -> double {
        static const double x2[] = { -1.0 / sqrt(3.0), 1.0 / sqrt(3.0) };
        static const double w2[] = { 1.0, 1.0 };
        static const double x3[] = { -sqrt(3.0 / 5.0), 0.0, sqrt(3.0 / 5.0) };
        static const double w3[] = { 5.0 / 9.0, 8.0 / 9.0, 5.0 / 9.0 };
        static const double x4[] = { -sqrt((3.0 + 2.0 * sqrt(6.0 / 5.0)) / 7.0), -sqrt((3.0 - 2.0 * sqrt(6.0 / 5.0)) / 7.0), sqrt((3.0 - 2.0 * sqrt(6.0 / 5.0)) / 7.0), sqrt((3.0 + 2.0 * sqrt(6.0 / 5.0)) / 7.0) };
        static const double w4[] = { (18.0 - sqrt(30.0)) / 36.0, (18.0 + sqrt(30.0)) / 36.0, (18.0 + sqrt(30.0)) / 36.0, (18.0 - sqrt(30.0)) / 36.0 };

        const double* x_ptr;
        const double* w_ptr;
        switch (nodes) {
            case 2: x_ptr = x2; w_ptr = w2; break;
            case 3: x_ptr = x3; w_ptr = w3; break;
            case 4: x_ptr = x4; w_ptr = w4; break;
            default: throw std::invalid_argument("Nieobslugiwana liczba wezlow.");
        }
        double sum = 0.0;
        for (int i = 0; i < nodes; ++i) {
            double transformed_x = ((upper - lower) / 2.0) * x_ptr[i] + ((upper + lower) / 2.0);
            sum += w_ptr[i] * func_to_integrate(transformed_x);
        }
        return (upper - lower) / 2.0 * sum;
    };

    // ========================================================================
    // KROK 2: BUDOWANIE MACIERZY A I WEKTORA B
    // ========================================================================
    std::vector<std::vector<double>> A(N, std::vector<double>(N));
    std::vector<double> B(N);
    const int integration_nodes = 4; // Ustawione na sztywno dla uproszczenia

    for (int j = 0; j < N; ++j) {
        auto f_times_xj = [&](double x) { return f(x) * pow(x, j); };
        B[j] = internal_gauss_legendre(f_times_xj, a, b, integration_nodes);

        for (int k = 0; k < N; ++k) {
            auto x_pow_jk = [&](double x) { return pow(x, j + k); };
            A[j][k] = internal_gauss_legendre(x_pow_jk, a, b, integration_nodes);
        }
    }

    // ========================================================================
    // KROK 3: ROZWIĄZANIE UKŁADU RÓWNAŃ
    // Tutaj wywołujemy funkcję z innego modułu
    // ========================================================================
    std::vector<double> coeffs = numeric::linear_algebra::gaussElimination(A, B);

    // ========================================================================
    // KROK 4: OBLICZENIE WARTOŚCI WIELOMIANU W PUNKCIE
    // ========================================================================
    double result = 0.0;
    for (size_t i = 0; i < coeffs.size(); ++i) {
        result += coeffs[i] * pow(eval_point, i);
    }

    return result;
}



}
}