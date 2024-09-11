#ifndef HEADERS_H
#define HEADERS_H

#include <string>
#include <vector>
#include <map>

std::map<std::string, std::vector<std::string>> MAP_FAN ={
        {"ID", {"ID"}},
        {"MODEL", {"MODEL"}},
        {"RPM", {"RPM_1", "RPM_5", "RPM_9", "RPM_13"}},
        {"POW", {"POW_1", "POW_2", "POW_3", "POW_4", "POW_5", "POW_6", "POW_7", "POW_8", "POW_9", "POW_10", "POW_11", "POW_12", "POW_13", "POW_14", "POW_15", "POW_16"}},
        {"PORT", {"PORT_1", "PORT_2", "PORT_3", "PORT_4", "PORT_5", "PORT_6", "PORT_7", "PORT_8", "PORT_9", "PORT_10", "PORT_11", "PORT_12", "PORT_13", "PORT_14", "PORT_15", "PORT_16"}},
        {"DP", {"DP_1", "DP_2", "DP_3", "DP_4", "DP_5", "DP_6", "DP_7", "DP_8", "DP_9", "DP_10", "DP_11", "DP_12", "DP_13", "DP_14", "DP_15", "DP_16"}},
        {"LW0", {"LW"}},
        {"LW", {"LW_1", "LW_2", "LW_3", "LW_4", "LW_5", "LW_6", "LW_7", "LW_8", "LW_9", "LW_10", "LW_11", "LW_12", "LW_13", "LW_14", "LW_15", "LW_16"}},
        {"VOLT", {"VOLT"}},
        {"I", {"I_1", "I_2", "I_3", "I_4", "I_5", "I_6", "I_7", "I_8", "I_9", "I_10", "I_11", "I_12", "I_13", "I_14", "I_15", "I_16"}},
        {"NOM POW", {"NOMINAL POWER INPUT"}},
        {"DIAM", {"FAN DIAMETER"}},
        {"I MAX", {"MOTOR MAX CURRENT ABSORP"}},
        {"ERP", {"ERP"}},
        {"PROT RATE", {"ELECTRICAL PROTECTION RATE"}},
        {"SPEED NOM", {"FAN SPEED NOMINAL"}},
        {"SPEED PL", {"FAN SPEED PL"}},
        {"MOTOR COUPLING", {"FAN MOTOR COUPLING"}},
        {"MOTOR TYPE", {"MOTOR TYPE"}},
        {"UL", {"UL"}},
        {"BLADES MAT", {"BLADES / HUB MATERIAL"}},
        {"MOTOR MAT", {"MOTOR MATERIAL"}},
        {"GRID MAT", {"GRID MATERIAL"}},
        {"BLADES COAT", {"BLADES / HUB COATINGS"}},
        {"MOTOR COAT", {"MOTOR COATINGS"}},
};

#endif // HEADERS_H