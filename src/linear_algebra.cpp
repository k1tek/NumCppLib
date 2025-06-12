// linear_algebra.cpp
#include "linear_algebra.h" // Dołączamy własny plik nagłówkowy

namespace numeric {
namespace linear_algebra {

void printMatrix(const std::vector<std::vector<double>>& A, const std::vector<double>& B) {
    int n = static_cast<int>(A.size());
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < static_cast<int>(A[i].size()); ++j) {
            std::cout << std::setw(10) << std::fixed << std::setprecision(4) << A[i][j] << "\t";
        }
        std::cout << "| " << B[i] << std::endl;
    }
}

std::vector<double> gaussElimination(std::vector<std::vector<double>> A, std::vector<double> b) {
    int n = static_cast<int>(A.size());
    if (n == 0 || A[0].size() != n || b.size() != n) {
        throw std::invalid_argument("Nieprawidlowe wymiary macierzy lub wektora!");
    }
    for (int k = 0; k < n - 1; k++) {
        int maxRow = k;
        for (int i = k + 1; i < n; i++) {
            if (std::abs(A[i][k]) > std::abs(A[maxRow][k])) {
                maxRow = i;
            }
        }
        
        if (maxRow != k) {
            std::swap(A[k], A[maxRow]);
            std::swap(b[k], b[maxRow]);
        }
        
        // Sprawdzenie osobliwości PO potencjalnej zamianie wierszy
        if (std::abs(A[k][k]) < 1e-12) {
             // Jeśli po zamianie wierszy na diagonali nadal jest zero, macierz jest osobliwa
            throw std::runtime_error("Układ rownan jest osobliwy lub liniowo zależny.");
        }

        for (int i = k + 1; i < n; i++) {
            double factor = A[i][k] / A[k][k];
            for (int j = k; j < n; j++) {
                A[i][j] -= factor * A[k][j];
            }
            b[i] -= factor * b[k];
        }
    }

    std::vector<double> x(n);
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0.0;
        for (int j = i + 1; j < n; j++) {
            sum += A[i][j] * x[j];
        }
        if (std::abs(A[i][i]) < 1e-12) {
            // Ten błąd jest redundantny, jeśli pierwszy test jest poprawny, ale zostawiam dla bezpieczeństwa
            throw std::runtime_error("Dzielenie przez zero podczas podstawiania wstecz (macierz osobliwa).");
        }
        x[i] = (b[i] - sum) / A[i][i];
    }
    return x;
}

std::vector<double> luDecomposition(std::vector<std::vector<double>> A, std::vector<double> b) {
    const int n = static_cast<int>(A.size());

    // Sprawdzenie poprawności wymiarów
    if (n == 0 || A[0].size() != n || b.size() != n) {
        throw std::invalid_argument("Nieprawidłowe wymiary macierzy lub wektora.");
    }
    
    std::vector<std::vector<double>> L(n, std::vector<double>(n, 0.0));
    std::vector<std::vector<double>>& U = A; // Używamy macierzy A jako U dla oszczędności pamięci

    // --- KROK 1: Dekompozycja LU z częściowym pivotingiem ---
    for (int k = 0; k < n - 1; ++k) {
        // Znajdź wiersz z maksymalnym elementem (pivot)
        int max_row = k;
        for (int i = k + 1; i < n; ++i) {
            if (std::abs(U[i][k]) > std::abs(U[max_row][k])) {
                max_row = i;
            }
        }

        // Zamiana wierszy w U, L i b
        if (max_row != k) {
            std::swap(U[k], U[max_row]);
            std::swap(b[k], b[max_row]); 
            std::swap(L[k], L[max_row]);
        }

        // Sprawdzenie osobliwości
        if (std::abs(U[k][k]) < 1e-12) {
            throw std::runtime_error("Macierz jest osobliwa, nie można kontynuowac dekompozycji.");
        }

        // Eliminacja Gaussa
        for (int i = k + 1; i < n; ++i) {
            double factor = U[i][k] / U[k][k];
            L[i][k] = factor;
            for (int j = k; j < n; ++j) {
                U[i][j] -= factor * U[k][j];
            }
        }
    }
    
    // Uzupełnienie diagonali macierzy L
    for (int i = 0; i < n; ++i) {
        L[i][i] = 1.0;
    }

    // --- KROK 2: Podstawienie w przód (rozwiązanie Lz = b) ---
    std::vector<double> z(n);
    for (int i = 0; i < n; ++i) {
        double sum = 0.0;
        for (int j = 0; j < i; ++j) {
            sum += L[i][j] * z[j];
        }
        z[i] = b[i] - sum;
    }

    // --- KROK 3: Podstawienie wstecz (rozwiązanie Ux = z) ---
    std::vector<double> x(n);
    for (int i = n - 1; i >= 0; --i) {
        double sum = 0.0;
        for (int j = i + 1; j < n; ++j) {
            sum += U[i][j] * x[j];
        }
        if (std::abs(U[i][i]) < 1e-12) {
            throw std::runtime_error("Dzielenie przez zero podczas podstawiania wstecz (macierz osobliwa).");
        }
        x[i] = (z[i] - sum) / U[i][i];
    }

    return x;
}



} // namespace linear_algebra
} // namespace numeric