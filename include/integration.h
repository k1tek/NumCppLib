// include/integration.h

#ifndef INTEGRATION_H
#define INTEGRATION_H

#include <vector>
#include <functional> // Kluczowe dla std::function
#include <stdexcept>

namespace numeric {
namespace integration {

    /**
     * @brief Oblicza całkę oznaczoną metodą prostokątów.
     * @param f Funkcja do całkowania.
     * @param a Dolna granica całkowania.
     * @param b Górna granica całkowania.
     * @param n Liczba podprzedziałów.
     * @return Przybliżona wartość całki.
     */
    double rectangleRule(const std::function<double(double)>& f, double a, double b, int n);

    /**
     * @brief Oblicza całkę oznaczoną metodą trapezów.
     * @param f Funkcja do całkowania.
     * @param a Dolna granica całkowania.
     * @param b Górna granica całkowania.
     * @param n Liczba podprzedziałów.
     * @return Przybliżona wartość całki.
     */
    double trapezoidalRule(const std::function<double(double)>& f, double a, double b, int n);

    /**
     * @brief Oblicza całkę oznaczoną metodą Simpsona.
     * @param f Funkcja do całkowania.
     * @param a Dolna granica całkowania.
     * @param b Górna granica całkowania.
     * @param n Liczba podprzedziałów (musi być parzysta, zostanie zaokrąglona w górę).
     * @return Przybliżona wartość całki.
     */
    double simpsonRule(const std::function<double(double)>& f, double a, double b, int n);

    /**
     * @brief Oblicza całkę oznaczoną kwadraturą Gaussa-Legendre'a.
     * @param f Funkcja do całkowania.
     * @param a Dolna granica całkowania.
     * @param b Górna granica całkowania.
     * @param nodes Liczba węzłów kwadratury (obsługiwane 2, 3, 4).
     * @return Przybliżona wartość całki.
     */
    double gaussLegendre(const std::function<double(double)>& f, double a, double b, int nodes);

    /**
     * @brief Oblicza całkę oznaczoną złożoną kwadraturą Gaussa-Legendre'a.
     * @param f Funkcja do całkowania.
     * @param a Dolna granica całkowania.
     * @param b Górna granica całkowania.
     * @param nodes Liczba węzłów na segment.
     * @param segments Liczba segmentów, na które zostanie podzielony przedział [a, b].
     * @return Przybliżona wartość całki.
     */
    double segmentedGaussLegendre(const std::function<double(double)>& f, double a, double b, int nodes, int segments);

} // namespace integration
} // namespace numeric

#endif // INTEGRATION_H