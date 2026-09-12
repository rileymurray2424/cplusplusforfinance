#include <iostream>
#include <cmath>

const double ROOT_2PI = sqrt(2.0 * acos(-1.0));

double normcdf(double x) {
    if (x < 0.0) return 1.0 - normcdf(-x);

    double k = 1.0 / (1.0 + 0.2316419 * x);

    double poly = k * ( 0.319381530
                + k * (-0.356563782
                + k * ( 1.781477937
                + k * (-1.821255978
                + k *   1.330274429))));

    return 1.0 - exp(-x * x / 2.0) * poly / ROOT_2PI;
                }
int main() {
    std::cout << normcdf(0.0) << "\n";
    std::cout << normcdf(1.96) << "\n";
    std::cout << normcdf(-1.0) << "\n";
    return 0;

}

// N is a bad name for a function because N is so commonly used.