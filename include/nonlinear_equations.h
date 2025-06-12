// include/nonlinear_equations.h

#ifndef NONLINEAR_EQUATIONS_H
#define NONLINEAR_EQUATIONS_H

#include <functional>
#include <optional>
#include <stdexcept>

namespace numeric {
namespace nonlinear {

    using NonLinearFunction = std::function<double(double)>;

    std::optional<double> bisectionMethod(const NonLinearFunction& f, double a, double b,
                                          double epsilon = 1e-7, int max_iter = 100);
    std::optional<double> secantMethod(const NonLinearFunction& f, double x0, double x1,
                                       double epsilon = 1e-7, int max_iter = 100);
    std::optional<double> regulaFalsiMethod(const NonLinearFunction& f, double a, double b,
                                             double epsilon = 1e-7, int max_iter = 100);

    /**
     * @brief Znajduje miejsce zerowe metoda Newtona z analityczna pochodna.
     * @param f Funkcja, ktorej miejsce zerowe szukamy.
     * @param df Analityczna pochodna funkcji f.
     * @param x0 Punkt startowy.
     * @param epsilon Dokladnosc obliczen.
     * @param max_iter Maksymalna liczba iteracji.
     * @return std::optional<double> zawierajacy znaleziony pierwiastek lub pusty.
     */
    std::optional<double> newtonMethod(const NonLinearFunction& f, const NonLinearFunction& df, double x0,
                                       double epsilon = 1e-7, int max_iter = 100);

    /**
     * @brief Znajduje miejsce zerowe metoda Newtona z numeryczna pochodna.
     * @param f Funkcja, ktorej miejsce zerowe szukamy.
     * @param x0 Punkt startowy.
     * @param epsilon Dokladnosc obliczen.
     * @param max_iter Maksymalna liczba iteracji.
     * @param h Krok do obliczenia pochodnej numerycznej.
     * @return std::optional<double> zawierajacy znaleziony pierwiastek lub pusty.
     */
    std::optional<double> newtonMethod(const NonLinearFunction& f, double x0,
                                       double epsilon = 1e-7, int max_iter = 100, double h = 1e-5);


} // namespace nonlinear
} // namespace numeric

#endif // NONLINEAR_EQUATIONS_H