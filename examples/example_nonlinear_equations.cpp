// examples/example_nonlinear_equations.cpp

#include <iostream>
#include <iomanip>
#include <cmath>
#include "nonlinear_equations.h"

// Funkcja: f(x) = x^3 - x - 2
double myFunction(double x) {
    return x * x * x - x - 2;
}

// Pochodna: f'(x) = 3x^2 - 1
double myDerivative(double x) {
    return 3 * x * x - 1;
}

void printResult(const std::string& methodName, std::optional<double> result) {
    std::cout << std::setw(25) << std::left << methodName << ": ";
    if (result) {
        std::cout << "Znaleziono pierwiastek: " << std::fixed << std::setprecision(8) << *result << std::endl;
    } else {
        std::cout << "Nie znaleziono pierwiastka." << std::endl;
    }
}

int main() {
    std::cout << "=== Testowanie biblioteki rownan nieliniowych ===\n";
    std::cout << "Funkcja: f(x) = x^3 - x - 2\n\n";

    double start_point = 1.5;

    // --- Metoda Newtona z pochodna analityczna ---
    // Kompilator wybierze wersje z 3 argumentami (f, df, x0)
    auto resultNewtonAnalytical = numeric::nonlinear::newtonMethod(myFunction, myDerivative, start_point);
    printResult("Metoda Newtona (analityczna)", resultNewtonAnalytical);

    // --- Metoda Newtona z pochodna numeryczna ---
    // Kompilator wybierze wersje z 2 argumentami (f, x0)
    auto resultNewtonNumerical = numeric::nonlinear::newtonMethod(myFunction, start_point);
    printResult("Metoda Newtona (numeryczna)", resultNewtonNumerical);

    // --- Inne metody dla porownania ---
    auto resultBisection = numeric::nonlinear::bisectionMethod(myFunction, 1.0, 2.0);
    printResult("Metoda bisekcji", resultBisection);

    auto resultSecant = numeric::nonlinear::secantMethod(myFunction, 1.0, 2.0);
    printResult("Metoda siecznych", resultSecant);

    return 0;
}