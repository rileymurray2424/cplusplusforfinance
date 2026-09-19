#include <iostream>
#include <stdexcept>

long factorialWhile(int n)
{
    if (n < 0) throw std::invalid_argument("factorial: n must be non-negative");

    long result = 1;
    int i = 1;
    while (i <= n)
    {
        result *= i;
        i++;
    }
    return result;
}

long factorialFor(int n)
{
    if (n < 0) throw std::invalid_argument("factorial: n must be non-negative");

    long result = 1;
    for (int i = 1; i <= n; i++)
    {
        result *= i;
    }
    return result;
}

long factorialDoWhile(int n)
{
    if (n < 0) throw std::invalid_argument("factorial: n must be non-negative");

    long result = 1;
    int i = 1;
    do
    {
        result *= i;
        i++;
    } while (i <= n);
    return result;
}

int main()
{
    for (int n = 0; n <= 10; n++)
    {
        std::cout << n << "! = "
                  << factorialWhile(n) << " "
                  << factorialFor(n) << " "
                  << factorialDoWhile(n) << "\n";
    }
    return 0;
}