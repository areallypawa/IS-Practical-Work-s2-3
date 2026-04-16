//#include <cassert>
//#include <iostream>
//#include <stdexcept>
//
//double evalRPNWrapper(const std::string& s);
//double evalPNWrapper(const std::string& s);
//
//int main() {
//    // RPN тесты
//    assert(evalRPNWrapper("2 3 +") == 5);
//    assert(evalRPNWrapper("10 5 /") == 2);
//
//    // PN тесты
//    assert(evalPNWrapper("+ 2 3") == 5);
//    assert(evalPNWrapper("/ 10 5") == 2);
//
//    // Невалидный ввод
//    try {
//        evalRPNWrapper("2 +");
//        assert(false); // не должно сюда дойти
//    }
//    catch (...) {}
//
//    std::cout << "All tests passed!\n";
//}