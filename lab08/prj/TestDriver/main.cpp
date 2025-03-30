#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include "ModulesAvramenko.h"

using namespace std;

string doubleToString(double value, int precision = 3) {
    ostringstream oss;
    oss << fixed << setprecision(precision) << value;
    return oss.str();
}

void test_s_calculation() {

    double x[10] = {1, 0.5, 2.0, 3.0, -1.0, 0, 10, 0, -3, 100};
    double y[10] = {2.0, -1.0, -2.0, 2.0, -1.0, 0, -5, 3, -2, 1};
    double z[10] = {3.0, 4.0, 5.0, -4.0, -1.0, 0.0, 2.0, 2.0, 4.0, 1.0};
    double expected_results[10] = {96.595, -2.8305, NAN, 96.1116, -4.19002, NAN, -9375.385, 729, -96.1116, -2.08891};


    for (short i = 0; i < 10; i++) {
        double result = s_calculation(x[i], y[i], z[i]);
        string resultStr = doubleToString(result);
        string expectedStr = doubleToString(expected_results[i]);
        bool passed = false;

        // Для NaN використовується isNaN, оскільки NaN != NaN
        if (std::isnan(result) && std::isnan(expected_results[i])) {
            passed = true;
        } else if (resultStr == expectedStr) {
            passed = true;
        }

        cout << "Test case #" << i+1 << ": s_calculation("
             << x[i] << ", " << y[i] << ", " << z[i] << ") = "
             << resultStr << " == " << expectedStr
             << " --> " << (passed ? "passed" : "failed") << endl;
    }
}

int main()
{
    test_s_calculation();
    return 0;
}
