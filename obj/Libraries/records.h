#ifndef RECORDS_H
#define RECORDS_H

#include <vector>
#include <string>
#include <map>

// using namespace std;

struct FanRecord {
    int _id;
    std::string _model;
    std::vector<float> _n_rpm;
    std::vector<float> _pow;
    std::vector<float> _flow;
    std::vector<float> _dp;
    std::string _lw0;
    std::vector<float> _lw;
    float _volt;
    std::vector<float> _cur;
    float _nom_pow;
    float _nom_rpm;
    float _diam;
    std::string _cur_max;
    
    // empty constructor needed for the initialization of the variable
    FanRecord() {}
    // constructor
    FanRecord(int id, std::string model, std::vector<float> n_rpm, std::vector<float> pow, std::vector<float> flow, std::vector<float> dp, std::string lw0, std::vector<float> lw, float volt, std::vector<float> cur, float nom_pow, float nom_rpm, float diam, std::string cur_max) : _id(id), _model(model), _n_rpm(n_rpm), _pow(pow), _nom_rpm(nom_rpm), _flow(flow), _dp(dp), _lw0(lw0), _lw(lw), _volt(volt), _cur(cur), _nom_pow(nom_pow), _diam(diam), _cur_max(cur_max) {}
    // FIXME: for testing purposes -> to be deleted
    FanRecord(int id, std::string model, std::vector<float> n_rpm) : _id(id), _model(model), _n_rpm(n_rpm) {}
};


struct HERecord {
    // empty constructor needed for the initialization of the variable
    HERecord() {}
    // constructor
};
struct AdiabRecord {
    // empty constructor needed for the initialization of the variable
    AdiabRecord() {}
    // constructor
};
struct CoolerRecord { // general Cooler information
    // empty constructor needed for the initialization of the variable
    CoolerRecord() {}
    // constructor
}; 


struct ComprRecord {};
struct EvapRecord {};
struct CondRecord {};
struct ChillerRecord {};

#endif // RECORDS_H