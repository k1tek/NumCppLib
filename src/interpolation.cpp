// src/interpolation.cpp

#include "interpolation.h" // Nasz plik nagłówkowy

namespace numeric {
namespace interpolation {

// === Funkcje pomocnicze, ukryte przed użytkownikiem ===
namespace { // Anonimowa przestrzeń nazw

    // Funkcja obliczająca tabelę ilorazów różnicowych dla wielomianu Newtona
    std::vector<std::vector<double>> calculateDividedDifferences(const std::vector<double>& x, const std::vector<double>& y) {
        int n = static_cast<int>(x.size());
        std::vector<std::vector<double>> table(n, std::vector<double>(n, 0.0));

        // Pierwsza kolumna to wartości y
        for (int i = 0; i < n; i++) {
            table[i][0] = y[i];
        }

        // Obliczanie kolejnych kolumn
        for (int j = 1; j < n; j++) {
            for (int i = 0; i < n - j; i++) {
                if (std::abs(x[i + j] - x[i]) < 1e-12) {
                     throw std::runtime_error("Dzielenie przez zero w ilorazach różnicowych (węzły x nie są unikalne).");
                }
                table[i][j] = (table[i + 1][j - 1] - table[i][j - 1]) / (x[i + j] - x[i]);
            }
        }
        return table;
    }

} // Koniec anonimowej przestrzeni nazw

// === Implementacja funkcji publicznych ===

double lagrangeInterpolation(const std::vector<double>& x, const std::vector<double>& y, double xp) {
    if (x.size() != y.size() || x.empty()) {
        throw std::invalid_argument("Wektory x i y muszą mieć ten sam, niezerowy rozmiar.");
    }
    
    double result = 0.0;
    int n = static_cast<int>(x.size());

    for (int i = 0; i < n; i++) {
        double basis_polynomial = 1.0;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                 if (std::abs(x[i] - x[j]) < 1e-12) {
                     throw std::runtime_error("Dzielenie przez zero w wielomianie Lagrange'a (węzły x nie są unikalne).");
                }
                basis_polynomial *= (xp - x[j]) / (x[i] - x[j]);
            }
        }
        result += y[i] * basis_polynomial;
    }

    return result;
}


double newtonInterpolation(const std::vector<double>& x, const std::vector<double>& y, double xp) {
    if (x.size() != y.size() || x.empty()) {
        throw std::invalid_argument("Wektory x i y muszą mieć ten sam, niezerowy rozmiar.");
    }

    // Krok 1: Oblicz tablicę ilorazów różnicowych
    auto divided_diff_table = calculateDividedDifferences(x, y);

    // Krok 2: Oblicz wartość wielomianu w punkcie xp
    int n = static_cast<int>(x.size());
    double result = divided_diff_table[0][0];
    double product_term = 1.0;

    for (int i = 1; i < n; i++) {
        product_term *= (xp - x[i - 1]);
        result += divided_diff_table[0][i] * product_term;
    }

    return result;
}

} // namespace interpolation
} // namespace numeric