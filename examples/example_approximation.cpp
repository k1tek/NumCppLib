#include <iostream>
#include <vector>
#include "approximation.h"

double my_function(double x) {
    return cos(x) * x * x * x * x;
}

int main() {
    // Przykład użycia funkcji approximate_value_at_point
    auto f = my_function; // Funkcja do aproksymacji
    double eval_point = 1.0; // Punkt, w którym chcemy ocenić funkcję
    int N = 3; // Stopień wielomianu -- OSTROŻNIE ! Używamy bazy standardowej, przy dużeych ilościach dostajemy macierz ortogonalną.
    double result = numeric::approximation::approximateValueAtPoint(f, 0.0, 3.14159265, N, eval_point);
    // Wyświetlenie wyniku
    std::cout << "Aproksymowana wartosc funkcji w punkcie " << eval_point << " wynosi: " << result << std::endl;
    // Możesz dodać więcej testów lub sprawdzić inne funkcje

    return 0;
}