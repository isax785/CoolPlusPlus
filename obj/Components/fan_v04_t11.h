#include <tuple>
#include <map>
#include <vector>
#include <string>
#include "../Libraries/records.h"

class Fan {
    private:
        FanRecord* _fan_record;
        void _new_points();
        std::tuple<double, double> _inters_new_u(double, double, double);
        double _interp_u_rpm(double n0100);
        std::tuple<double, double, double, double> _new_curve_ec(double n0100);
        void _new_curve_tc(double n0100);
        void _perf_u();
        void _perf_dp();
        void _perf_pow();
    public:
        Fan(FanRecord* fan_record);
        void new_curve();
        void perf(); // input:settings ??
};