#include <tuple>
#include <map>
#include <vector>
#include <string>
#include "../Libraries/records.h"

class Fan {
    private:
        FanRecord const _fan_record;
        void _new_points();
        tuple<double, double> _inters_new_u(double, double, double);
        double _interp_u_rpm(double n0100);
        tuple<double, double, double, double> _new_curve_ec(double n0100);
        void _new_curve_tc(double n0100);
        void _perf_u();
        void _perf_dp();
        void _perf_pow();
    public:
        Fan(const FanRecord & fan_record);
        void new_curve();
        void perf(); // input:settings ??
};