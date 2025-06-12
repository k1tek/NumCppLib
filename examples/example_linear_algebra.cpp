#include <iostream>
#include <vector>
#include "linear_algebra.h" // Dołączamy nagłówek naszej biblioteki

// Funkcja pomocnicza do drukowania wektora
void print_vector(const std::vector<double>& vec) {
    std::cout << "[ ";
    for (const auto& val : vec) {
        std::cout << val << " ";
    }
    std::cout << "]" << std::endl;
}

int main() {
    //std::cout << "=== Przyklad uzycia biblioteki NumCppLib ===" << std::endl;

    // Przykładowe wektory
    std::vector<std::vector<double>> a = {{6, 2, 3},
                             {5, 5, 3},
                             {7, 8, 9}};
    std::vector<double> b = {4, 5, 6};

    // Drukujemy macierz i wektor
    std::cout << "Macierz A i wektor b:" << std::endl;
    // Używamy funkcji z biblioteki do drukowania macierzy
    numeric::linear_algebra::printMatrix(a, b);
    //Używamy naszej funkcji z biblioteki
    std::vector<double> solution1 = numeric::linear_algebra::luDecomposition(a, b);
    std::vector<double> solution2 = numeric::linear_algebra::gaussElimination(a,b);
    // Drukujemy rozwiązanie układu równań
    std::cout << "Rozwiazanie ukladu rownan (metoda LU): ";
    print_vector(solution1);
    std::cout << "Rozwiazanie ukladu rownan (eliminacja Gaussa): ";
    print_vector(solution2);

    

    return 0;
}