#include <iostream>
#include <cmath>

double compoundInterest(double P, double i, int n) {
    return P * pow(1 + 0.01*i, n) - P;
}

int main() {
    std::cout << compoundInterest(1000, 5, 10) << "\n";
    return 0;
}