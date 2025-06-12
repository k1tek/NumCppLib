// src/integration.cpp

#include "integration.h"
#include <cmath>
#include <stdexcept> // Upewnij sie, ze jest dolaczony

namespace numeric {
namespace integration {

// Prywatna funkcja pomocnicza do walidacji dla wiekszosci metod
void validateBasicInputs(const std::function<double(double)>& f, int n) {
    if (!f) {
        throw std::invalid_argument("Funkcja f nie moze byc pusta.");
    }
    if (n <= 0) {
        throw std::invalid_argument("Liczba podprzedzialow (n) musi byc dodatnia.");
    }
}

// Prywatna funkcja pomocnicza do walidacji dla Gaussa
void validateGaussInputs(const std::function<double(double)>& f, int nodes) {
    if (!f) {
        throw std::invalid_argument("Funkcja f nie moze byc pusta.");
    }
    if (nodes != 2 && nodes != 3 && nodes != 4) {
        throw std::invalid_argument("Nieobslugiwana liczba wezlow. Wybierz 2, 3 lub 4.");
    }
}

double rectangleRule(const std::function<double(double)>& f, double a, double b, int n) {
    validateBasicInputs(f, n);
    double h = (b - a) / static_cast<double>(n);
    double sum = 0.0;
    for (int i = 0; i < n; ++i) {
        double x = a + h * (static_cast<double>(i) + 0.5);
        sum += f(x);
    }
    return sum * h;
}

double trapezoidalRule(const std::function<double(double)>& f, double a, double b, int n) {
    validateBasicInputs(f, n);
    double h = (b - a) / static_cast<double>(n);
    double sum = 0.5 * (f(a) + f(b));
    for (int i = 1; i < n; ++i) {
        sum += f(a + static_cast<double>(i) * h);
    }
    return sum * h;
}

double simpsonRule(const std::function<double(double)>& f, double a, double b, int n) {
    validateBasicInputs(f, n);
    if (n % 2 != 0) {
        n++;
    }
    double h = (b - a) / static_cast<double>(n);
    double sum = f(a) + f(b);
    for (int i = 1; i < n; i += 2) {
        sum += 4 * f(a + static_cast<double>(i) * h);
    }
    for (int i = 2; i < n - 1; i += 2) {
        sum += 2 * f(a + static_cast<double>(i) * h);
    }
    return sum * h / 3.0;
}

double gaussLegendre(const std::function<double(double)>& f, double a, double b, int nodes) {
    validateGaussInputs(f, nodes);
    static const double x2[] = { -0.5773502691896257, 0.5773502691896257 };
    static const double w2[] = { 1.0, 1.0 };
    static const double x3[] = { -0.7745966692414834, 0.0, 0.7745966692414834 };
    static const double w3[] = { 0.5555555555555556, 0.8888888888888888, 0.5555555555555556 };
    static const double x4[] = { -0.8611363115940526, -0.3399810435848563, 0.3399810435848563, 0.8611363115940526 };
    static const double w4[] = { 0.3478548451374538, 0.6521451548625461, 0.6521451548625461, 0.3478548451374538 };

    const double* x_nodes;
    const double* w_weights;
    switch (nodes) {
        case 2: x_nodes = x2; w_weights = w2; break;
        case 3: x_nodes = x3; w_weights = w3; break;
        case 4: x_nodes = x4; w_weights = w4; break;
    }
   
    double sum = 0.0;
    double c1 = (b - a) / 2.0;
    double c2 = (b + a) / 2.0;
    for (int i = 0; i < nodes; ++i) {
        double xi = c1 * x_nodes[i] + c2;
        sum += w_weights[i] * f(xi);
    }
    return c1 * sum;
}

double segmentedGaussLegendre(const std::function<double(double)>& f, double a, double b, int nodes, int segments) {
    if (!f) {
        throw std::invalid_argument("Funkcja f nie moze byc pusta.");
    }
    if (segments <= 0) {
        throw std::invalid_argument("Liczba segmentow musi byc dodatnia.");
    }
    double total = 0.0;
    double h = (b - a) / static_cast<double>(segments);
    for (int i = 0; i < segments; ++i) {
        double seg_a = a + static_cast<double>(i) * h;
        double seg_b = seg_a + h;
        total += gaussLegendre(f, seg_a, seg_b, nodes);
    }
    return total;
}

} // namespace integration
} // namespace numeric