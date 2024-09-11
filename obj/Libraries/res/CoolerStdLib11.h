#ifndef COOLSERSTDLIB11_H
#define COOLSERSTDLIB11_H

#include <vector>
#include <map>
#include <string>
#include "../records.h"

FanRecord f1 {1, "model1", {1.123, 12.123, 123, 31231}};
FanRecord f2 {2, "model2", {1.123, 12.123, 123, 31231}};

std::map<std::string, FanRecord> map_fan_std = {
    {"model1", f1},
    {"model2", f2}
};

#endif // COOLSERSTDLIB11_H