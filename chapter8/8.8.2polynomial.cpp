#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Polynomial {
public:
    Polynomial() : coeffs(1, 0.0) {}

    Polynomial(double c) : coeffs(1, c) {}

    Polynomial(const vector<double>& a) : coeffs(a) {
        if (coeffs.empty()) coeffs.push_back(0.0);
    }

    double evaluate(double x) const {
        double result = 0.0;
        for (int i = (int)coeffs.size() - 1; i >= 0; i--) {
            result = result * x + coeffs[i];
        }
        return result;
    }

    Polynomial add(const Polynomial& other) const {
        size_t n = max(coeffs.size(), other.coeffs.size());
        vector<double> sum(n, 0.0);
        for (size_t i = 0; i < coeffs.size(); i++)       sum[i] += coeffs[i];
        for (size_t i = 0; i < other.coeffs.size(); i++) sum[i] += other.coeffs[i];
        return Polynomial(sum);
    }

private:
    vector<double> coeffs;
};

int main() {
    Polynomial zero;                      
    Polynomial five(5.0);                 
    Polynomial p(vector<double>{1, 2, 3}); 
    Polynomial q(vector<double>{0, -1});  

    cout << "zero(2)  = " << zero.evaluate(2) << "\n";   
    cout << "five(2)  = " << five.evaluate(2) << "\n";   
    cout << "p(2)     = " << p.evaluate(2) << "\n";   
    cout << "(p+q)(2) = " << p.add(q).evaluate(2) << "\n"; 
    return 0;
}