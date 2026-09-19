#include <cmath>
#include <iostream>
#include <stdexcept>

double normcdf(double z) { return 0.5 * erfc(-z / sqrt(2.0)); }

double norminv(double x)
{
    if (!(x >= 0.0 && x <= 1.0))
        throw std::invalid_argument("norminv: x outside [0,1]");

    double lo = -40.0, hi = 40.0;
    for (int i = 0; i < 200; i++)
    {
        double mid = 0.5 * (lo + hi);
        if (normcdf(mid) < x) lo = mid; else hi = mid;
    }
    return 0.5 * (lo + hi);
}

int main()
{
    std::cout << norminv(0.975) << " " << norminv(0.5) << " " << norminv(0.025) << "\n";
    try { norminv(1.5); }
    catch (const std::invalid_argument& e) { std::cout << "caught: " << e.what() << "\n"; }
    return 0;
}
// looks like magic numbers here but it's all explainable.