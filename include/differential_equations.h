// include/differential_equations.h

#ifndef DIFFERENTIAL_EQUATIONS_H
#define DIFFERENTIAL_EQUATIONS_H

#include <vector>
#include <functional>
#include <stdexcept> // Potrzebne dla std::invalid_argument

namespace numeric {
namespace ode {

    using OdeFunction = std::function<double(double x, double y)>;

    struct SolutionPoint {
        double x;
        double y;
    };

    /**
     * @brief Rozwiazuje rownanie rozniczkowe zwyczajne metoda Eulera.
     * @throws std::invalid_argument jesli krok h jest niedodatni, x_end < x0, lub funkcja f jest nieprawidlowa.
     */
    std::vector<SolutionPoint> eulerMethod(
        const OdeFunction& f, double x0, double y0, double h, double x_end);

    /**
     * @brief Rozwiazuje rownanie rozniczkowe zwyczajne metoda Heuna.
     * @throws std::invalid_argument jesli krok h jest niedodatni, x_end < x0, lub funkcja f jest nieprawidlowa.
     */
    std::vector<SolutionPoint> heunMethod(
        const OdeFunction& f, double x0, double y0, double h, double x_end);

    /**
     * @brief Rozwiazuje rownanie rozniczkowe zwyczajne metoda punktu srodkowego.
     * @throws std::invalid_argument jesli krok h jest niedodatni, x_end < x0, lub funkcja f jest nieprawidlowa.
     */
    std::vector<SolutionPoint> midpointMethod(
        const OdeFunction& f, double x0, double y0, double h, double x_end);

    /**
     * @brief Rozwiazuje rownanie rozniczkowe zwyczajne metoda Rungego-Kutty 4. rzedu.
     * @throws std::invalid_argument jesli krok h jest niedodatni, x_end < x0, lub funkcja f jest nieprawidlowa.
     */
    std::vector<SolutionPoint> rungeKutta4(
        const OdeFunction& f, double x0, double y0, double h, double x_end);

} // namespace ode
} // namespace numeric

#endif // DIFFERENTIAL_EQUATIONS_H