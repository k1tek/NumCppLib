// src/differential_equations.cpp

#include "differential_equations.h"
#include <cmath>
#include <stdexcept>

namespace numeric {
namespace ode {

namespace { // Anonimowa przestrzen nazw dla funkcji pomocniczych
    // Prywatna funkcja do walidacji danych wejsciowych
    void validateInputs(const OdeFunction& f, double h, double x0, double x_end) {
        if (!f) {
            throw std::invalid_argument("Funkcja f nie jest zdefiniowana (jest pusta).");
        }
        if (h <= 0) {
            throw std::invalid_argument("Krok calkowania (h) musi byc dodatni.");
        }
        if (x_end < x0) {
            throw std::invalid_argument("Punkt koncowy (x_end) nie moze byc mniejszy od punktu poczatkowego (x0).");
        }
    }
} // Koniec anonimowej przestrzeni nazw

std::vector<SolutionPoint> eulerMethod(
    const OdeFunction& f, double x0, double y0, double h, double x_end) {
    
    validateInputs(f, h, x0, x_end); // Walidacja na poczatku
    std::vector<SolutionPoint> results;
    double x = x0;
    double y = y0;

    while (x <= x_end) {
        results.push_back({x, y});
        y = y + h * f(x, y);
        x = x + h;
    }
    
    return results;
}

std::vector<SolutionPoint> heunMethod(
    const OdeFunction& f, double x0, double y0, double h, double x_end) {
    
    validateInputs(f, h, x0, x_end); // Walidacja na poczatku
    std::vector<SolutionPoint> results;
    double x = x0;
    double y = y0;

    while (x <= x_end) {
        results.push_back({x, y});
        double k1 = f(x, y);
        double y_pred = y + h * k1;
        double k2 = f(x + h, y_pred);
        y = y + (h / 2.0) * (k1 + k2);
        x = x + h;
    }

    return results;
}

std::vector<SolutionPoint> midpointMethod(
    const OdeFunction& f, double x0, double y0, double h, double x_end) {
    
    validateInputs(f, h, x0, x_end); // Walidacja na poczatku
    std::vector<SolutionPoint> results;
    double x = x0;
    double y = y0;

    while (x <= x_end) {
        results.push_back({x, y});
        double k1 = f(x, y);
        double y_mid = y + (h / 2.0) * k1;
        double k2 = f(x + h / 2.0, y_mid);
        y = y + h * k2;
        x = x + h;
    }

    return results;
}

std::vector<SolutionPoint> rungeKutta4(
    const OdeFunction& f, double x0, double y0, double h, double x_end) {
    
    validateInputs(f, h, x0, x_end); // Walidacja na poczatku
    std::vector<SolutionPoint> results;
    double x = x0;
    double y = y0;

    while (x <= x_end) {
        results.push_back({x, y});
        double k1 = h * f(x, y);
        double k2 = h * f(x + h / 2.0, y + k1 / 2.0);
        double k3 = h * f(x + h / 2.0, y + k2 / 2.0);
        double k4 = h * f(x + h, y + k3);
        y = y + (1.0 / 6.0) * (k1 + 2.0 * k2 + 2.0 * k3 + k4);
        x = x + h;
    }

    return results;
}

} // namespace ode
} // namespace numeric