// include/interpolation.h

#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include <vector>
#include <stdexcept>

namespace numeric {
namespace interpolation {

    /**
     * @brief Oblicza wartość funkcji w punkcie xp używając wielomianu interpolacyjnego Lagrange'a.
     * 
     * @param x Wektor węzłów (wartości x).
     * @param y Wektor wartości funkcji w węzłach (wartości y).
     * @param xp Punkt, w którym ma być obliczona wartość interpolowana.
     * @return double Wartość interpolowana w punkcie xp.
     * @throws std::invalid_argument jeśli wektory x i y mają różne rozmiary lub są puste.
     */
    double lagrangeInterpolation(const std::vector<double>& x, const std::vector<double>& y, double xp);

    /**
     * @brief Oblicza wartość funkcji w punkcie xp używając wielomianu interpolacyjnego Newtona.
     * 
     * @param x Wektor węzłów (wartości x).
     * @param y Wektor wartości funkcji w węzłach (wartości y).
     * @param xp Punkt, w którym ma być obliczona wartość interpolowana.
     * @return double Wartość interpolowana w punkcie xp.
     * @throws std::invalid_argument jeśli wektory x i y mają różne rozmiary lub są puste.
     */
    double newtonInterpolation(const std::vector<double>& x, const std::vector<double>& y, double xp);

} // namespace interpolation
} // namespace numeric

#endif // INTERPOLATION_H