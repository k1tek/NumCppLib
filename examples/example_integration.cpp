// examples/main_integration.cpp

#include <iostream>
#include <vector>
#include <iomanip>
#include "integration.h" // Nasza nowa biblioteka

// Definicja funkcji wielomianowej za pomocą lambdy i przechwycenia współczynników
auto makePolynomial(const std::vector<double>& coeffs) {
    return [coeffs](double x) {
        double result = coeffs[0];
        for (size_t i = 1; i < coeffs.size(); ++i) {
            result = result * x + coeffs[i];
        }
        return result;
    };
}

// Definicja funkcji trygonometrycznej
double trigonometricFunction(double x) {
    return x * std::pow(std::cos(x), 3);
}

int main() {
    std::cout << std::fixed << std::setprecision(10);

    // === Testowanie dla funkcji wielomianowej ===
    std::vector<double> poly_coeffs = { /* Twoje współczynniki ai */ -5.0, 2.0, 3.0, -1.0, 7.0};
    auto polynomial = makePolynomial(poly_coeffs);
    double a_poly = -2.0, b_poly = 5.0; // Twoje granice [a,b]
    int n = 100;

    std::cout << "=== CALKOWANIE FUNKCJI WIELOMIANOWEJ ===" << std::endl;
    std::cout << "Przedzial: [" << a_poly << ", " << b_poly << "], N = " << n << std::endl;
    
    double rect_poly = numeric::integration::rectangleRule(polynomial, a_poly, b_poly, n);
    std::cout << "Metoda prostokatow: " << rect_poly << std::endl;
    
    double trap_poly = numeric::integration::trapezoidalRule(polynomial, a_poly, b_poly, n);
    std::cout << "Metoda trapezow:    " << trap_poly << std::endl;

    double simp_poly = numeric::integration::simpsonRule(polynomial, a_poly, b_poly, n);
    std::cout << "Metoda Simpsona:    " << simp_poly << std::endl;
    
    std::cout << "\n----------------------------------------\n" << std::endl;

    // === Testowanie dla funkcji trygonometrycznej ===
    double a_trig = 3.5, b_trig = 6.52968912629344;
    double exact_value_trig = 4.2025;

    std::cout << "=== CALKOWANIE FUNKCJI x*cos^3(x) ===" << std::endl;
    std::cout << "Przedzial: [" << a_trig << ", " << b_trig << "], Dokladna wartosc: " << exact_value_trig << std::endl;

    // Porównanie Simpsona i Gaussa-Legendre'a
    int segments = 10;
    int nodes = 4;
    double simp_trig = numeric::integration::simpsonRule(trigonometricFunction, a_trig, b_trig, segments);
    double gauss_trig = numeric::integration::segmentedGaussLegendre(trigonometricFunction, a_trig, b_trig, nodes, segments);
    
    std::cout << "Simpson (N=" << segments << "):        " << simp_trig << ", Blad: " << std::abs(simp_trig - exact_value_trig) << std::endl;
    std::cout << "Gauss-Legendre (N=" << segments << ", wezly=" << nodes << "): " << gauss_trig << ", Blad: " << std::abs(gauss_trig - exact_value_trig) << std::endl;

    return 0;
}