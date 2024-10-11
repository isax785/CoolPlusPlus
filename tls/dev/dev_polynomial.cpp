#include <iostream>
#include <chrono>
#include "../tls_display.h"
#include "../tls_polynomial.h"

using namespace std;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

int main() {
    // -------- Checking Error (low nr points) --------
    // vector<vector<float>> v_err = {{1, 2}, {2, 3}};
    // QuadraticPolynomial poly_err = QuadraticPolynomial(v_err);  // error

    // vector<vector<float>> v = {{-1, 1}, {0, 0}, {1, 1}};
    // -------- Testing --------
    vector<vector<float>> v = {{3, 9}, {1, 1}, {2, 4}};
    auto t1 = high_resolution_clock::now();

    QuadraticPolynomial poly = QuadraticPolynomial(v);

    auto t2 = high_resolution_clock::now();
    duration<double, std::milli> ms_double = t2 - t1;
    cout << "Instatiation time: " << ms_double.count() << "ms\n";

    poly.display_stats();
    cout << poly.polyval(6) << endl;
    cout << poly.polyval(-6) << endl;

    vector<vector<float>> v2 = {{3, 10}, {1, 2}, {2, 5}};
    QuadraticPolynomial poly2 = QuadraticPolynomial(v2);
    cout << poly2.polyval(6) << endl;
}