#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
using namespace std;

mt19937 rng(42);
double randn() {
    static normal_distribution<double> d(0.0, 1.0);
    return d(rng);
}
double normcdf(double x) { return 0.5 * erfc(-x / sqrt(2.0)); }

class BlackScholesModel {
public:
    double stockPrice, volatility, riskFreeRate, date;

    vector<double> generateRiskNeutralPricePath(double toDate, int nSteps) const {
        vector<double> path(nSteps);
        double dt = (toDate - date) / nSteps;
        double drift = (riskFreeRate - 0.5 * volatility * volatility) * dt;
        double s = stockPrice;
        for (int i = 0; i < nSteps; i++) {
            s *= exp(drift + volatility * sqrt(dt) * randn());
            path[i] = s;
        }
        return path;
    }
};

class CallOption {
public:
    double strike, maturity;
    double payoff(double stockAtMaturity) const {
        return max(stockAtMaturity - strike, 0.0);
    }
};

class PutOption {
public:
    double strike, maturity;
    double payoff(double stockAtMaturity) const {
        return max(strike - stockAtMaturity, 0.0);
    }
};

class MonteCarloPricer {
public:
    int nScenarios = 100000;
    int nSteps = 10;

    double price(const CallOption& option, const BlackScholesModel& model) const {
        double total = 0.0;
        for (int i = 0; i < nScenarios; i++) {
            vector<double> path = model.generateRiskNeutralPricePath(option.maturity, nSteps);
            total += option.payoff(path.back());
        }
        double mean = total / nScenarios;
        return exp(-model.riskFreeRate * (option.maturity - model.date)) * mean;
    }

    double price(const PutOption& option, const BlackScholesModel& model) const {
        double total = 0.0;
        for (int i = 0; i < nScenarios; i++) {
            vector<double> path = model.generateRiskNeutralPricePath(option.maturity, nSteps);
            total += option.payoff(path.back());
        }
        double mean = total / nScenarios;
        return exp(-model.riskFreeRate * (option.maturity - model.date)) * mean;
    }
};

int main() {
    BlackScholesModel m;
    m.stockPrice = 100; m.volatility = 0.2; m.riskFreeRate = 0.05; m.date = 0;

    PutOption put;
    put.strike = 100; put.maturity = 1;

    MonteCarloPricer pricer;
    double mc = pricer.price(put, m);

    double S = m.stockPrice, K = put.strike, r = m.riskFreeRate, s = m.volatility;
    double T = put.maturity - m.date;
    double d1 = (log(S / K) + (r + 0.5 * s * s) * T) / (s * sqrt(T));
    double d2 = d1 - s * sqrt(T);
    double bs = K * exp(-r * T) * normcdf(-d2) - S * normcdf(-d1);

    cout << "Monte Carlo put price:   " << mc << "\n";
    cout << "Black-Scholes put price: " << bs << "\n";
    return 0;
}