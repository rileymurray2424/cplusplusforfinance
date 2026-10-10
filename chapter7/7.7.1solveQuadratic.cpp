#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int solveQuadratic(double a, double b, double c, double& root1, double& root2)
{
    if (a == 0) {                       
        if (b == 0) return 0;
        root1 = root2 = -c / b;
        return 1;
    }

    double disc = b * b - 4 * a * c;

    if (disc < 0) {
        return 0;                       
    }
    else if (disc == 0) {
        root1 = root2 = -b / (2 * a);
        return 1;
    }
    else {
        double s = sqrt(disc);
        root1 = (-b + s) / (2 * a);
        root2 = (-b - s) / (2 * a);
        return 2;
    }
}


vector<double> solveQuadratic(double a, double b, double c)
{
    vector<double> roots;

    if (a == 0) {
        if (b != 0) roots.push_back(-c / b);
        return roots;
    }

    double disc = b * b - 4 * a * c;

    if (disc == 0) {
        roots.push_back(-b / (2 * a));
    }
    else if (disc > 0) {
        double s = sqrt(disc);
        roots.push_back((-b + s) / (2 * a));
        roots.push_back((-b - s) / (2 * a));
    }
    return roots;
}

int main()
{
    double a, b, c;
    cout << "Enter a, b, c: ";
    cin >> a >> b >> c;


    double r1, r2;
    int n = solveQuadratic(a, b, c, r1, r2);
    cout << "Reference version: " << n << " root(s)";
    if (n >= 1) cout << ": " << r1;
    if (n == 2) cout << ", " << r2;
    cout << endl;

    vector<double> roots = solveQuadratic(a, b, c);
    cout << "Vector version: " << roots.size() << " root(s)";
    for (size_t i = 0; i < roots.size(); i++)
        cout << (i == 0 ? ": " : ", ") << roots[i];
    cout << endl;

    return 0;
}
