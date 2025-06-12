// examples/main.cpp

#include <iostream>
#include <vector>
#include <limits>
#include "interpolation.h" // Dołączamy naszą nową bibliotekę

// ... (załóżmy, że funkcja LoadData() jest zdefiniowana tak jak wcześniej) ...
std::vector<std::vector<double>> LoadData();

int main() {
    std::vector<double> x_nodes = {0.0, 1.0, 2.0, 3.0, 4.0};
    std::vector<double> y_nodes = {1.0, 2.0, 0.0, 2.0, 3.0};
    
    // Użycie interpolacji Lagrange'a
    try {
        double point_to_eval = 1.5;
        double lagrange_result = numeric::interpolation::lagrangeInterpolation(x_nodes, y_nodes, point_to_eval);
        std::cout << "Wartosc (Lagrange) w punkcie x = " << point_to_eval << " wynosi: " << lagrange_result << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Blad w interpolacji Lagrange'a: " << e.what() << std::endl;
    }
    
    // Użycie interpolacji Newtona
    try {
        double point_to_eval = 1.5;
        double newton_result = numeric::interpolation::newtonInterpolation(x_nodes, y_nodes, point_to_eval);
        std::cout << "Wartosc (Newton) w punkcie x = " << point_to_eval << " wynosi: " << newton_result << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Blad w interpolacji Newtona: " << e.what() << std::endl;
    }


    // Reszta Twojej logiki, np. szukanie optymalnego kroku, może tu zostać
    // i używać tych samych funkcji z biblioteki. Przykład:
    
    std::cout << "\nSzukanie optymalnego kroku dla interpolacji Newtona..." << std::endl;
    double minimalnyBlad = std::numeric_limits<double>::max();
    int optymalnyOdstęp = -1;

    for (int krok = 1; krok < x_nodes.size(); krok++) {
        std::vector<double> x_sub, y_sub;
        for (int i = 0; i < x_nodes.size(); i += krok) {
            x_sub.push_back(x_nodes[i]);
            y_sub.push_back(y_nodes[i]);
        }
        if (x_sub.size() < 2) continue;

        double sumaBledow = 0.0;
        for (size_t j = 0; j < x_nodes.size(); ++j) {
            // Wywołanie funkcji z biblioteki
            double wartoscInterpolowana = numeric::interpolation::newtonInterpolation(x_sub, y_sub, x_nodes[j]);
            sumaBledow += pow(y_nodes[j] - wartoscInterpolowana, 2);
        }
        
        if (sumaBledow < minimalnyBlad) {
            minimalnyBlad = sumaBledow;
            optymalnyOdstęp = krok;
        }
    }

    std::cout << "Najlepszy krok: " << optymalnyOdstęp << ", blad: " << minimalnyBlad << std::endl;

    return 0;
}

// ... Implementacja LoadData() ...