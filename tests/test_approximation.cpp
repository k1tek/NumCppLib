// tests/test_approximation.cpp

#include <iostream>
#include <cassert>
#include <cmath>
#include <stdexcept>
#include "approximation.h"

namespace {
    // Funkcja pomocnicza do porownywania liczb double
    void assertDoubleEqual(double a, double b, double tolerance = 1e-7) {
        assert(std::abs(a - b) < tolerance);
    }
}

/**
 * @brief Testuje poprawnosc aproksymacji dla funkcji, ktora moze byc idealnie odwzorowana.
 * 
 * Uzywamy funkcji liniowej f(x) = 2x + 1. Aproksymacja wielomianem stopnia 1 (N=2)
 * powinna zwrocic dokladnie te sama funkcje, a wiec wartosc w punkcie powinna byc idealna.
 */
void TestApproximateValueAtPointCorrectness() {
    std::cout << "Test: approximateValueAtPoint - funkcja liniowa... ";
    
    auto f_linear = [](double x) { return 2.0 * x + 1.0; };
    
    // Parametry: funkcja, przedzial [0, 1], wielomian st. 1 (N=2), punkt do oceny 0.5
    double value = numeric::approximation::approximateValueAtPoint(f_linear, 0.0, 1.0, 2, 0.5);
    
    // Oczekiwany wynik: f(0.5) = 2 * 0.5 + 1 = 2.0
    assertDoubleEqual(value, 2.0);
    
    std::cout << "OK" << std::endl;
}

/**
 * @brief Testuje, czy funkcja poprawnie rzuca wyjatek dla nieprawidlowych danych wejsciowych.
 * 
 * Sprawdzamy przypadek, gdy liczba wspolczynnikow wielomianu N jest niedodatnia,
 * co jest logicznym bledem i powinno byc zgloszone.
 */
void TestApproximateValueAtPointThrowsOnInvalidInput() {
    std::cout << "Test: approximateValueAtPoint - niepoprawny stopien N... ";
    
    auto f_dummy = [](double x) { return x; };
    
    try {
        // Proba wywolania z N = 0, co powinno rzucic wyjatek
        numeric::approximation::approximateValueAtPoint(f_dummy, 0.0, 1.0, 0, 0.5);
        assert(false); // Ten kod nie powinien byc osiagniety, jesli rzucono wyjatek
    } catch(const std::invalid_argument&) {
        // Zlapano oczekiwany wyjatek, test zakonczony sukcesem
        std::cout << "OK" << std::endl;
    }
}