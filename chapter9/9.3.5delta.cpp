#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
using namespace std;

mt19937 rng(42);
normal_distribution<double> Z(0.0, 1.0);
double normcdf(double x) { return 0.5 * erfc(-x / sqrt(2.0)); }

struct BlackScholesModel {
    double stockPrice, volatility, riskFreeRate;

    double terminalPrice(double S0, const vector<double>& eps, double T) const {
        double dt = T / eps.size(), S = S0;
        for (double e : eps)
            S *= exp((riskFreeRate - 0.5 * volatility * volatility) * dt
                     + volatility * sqrt(dt) * e);
        return S;
    }
};

double mcCallDelta(const BlackScholesModel& m, double K, double T, int N, int nSteps) {
    double h = m.stockPrice * 1e-6, up = 0, down = 0;
    vector<double> eps(nSteps);
    for (int i = 0; i < N; i++) {
        for (double& e : eps) e = Z(rng);                                 
        up   += max(m.terminalPrice(m.stockPrice + h, eps, T) - K, 0.0); 
        down += max(m.terminalPrice(m.stockPrice - h, eps, T) - K, 0.0);
    }
    return exp(-m.riskFreeRate * T) * (up - down) / N / (2 * h);
}

int main() {
    BlackScholesModel m{100, 0.2, 0.05};
    double K = 100, T = 1;

    double mc = mcCallDelta(m, K, T, 100000, 10);

   
    double d1 = (log(m.stockPrice / K) + (m.riskFreeRate + 0.5 * m.volatility * m.volatility) * T)
                / (m.volatility * sqrt(T));
    double bs = normcdf(d1);

    cout << "MC delta: " << mc << "\nBS delta: " << bs << "\n";
    cout << (fabs(mc - bs) < 0.01 ? "PASS\n" : "FAIL\n");
}