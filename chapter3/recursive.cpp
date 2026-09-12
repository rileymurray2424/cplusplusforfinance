#include <iostream>

int sumTo(int n) {
    if (n <= 0) return 0;
    return n + sumTo(n - 1);
}

int main() {
    std::cout << sumTo(4) << "\n";
    std::cout << sumTo(100) << "\n";
    return 0;
}