#include <string>
#include "fan_v04_t11.h"

using namespace std;

Fan::Fan(const FanRecord& fan_record) : _fan_record(fan_record) {}

void Fan::_perf_pow()
{
}


void Fan::new_curve()
{
}

void Fan::perf()
{
}

void Fan::_new_points() {}

tuple<double, double> Fan::_inters_new_u(double u_rpm_i, double dp_rpm_i, double kv) {
    return tuple<double, double>();
}

double Fan::_interp_u_rpm(double n0100)
{
    return 0.0;
}

tuple<double, double, double, double> Fan::_new_curve_ec(double n0100)
{
    return tuple<double, double, double, double>();
}

void Fan::_new_curve_tc(double n0100) {
}

void Fan::_perf_u() {
}

void Fan::_perf_dp() {
};