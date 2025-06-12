// src/nonlinear_equations.cpp

#include "nonlinear_equations.h"
#include <cmath>
#include <limits>

namespace numeric {
namespace nonlinear {

std::optional<double> bisectionMethod(const NonLinearFunction& f, double a, double b, double epsilon, int max_iter) {
    if (!f || a >= b || epsilon <= 0 || max_iter <= 0) {
        throw std::invalid_argument("Nieprawidlowe argumenty dla metody bisekcji.");
    }

    double fa = f(a);
    double fb = f(b);

    if (fa * fb >= 0) {
        // Warunek konieczny dla metody bisekcji nie jest spelniony.
        return std::nullopt;
    }

    for (int i = 0; i < max_iter; ++i) {
        double c = a + (b - a) / 2.0; // Stabilniejsza numerycznie wersja (a+b)/2
        double fc = f(c);

        if (std::abs(b - a) < epsilon || std::abs(fc) < epsilon) {
            return c;
        }

        if (fa * fc < 0) {
            b = c;
            fb = fc;
        } else {
            a = c;
            fa = fc;
        }
    }

    return std::nullopt; // Nie znaleziono pierwiastka w zadanej liczbie iteracji
}

std::optional<double> secantMethod(const NonLinearFunction& f, double x0, double x1, double epsilon, int max_iter) {
    if (!f || epsilon <= 0 || max_iter <= 0) {
        throw std::invalid_argument("Nieprawidlowe argumenty dla metody siecznych.");
    }

    for (int i = 0; i < max_iter; ++i) {
        double fx0 = f(x0);
        double fx1 = f(x1);

        if (std::abs(fx1) < epsilon) {
            return x1;
        }

        if (std::abs(fx1 - fx0) < std::numeric_limits<double>::epsilon()) {
            // Unikniecie dzielenia przez zero
            return std::nullopt;
        }

        double x_next = x1 - fx1 * (x1 - x0) / (fx1 - fx0);
        
        if (std::abs(x_next - x1) < epsilon) {
            return x_next;
        }

        x0 = x1;
        x1 = x_next;
    }

    return std::nullopt;
}

// Wersja analityczna (rdzen implementacji)
std::optional<double> newtonMethod(const NonLinearFunction& f, const NonLinearFunction& df, double x0, double epsilon, int max_iter) {
    if (!f || !df || epsilon <= 0 || max_iter <= 0) {
        throw std::invalid_argument("Nieprawidlowe argumenty dla metody Newtona.");
    }

    double x = x0;
    for (int i = 0; i < max_iter; ++i) {
        double fx = f(x);
        double dfx = df(x);

        if (std::abs(fx) < epsilon) {
            return x;
        }

        if (std::abs(dfx) < std::numeric_limits<double>::epsilon()) {
            return std::nullopt; // Pochodna bliska zeru
        }

        double x_next = x - fx / dfx;

        if (std::abs(x_next - x) < epsilon) {
            return x_next;
        }
        x = x_next;
    }

    return std::nullopt;
}

// Wersja numeryczna (przeciazona)
std::optional<double> newtonMethod(const NonLinearFunction& f, double x0, double epsilon, int max_iter, double h) {
    if (!f) {
        throw std::invalid_argument("Funkcja f nie moze byc pusta.");
    }

    // Tworzymy pochodna numeryczna za pomoca lambdy
    NonLinearFunction numerical_df = [f, h](double x) {
        return (f(x + h) - f(x)) / h;
    };

    // Wywolujemy wersje analityczna, podajac jej nasza swiezo stworzona pochodna numeryczna.
    // Dzieki temu cala logika petli jest w jednym miejscu.
    return newtonMethod(f, numerical_df, x0, epsilon, max_iter);
}

std::optional<double> regulaFalsiMethod(const NonLinearFunction& f, double a, double b, double epsilon, int max_iter) {
    if (!f || a >= b || epsilon <= 0 || max_iter <= 0) {
        throw std::invalid_argument("Nieprawidlowe argumenty dla metody regula falsi.");
    }
    
    double fa = f(a);
    double fb = f(b);

    if (fa * fb >= 0) {
        return std::nullopt;
    }

    for (int i = 0; i < max_iter; ++i) {
        if (std::abs(fb - fa) < std::numeric_limits<double>::epsilon()) {
            return std::nullopt;
        }
        
        double c = (a * fb - b * fa) / (fb - fa);
        double fc = f(c);
        
        if (std::abs(b - a) < epsilon || std::abs(fc) < epsilon) {
            return c;
        }
        
        if (fa * fc < 0) {
            b = c;
            fb = fc;
        } else {
            a = c;
            fa = fc;
        }
    }
    
    return std::nullopt;
}


} // namespace nonlinear
} // namespace numeric