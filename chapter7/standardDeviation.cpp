#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include <stdexcept>
using namespace std;

double mean(const vector<double>& v)
{
    if (v.empty()) {
        throw invalid_argument("mean vector is empty");
    }
    double sum = 0.0;
    for (double x : v) {
        sum += x;
    }
    return sum / v.size();
}


double standardDeviation(const vector<double>& v, bool population = false)
{
    size_t n = v.size();
    if (population && n < 1) {
        throw invalid_argument("need at least 1 value");
    }
    if (!population && n < 2) {
        throw invalid_argument("sample needs at least 2 values");
    }

    double m = mean(v);
    double sumSq = 0.0;
    for (double x : v) {
        sumSq += (x - m) * (x - m);
    }

    double denom = population ? n : n - 1;
    return sqrt(sumSq / denom);
}

bool approxEqual(double x, double y, double tol = 1e-9)
{
    return fabs(x - y) < tol;
}

void testStandardDeviation()
{
    
    vector<double> data = {2, 4, 4, 4, 5, 5, 7, 9};
    assert(approxEqual(standardDeviation(data, true), 2.0));            
    assert(approxEqual(standardDeviation(data, false), sqrt(32.0 / 7))); 

    
    assert(approxEqual(standardDeviation(data), sqrt(32.0 / 7)));

    
    assert(approxEqual(standardDeviation({3, 3, 3, 3}), 0.0));

    
    assert(approxEqual(standardDeviation({5}, true), 0.0));
    bool threw = false;
    try { standardDeviation({5}); }
    catch (const invalid_argument&) { threw = true; }
    assert(threw);

    
    threw = false;
    try { standardDeviation({}, true); }
    catch (const invalid_argument&) { threw = true; }
    assert(threw);

    cout << "All tests passed" << endl;
}

int main()
{
    testStandardDeviation();
    return 0;
}