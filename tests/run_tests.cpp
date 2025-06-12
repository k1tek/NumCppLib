// tests/run_tests.cpp

#include <iostream>

// === Deklaracje testow dla: linear_algebra ===
void TestGaussEliminationSolvable();
void TestGaussEliminationThrowsOnInvalidInput();
void TestLuDecompositionSolvable();
void TestLuDecompositionThrowsOnInvalidInput();

// === Deklaracje testow dla: interpolation ===
void TestLagrangeInterpolationCorrectness();
void TestLagrangeInterpolationThrowsOnInvalidInput();
void TestNewtonInterpolationCorrectness();
void TestNewtonInterpolationThrowsOnInvalidInput();

// === Deklaracje testow dla: integration ===
void TestRectangleRuleCorrectness();
void TestRectangleRuleThrowsOnInvalidInput();
void TestTrapezoidalRuleCorrectness();
void TestTrapezoidalRuleThrowsOnInvalidInput();
void TestSimpsonRuleCorrectness();
void TestSimpsonRuleThrowsOnInvalidInput();
void TestGaussLegendreCorrectness();
void TestGaussLegendreThrowsOnUnsupportedNodes();
void TestSegmentedGaussLegendreCorrectness();
void TestSegmentedGaussLegendreThrowsOnInvalidInput();

// === Deklaracje testow dla: differential_equations ===
void TestEulerMethodCorrectness();
void TestEulerMethodThrowsOnInvalidInput();
void TestHeunMethodCorrectness();
void TestHeunMethodThrowsOnInvalidInput();
void TestMidpointMethodCorrectness();
void TestMidpointMethodThrowsOnInvalidInput();
void TestRungeKutta4Correctness();
void TestRungeKutta4ThrowsOnInvalidInput();

// === Deklaracje testow dla: nonlinear_equations ===
void TestBisectionMethodFindsRoot();
void TestBisectionMethodReturnsNullopt();
void TestSecantMethodFindsRoot();
void TestSecantMethodThrowsOnInvalidInput();
void TestNewtonMethodAnalyticalFindsRoot();
void TestNewtonMethodNumericalFindsRoot();
void TestRegulaFalsiMethodFindsRoot();
void TestRegulaFalsiMethodReturnsNullopt();

// === Deklaracje testow dla: approximation ===
void TestApproximateValueAtPointCorrectness();
void TestApproximateValueAtPointThrowsOnInvalidInput();

int main() {
    std::cout << "=== URUCHAMIANIE TESTOW JEDNOSTKOKWYCH BIBLIOTEKI NumCppLib ===\n" << std::endl;

    std::cout << "--- Modul: Linear Algebra ---" << std::endl;
    TestGaussEliminationSolvable();
    TestGaussEliminationThrowsOnInvalidInput();
    TestLuDecompositionSolvable();
    TestLuDecompositionThrowsOnInvalidInput();

    std::cout << "\n--- Modul: Interpolation ---" << std::endl;
    TestLagrangeInterpolationCorrectness();
    TestLagrangeInterpolationThrowsOnInvalidInput();
    TestNewtonInterpolationCorrectness();
    TestNewtonInterpolationThrowsOnInvalidInput();

    std::cout << "\n--- Modul: Integration ---" << std::endl;
    TestRectangleRuleCorrectness();
    TestRectangleRuleThrowsOnInvalidInput();
    TestTrapezoidalRuleCorrectness();
    TestTrapezoidalRuleThrowsOnInvalidInput();
    TestSimpsonRuleCorrectness();
    TestSimpsonRuleThrowsOnInvalidInput();
    TestGaussLegendreCorrectness();
    TestGaussLegendreThrowsOnUnsupportedNodes();
    TestSegmentedGaussLegendreCorrectness();
    TestSegmentedGaussLegendreThrowsOnInvalidInput(); 
    
    std::cout << "\n--- Modul: Differential Equations ---" << std::endl;
    TestEulerMethodCorrectness();
    TestEulerMethodThrowsOnInvalidInput();
    TestHeunMethodCorrectness();
    TestHeunMethodThrowsOnInvalidInput();
    TestMidpointMethodCorrectness();
    TestMidpointMethodThrowsOnInvalidInput();
    TestRungeKutta4Correctness();
    TestRungeKutta4ThrowsOnInvalidInput();

    std::cout << "\n--- Modul: Nonlinear Equations ---" << std::endl;
    TestBisectionMethodFindsRoot();
    TestBisectionMethodReturnsNullopt();
    TestSecantMethodFindsRoot();
    TestSecantMethodThrowsOnInvalidInput();
    TestNewtonMethodAnalyticalFindsRoot();
    TestNewtonMethodNumericalFindsRoot();
    TestRegulaFalsiMethodFindsRoot();
    TestRegulaFalsiMethodReturnsNullopt();
    
    std::cout << "\n--- Modul: Approximation ---" << std::endl;
    TestApproximateValueAtPointCorrectness();
    TestApproximateValueAtPointThrowsOnInvalidInput();

    std::cout << "\n\n=== WSZYSTKIE TESTY ZAKONCZONE SUKCESEM! ===\n" << std::endl;

    return 0;
}