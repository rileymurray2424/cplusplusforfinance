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

double blackScholesCallPrice(double K, double T, double S,
double sigma, double r) {
    double sigmaRootT = sigma * sqrt(T);
    double d1 = (log(S / K) + (r + 0.5 * sigma * sigma )* T) / sigmaRootT;
    double d2 = d1 - sigmaRootT;
    return S * normcdf(d1) - K * exp(-r * T) * normcdf(d2);
}

int main() {
    std::cout << blackScholesCallPrice(100, 1.0, 100, 0.20, 0.05) << "\n";
    return 0;
}