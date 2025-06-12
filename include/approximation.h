#pragma once
#include <vector>
#include <functional>
#include <utility> // Dla std::pair

namespace numeric {
namespace approximation {

    // Przykład funkcji - aproksymacja metodą najmniejszych kwadratów dla linii prostej
    // Zwraca parę: [współczynnik a, wyraz wolny b] dla y = ax + b
   double approximateValueAtPoint(const std::function<double(double)>& f, double a, double b, int N, double eval_point);
}
}