#ifndef TLS_CSV_UTILS_H
#define TLS_CSV_UTILS_H

#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <map>
#include <string>

namespace fs = std::filesystem;

enum TYPES {
    STR,
    INT,
    FLOAT,
};

extern std::vector<std::string> parse_csv_line(const std::string& line); // parses a CSV line with `;` separator

std::vector<std::string> find_csv_files(const std::string& folder_path); // scans a folder and find all CSV files

void build_csv_data_map(const std::vector<std::vector<std::string>>& lines_vector, std::map<std::string, std::vector<std::string>> &data_map);

std::map<std::string, std::vector<std::string>> read_csv_file(const std::string& filePath);

template <typename T>
std::vector<T> convert_vector(std::map<std::string, std::vector<std::string>> &m, 
                              std::string key, 
                              int index, 
                              TYPES to_type,
                              std::vector<std::string> &keys) {
    std::vector<T> new_vec;
    T value;   
    // std::vector<std::string> keys = MAP_FAN[key];

    switch (to_type) {
        case STR:
            {
                if constexpr (std::is_same<T, std::string>::value) {
                    for (int i=0; i<keys.size(); i++) {
                            value = std::stoi(m[keys[i]][index]);
                            new_vec.push_back(value);
                        }
                }
                break;
            }
        case INT:
            {
                if constexpr (std::is_same<T, int>::value) {
                    for (int i=0; i<keys.size(); i++) {
                        value = std::stoi(m[keys[i]][index]);
                        new_vec.push_back(value);
                    }
                }
                break;
            }
        case FLOAT:
            {   
                if constexpr (std::is_same<T, float>::value) {
                    for (int i=0; i<keys.size(); i++) {
                        value = std::stof(m[keys[i]][index]);
                        new_vec.push_back(value);
                    }
                }
                break;
            }
        default:
            break;
    }
    return new_vec;
};

#endif // TLS_CSV_UTILS_H