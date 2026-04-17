#include <cassert>
#include <iostream>
#include <string>

// твои функции
double evaluateRPN(const std::string& rpn);
double evaluatePN(const std::string& expr);

int main() {

    // ===== RPN TESTS =====
    assert(evaluateRPN("2 3 +") == 5);
    assert(evaluateRPN("10 2 -") == 8);
    assert(evaluateRPN("4 5 *") == 20);
    assert(evaluateRPN("20 4 /") == 5);

    assert(evaluateRPN("2 3 + 4 *") == 20);
    assert(evaluateRPN("2.5 2 +") == 4.5);

    // ===== INFIX TESTS =====
    assert(evaluatePN("2 + 3") == 5);
    assert(evaluatePN("10 - 2") == 8);
    assert(evaluatePN("2 + 3 * 4") == 14);
    assert(evaluatePN("(2 + 3) * 4") == 20);

    std::cout << "ALL TESTS PASSED\n";
    return 0;
}