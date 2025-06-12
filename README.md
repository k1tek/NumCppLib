# NumCppLib - Biblioteka Metod Numerycznych w C++
Wykonali: Arek Baczyński, Bartosz Czapla
![Build Status](https://img.shields.io/badge/build-passing-brightgreen)
![C++ Standard](https://img.shields.io/badge/c%2B%2B-17-blue.svg)
![License](https://img.shields.io/badge/license-MIT-lightgrey.svg)

**NumCppLib** to nowoczesna, modułowa biblioteka napisana w C++17, implementująca fundamentalne algorytmy metod numerycznych. Została zaprojektowana z myślą o czystości kodu, elastyczności i łatwości użycia w innych projektach.

## Spis Treści
1. [O Projekcie](#o-projekcie)
2. [Funkcjonalności](#funkcjonalności)
3. [Wymagania i Budowanie](#wymagania-i-budowanie)
4. [Przegląd API i Przykłady Użycia](#przegląd-api-i-przykłady-użycia)
    - [Algebra Liniowa](#algebra-liniowa)
    - [Interpolacja](#interpolacja)
    - [Całkowanie Numeryczne](#całkowanie-numeryczne)
    - [Równania Różniczkowe Zwyczajne](#równania-różniczkowe-zwyczajne)
    - [Równania Nieliniowe](#równania-nieliniowe)
    - [Aproksymacja](#aproksymacja)
5. [Uruchamianie Testów](#uruchamianie-testów)
6. [Filozofia Projektu](#filozofia-projektu)

## O Projekcie

Celem projektu jest dostarczenie zbioru podstawowych algorytmów numerycznych w postaci dobrze zorganizowanej biblioteki C++. Każdy moduł został zaprojektowany tak, aby był jak najbardziej niezależny i łatwy do zintegrowania. Biblioteka kładzie nacisk na nowoczesne praktyki C++, takie jak użycie `std::function` dla elastyczności, `std::optional` do obsługi wyników i przemyślaną obsługę błędów.

## Funkcjonalności

Biblioteka jest podzielona na następujące moduły:

-   **Algebra Liniowa (`linear_algebra`)**: Rozwiązywanie układów równań liniowych.
    -   Eliminacja Gaussa z częściowym pivotingiem
    -   Dekompozycja LU
-   **Interpolacja (`interpolation`)**: Znajdowanie wartości funkcji w punktach pośrednich.
    -   Wielomian interpolacyjny Lagrange'a
    -   Wielomian interpolacyjny Newtona
-   **Całkowanie Numeryczne (`integration`)**: Obliczanie całek oznaczonych.
    -   Metoda prostokątów, trapezów i Simpsona
    -   Kwadratura Gaussa-Legendre'a (w tym wersja złożona)
-   **Równania Różniczkowe (`differential_equations`)**: Rozwiązywanie równań różniczkowych zwyczajnych pierwszego rzędu.
    -   Metoda Eulera, Heuna, punktu środkowego
    -   Metoda Rungego-Kutty 4. rzędu
-   **Równania Nieliniowe (`nonlinear_equations`)**: Znajdowanie miejsc zerowych funkcji.
    -   Metoda bisekcji, siecznych, regula falsi
    -   Metoda Newtona (z pochodną analityczną i numeryczną)
-   **Aproksymacja (`approximation`)**: Aproksymacja funkcji wielomianami.
    -   Aproksymacja średniokwadratowa

## Wymagania i Budowanie

### Wymagania
-   Kompilator C++ obsługujący standard C++17 (np. GCC, Clang, MSVC)
-   CMake (wersja 3.10 lub nowsza)

### Budowanie
Projekt wykorzystuje CMake do zarządzania procesem budowania. Aby skompilować bibliotekę, przykłady i testy, wykonaj następujące kroki w terminalu:

```bash
# 1. Stworz folder na pliki budowania
mkdir build

# 2. Przejdz do stworzonego folderu
cd build

# 3. Uruchom CMake, aby skonfigurowac projekt
cmake ..

# 4. Zbuduj wszystkie cele (biblioteke, przyklady, testy)
cmake --build .
```
Pliki wykonywalne dla przykładów i testów znajdą się w folderze `build/`.

## Przegląd API i Przykłady Użycia

Wszystkie funkcje znajdują się w przestrzeni nazw `numeric`.

### Algebra Liniowa
Rozwiązywanie układu równań `Ax = b`.
```cpp
#include "linear_algebra.h"
#include <vector>

std::vector<std::vector<double>> A = {{2, 1, -1}, {-3, -1, 2}, {-2, 1, 2}};
std::vector<double> b = {8, -11, -3};

// Oczekiwany wynik: {2, 3, -1}
std::vector<double> x = numeric::linear_algebra::gaussElimination(A, b);
```

### Interpolacja
Obliczanie wartości funkcji `f(1.5)` na podstawie znanych punktów.
```cpp
#include "interpolation.h"
#include <vector>

std::vector<double> x_nodes = {0, 1, 2};
std::vector<double> y_nodes = {1, 2, 5}; // f(x) = x^2 + 1

double value = numeric::interpolation::newtonInterpolation(x_nodes, y_nodes, 1.5);
// Oczekiwany wynik: 3.25
```

### Całkowanie Numeryczne
Obliczanie całki z `x^2` na przedziale `[0, 3]`.
```cpp
#include "integration.h"

auto my_function = [](double x) { return x * x; };
double result = numeric::integration::simpsonRule(my_function, 0.0, 3.0, 100);
// Oczekiwany wynik: 9.0
```

### Równania Różniczkowe Zwyczajne
Rozwiązywanie `dy/dx = y` z warunkiem `y(0) = 1`.
```cpp
#include "differential_equations.h"

auto ode_func = [](double x, double y) { return y; };
auto solution_points = numeric::ode::rungeKutta4(ode_func, 0.0, 1.0, 0.1, 1.0);
double final_y = solution_points.back().y;
// Oczekiwany wynik: e^1 ≈ 2.71828
```

### Równania Nieliniowe
Znajdowanie miejsca zerowego dla `f(x) = x^2 - 9`.
```cpp
#include "nonlinear_equations.h"
#include <optional>

auto parabola = [](double x) { return x * x - 9; };
auto parabola_deriv = [](double x) { return 2 * x; };

// Metoda Newtona z pochodna analityczna
std::optional<double> root1 = numeric::nonlinear::newtonMethod(parabola, parabola_deriv, 5.0);

// Metoda Newtona z pochodna numeryczna (przeciazona funkcja)
std::optional<double> root2 = numeric::nonlinear::newtonMethod(parabola, 5.0);
```

### Aproksymacja
Aproksymacja funkcji `f(x) = 2x+1` wielomianem stopnia 1.
```cpp
#include "approximation.h"

auto linear_func = [](double x) { return 2.0 * x + 1.0; };
double approx_value = numeric::approximation::approximateValueAtPoint(linear_func, 0.0, 1.0, 2, 0.5);
// Oczekiwany wynik: 2.0
```

## Uruchamianie Testów

Biblioteka jest wyposażona w zestaw testów jednostkowych. Po zbudowaniu projektu, można je uruchomić na dwa sposoby:

1.  **Uruchomienie wszystkich testów naraz (zalecane):**
    W terminalu, będąc w folderze `build`, wykonaj komendę:
    ```bash
    ctest
    ```
    Otrzymasz podsumowanie, które testy przeszły pomyślnie.

2.  **Uruchomienie pojedynczego zestawu testów:**
    Projekt buduje jeden program testowy o nazwie `run_tests`. Możesz go uruchomić bezpośrednio:
    ```bash
    ./run_tests  # Na systemach Linux/macOS
    run_tests.exe # Na systemie Windows
    ```

## Filozofia Projektu

-   **Modułowość:** Każdy algorytm należy do logicznej przestrzeni nazw i znajduje się w osobnym pliku, co ułatwia zarządzanie i rozbudowę.
-   **Elastyczność:** Szerokie użycie `std::function` pozwala użytkownikowi na przekazywanie dowolnych obiektów wywoływalnych (funkcji, lambd, funktorów) jako argumentów.
-   **Bezpieczeństwo i Obsługa Błędów:**
    -   **Błędy programisty** (np. podanie nieprawidłowych argumentów, ujemny krok) są sygnalizowane przez rzucenie wyjątku `std::invalid_argument`.
    -   **Oczekiwane niepowodzenia algorytmu** (np. brak znalezienia pierwiastka w danym przedziale) są sygnalizowane przez zwrócenie `std::optional`, co pozwala na czystą i bezpieczną obsługę wyniku.
-   **Spójność:** Cała biblioteka stosuje jednolitą konwencję nazewnictwa funkcji `camelCase`.
-   **Separacja Obliczeń od I/O:** Rdzeń biblioteki zajmuje się wyłącznie obliczeniami. Nie wykonuje żadnych operacji wejścia/wyjścia (np. drukowania na konsoli czy zapisu do plików), pozostawiając to w gestii użytkownika.
