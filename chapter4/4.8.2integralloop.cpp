#include <iostream>
#include <cmath>

double RectangleRule(double a, double b, int n)
{
    double h = (b - a) / n;
    double sum = 0.0;

    for (int i = 0; i < n; i++)
    {
        sum += sin(a + i*h + 0.5*h);
    }

    return h * sum;
}

int main()
{
    double a = 0.0;
    double b = M_PI;   // exact answer here is 2

    for (int n = 10; n <= 100000; n *= 10)
    {
        std::cout << "n = " << n
                  << ", approx = " << RectangleRule(a, b, n) << "\n";
    }

    return 0;
}