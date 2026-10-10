#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include <stdexcept>
using namespace std;

double mean(const vector<double>& v)
{
    if (v.empty()) {
        throw invalid_argument("mean: vector is empty");
    }
    double sum = 0.0;
    for (double x : v) {
        sum += x;
    }
    return sum / v.size();
}

bool approxEqual(double x, double y, double tol = 1e-9)
{
    return fabs(x - y) < tol;
}

void testMean()
{
    
    assert(approxEqual(mean({1, 2, 3, 4, 5}), 3.0));

    
    assert(approxEqual(mean({7.5}), 7.5));

    
    assert(approxEqual(mean({-2, -1, 0, 1, 2}), 0.0));

    
    assert(approxEqual(mean({1, 2}), 1.5));

    
    bool threw = false;
    try {
        mean({});
    }
    catch (const invalid_argument&) {
        threw = true;
    }
    assert(threw);

    cout << "All tests passed" << endl;
}

int main()
{
    testMean();
    return 0;
}
