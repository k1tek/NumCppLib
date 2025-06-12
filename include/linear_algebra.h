#pragma once // Zapewnia, że plik będzie dołączony tylko raz

#include <vector>
#include <stdexcept> // Do rzucania wyjątków
#include <iostream> // Do drukowania na konsolę
#include <iomanip> // Do formatowania wyjścia
#include <algorithm> // Do std::swap
#include <numeric> // Do std::iota

namespace numeric {
namespace linear_algebra {

    /**
     * @brief Dodaje dwa wektory (element po elemencie).
     * 
     * @param a Pierwszy wektor.
     * @param b Drugi wektor.
     * @return std::vector<double> Wektor będący sumą wektorów a i b.
     * @throw std::invalid_argument Jeśli wektory mają różne rozmiary.
     */
    void printMatrix(const std::vector<std::vector<double>>& A, const std::vector<double>& B);
    std::vector<double> gaussElimination(std::vector<std::vector<double>> A, std::vector<double> b);
    std::vector<double> luDecomposition(std::vector<std::vector<double>> A, std::vector<double> b);

    // Tutaj będziesz dodawać deklaracje kolejnych funkcji, np.:
    // double dot_product(const std::vector<double>& a, const std::vector<double>& b);

} // namespace linear_algebra
} // namespace numeric