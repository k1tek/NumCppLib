# Wymagana minimalna wersja CMake
cmake_minimum_required(VERSION 3.10)

# Nazwa projektu i standard C++
project(NumCppLib VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# === KROK 1: Definicja naszej biblioteki ===
add_library(numcpplib src/linear_algebra.cpp
                src/approximation.cpp
                src/interpolation.cpp
                src/integration.cpp
                src/differential_equations.cpp
                src/nonlinear_equations.cpp)
# Ustawiamy opcje kompilacji
target_include_directories(numcpplib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# === KROK 2: Definicja przykładu użycia ===
add_executable(example_linear_algebra examples/example_linear_algebra.cpp)
add_executable(example_approximation examples/example_approximation.cpp)
add_executable(example_interpolation examples/example_interpolation.cpp)
add_executable(example_integration examples/example_integration.cpp)
add_executable(example_differential_equations examples/example_differential_equations.cpp)
add_executable(example_nonlinear_equations examples/example_nonlinear_equations.cpp)


target_link_libraries(example_linear_algebra numcpplib)
target_link_libraries(example_approximation numcpplib)
target_link_libraries(example_interpolation numcpplib)
target_link_libraries(example_integration numcpplib)
target_link_libraries(example_differential_equations numcpplib)
target_link_libraries(example_nonlinear_equations numcpplib)

# === KROK 3: Definicja testów (WERSJA BEZ ŻADNEJ MAGII) ===
# Tworzymy program testowy tak samo, jak każdy inny program.
# Koniec z `enable_testing()` i `add_test()`, które wszystko psuły.
add_executable(run_tests 
    tests/run_tests.cpp                  # Nasz główny plik
    tests/test_linear_algebra.cpp        # Testy dla algebry
    tests/test_approximation.cpp      # Tę linię dodasz, jak stworzysz testy
    tests/test_differential_equations.cpp # Testy dla równań różniczkowych
    tests/test_interpolation.cpp         # Testy dla interpolacji
    tests/test_integration.cpp           # Testy dla całkowania
    tests/test_nonlinear_equations.cpp)   # Testy dla równań nieliniowych)
target_link_libraries(run_tests numcpplib)