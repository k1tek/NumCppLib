// examples/example_differential_equations.cpp

#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath> // Dla std::exp i std::abs

// Dołączamy naszą bibliotekę
#include "differential_equations.h"

// Definiujemy proste rownanie rozniczkowe: dy/dx = y
// Argument 'x' jest ignorowany, poniewaz pochodna zalezy tylko od 'y'.
double simple_ode_function(double x, double y) {
    return y;
}

int main() {
    std::cout << "=== Prosty test biblioteki rownan rozniczkowych ===" << std::endl;
    std::cout << "Rozwiazywane rownanie: dy/dx = y, z warunkiem y(0) = 1" << std::endl;
    std::cout << "Dokladne rozwiazanie: y(x) = e^x\n" << std::endl;

    // Parametry symulacji
    double x0 = 0.0;
    double y0 = 1.0;
    double h = 0.1;      // Dlugosc kroku
    double x_end = 1.0;  // Punkt koncowy

    // Wywolujemy jedna z metod z biblioteki, np. Rungego-Kutty 4. rzedu
    // jako ze jest najdokladniejsza
    std::vector<numeric::ode::SolutionPoint> solution = 
        numeric::ode::rungeKutta4(simple_ode_function, x0, y0, h, x_end);

    // Wyswietlamy wyniki
    std::cout << std::fixed << std::setprecision(8);
    std::cout << "x_val         y_approx      y_exact       error\n";
    std::cout << "-----------------------------------------------------\n";

    for (const auto& point : solution) {
        double exact_y = std::exp(point.x);
        double error = std::abs(point.y - exact_y);
        
        std::cout << std::setw(12) << point.x
                  << std::setw(14) << point.y
                  << std::setw(14) << exact_y
                  << std::setw(14) << error
                  << std::endl;
    }

    return 0;
}