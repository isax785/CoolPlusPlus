#ifndef TLS_POLYNOMIAL_H
#define TLS_POLYNOMIAL_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include <cmath>

/*
Least square regression of a polynomial.

The points to be interpolated are contained into a vector in
the form {{x1, y1}, {x2, y2}, ..., {xn, yn}}
*/

void func(int x) { std::cout << x << std::endl; };

float calculate_x_sum(const std::vector<std::vector<float>>& point_pairs, int n) {
        // SUM(x_i^n)
        float sum = 0;
        for (int i=0; i<point_pairs.size(); i++) sum += pow(point_pairs[i][0], n);
        return sum;
    };


struct PolyFunctions {
    static float calculate_x_sum(const std::vector<std::vector<float>>& point_pairs, int n) {
        // SUM(x_i^n)
        float sum = 0;
        for (int i=0; i<point_pairs.size(); i++) sum += pow(point_pairs[i][0], n);
        return sum;
    };

    static float calculate_x_y_sum(const std::vector<std::vector<float>>& point_pairs, int n, int m) {
        // SUM(x_i^n * y_i^n)
        float sum = 0;
        for (int i=0; i<point_pairs.size(); i++) sum += pow(point_pairs[i][0], n) * pow(point_pairs[i][1], m);
        return sum;
    };

    static float calculate_y_sum(const std::vector<std::vector<float>>& point_pairs) {
        // SUM(y_i)
        float sum = 0;
        for (int i=0; i<point_pairs.size(); i++) sum += point_pairs[i][1];
        return sum;
    };

    static float calculate_ymean(const std::vector<std::vector<float>>& point_pairs) {
        float y_mean = calculate_y_sum(point_pairs) / point_pairs.size();
        return y_mean;
    };
};

float determinant2x2(std::vector<float>& m) {
    // matrix into vector form: 
    // {a1, b1, 
    //  a2, b2}
    // det(A) = a1b2 - a2b1
    return m[0]*m[3] - m[2]*m[1]; 
};

float determinant3x3(std::vector<float>& m) {
    // matrix into vector form: 
    // {a1, b1, c1
    //  a2, b2, c2,
    //  a3, b3, c3}
    // det(A) = a1b2c3 + a3b1c2 + c1a2b3 - a3b2c1 - b3c2a1 - c3a2b1
    return m[0]*m[4]*m[8] + m[6]*m[1]*m[5] + m[2]*m[3]*m[7] -
           m[6]*m[4]*m[2] - m[7]*m[5]*m[2] - m[8]*m[3]*m[1];
};

class Polynomial {
    public:
        virtual void _calculate_coefficients()=0;
};

class QuadraticPolynomial {
    private:
        int _nr_points;
        std::vector<std::vector<float>> _point_pairs;
        float _s40, _s30, _s20, _s21, _s10, _s11, _s00, _s01;
        float _d, _da, _db, _dc;   // determinants
        float a, b, c;    // coefficients
        float _y_mean;
        float _s_sqr=0;   // total sum of squares
        float _s_res=0;   // residual sum of squares
        float _r2;        // r-square
        void _set_points(std::vector<std::vector<float>> point_pairs) {
            _point_pairs = point_pairs;
            _nr_points = point_pairs.size();
            if (_nr_points < 3) {
                throw std::invalid_argument("Provide at least 3 points.");
            }
        };
        float _calculate_x_sum(int n) {
            // SUM(x_i^n)
            float sum = 0;
            for (int i=0; i<_nr_points; i++) sum += pow(_point_pairs[i][0], n);
            return sum;
        };
        float _calculate_x_y_sum(int n, int m) {
            // SUM(x_i^n * y_i^n)
            float sum = 0;
            for (int i=0; i<_nr_points; i++) sum += pow(_point_pairs[i][0], n) * pow(_point_pairs[i][1], m);
            return sum;
        }
        float _calculate_y_sum() {
            // SUM(y_i)
            float sum = 0;
            for (int i=0; i<_nr_points; i++) sum += _point_pairs[i][1];
            return sum;
        }
        void _calculate_ymean() {
            _y_mean = _s01 / _nr_points;
        };
        void _calculate_coefficients() {
            _s40 = calculate_x_sum(_point_pairs, 4);
            _s30 = _calculate_x_sum(3);
            _s20 = _calculate_x_sum(2);
            _s21 = _calculate_x_y_sum(2, 1);
            _s10 = _calculate_x_sum(1);
            _s11 = _calculate_x_y_sum(1, 1);
            _s00 = _calculate_x_sum(0);
            _s01 = _calculate_y_sum();
            // Determinants: Cramer's law
            _d = _s40 * (_s20 * _s00 - _s10 * _s10) -
                 _s30 * (_s30 * _s00 - _s10 * _s20) +
                 _s20 * (_s30 * _s10 - _s20 * _s20);
            _da = _s21 * (_s20 * _s00 - _s10 * _s10) -
                  _s11 * (_s30 * _s00 - _s10 * _s20) +
                  _s01 * (_s30 * _s10 - _s20 * _s20);
            _db = _s40 * (_s11 * _s00 - _s01 * _s10) -
                  _s30 * (_s21 * _s00 - _s01 * _s20) +
                  _s20 * (_s21 * _s10 - _s11 * _s20);
            _dc = _s40 * (_s20 * _s01 - _s10 * _s11) -
                  _s30 * (_s30 * _s01 - _s10 * _s21) +
                  _s20 * (_s30 * _s11 - _s20 * _s21);
            // ciefficients
            a = _da / _d;
            b = _db / _d;
            c = _dc / _d;
        };
        void _calculate_rsquare() {
            _calculate_ymean();
            for (int i=0; i<_nr_points; i++) _s_sqr += pow(_point_pairs[i][1] - _y_mean, 2);
            for (int i=0; i<_nr_points; i++) _s_res += pow(_point_pairs[i][1] - polyval(_point_pairs[i][0]), 2);
            _r2 = 1 - (_s_sqr / _s_res);
        };
    public:
        QuadraticPolynomial(std::vector<std::vector<float>> point_pairs) {
            _set_points(point_pairs);
            _calculate_coefficients();
            _calculate_rsquare();
        };
        float polyval(float x) {
            return a * pow(x, 2) + b * x + c;
        };
        std::vector<float> get_coefficients() { return {a, b, c}; };
        float get_rsquare() { return _r2; }
        void display_stats() {
            std::cout << "R2: " << _r2 << std::endl;
            std::cout << "a: " << a << std::endl;
            std::cout << "b: " << b << std::endl;
            std::cout << "c: " << c << std::endl;
        };
};

class CubicPolynomial {
    public: 
        CubicPolynomial(std::vector<std::vector<float>> point_pairs) { };
};

#endif // TLS_POLYNOMIAL_H