#include <iostream>

int fibonacci(int n) {
    if (n <= 1) return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    for (int n = 0; n <= 10; n++) {
        std::cout << "x" << n << " = " << fibonacci(n) << "\n";
    }
    return 0;
}