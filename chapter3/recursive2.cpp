#include <iostream>

void printRange(int a, int b) {
    if (a > b) return;
    std::cout << a << " ";
    printRange(a + 1, b);
}

int main() {
    printRange(3, 9);
    std::cout << "\n";
    printRange(5, 5);
    std::cout << "\n";
    printRange(9, 3);
    std::cout << "\n";
    return 0;
}