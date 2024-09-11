#include <iostream>
#include <filesystem>
#include <fstream>

#include "cooler_lib.h"
#include "res/headers.h"

#include "../../tls/tls_display.h" // DEBUG: for debugging purposes only

namespace fs = std::filesystem;
// using namespace std;

std::vector<std::string> find_csv_files(const std::string& fodler_path) { // scans a folder and find all CSV files
    std::vector<std::string> csvFiles;

    for (const auto& entry : fs::directory_iterator(fodler_path)) {
        if (entry.is_regular_file() && entry.path().extension() == ".csv") {
            csvFiles.push_back(entry.path().string());
        }
    }

    return csvFiles;
}

std::map<std::string, std::vector<std::string>> read_csv_file(const std::string& filePath) {
    // NOTE: 1. reads the csv file
    //       2. parses each line (row) into vector<string>
    //       3. arranges the rows into columns as  map<string, vector<string>
    //          (first: column header - second> content vector<string>)
    //       4. returns the map (map<string, vector<string>)

    std::map<std::string, std::vector<std::string>> data;
    std::ifstream file(filePath);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filePath << std::endl;
        return data;
    }

    std::vector<std::vector<std::string>> lines;
    // parsing the lines
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) { // Skip empty lines
            lines.push_back(parse_csv_line(line));
        }
    }
    // cout << "Line length: " << lines[0].size() << endl; // DEBUG

    // allocate each column into the map
    for (int i=0; i<lines[0].size(); i++) { // headers row
        data[lines[0][i]] = {};
        // cout << i << " " << lines[0][i] << endl;
    }
    for (int i=1; i<lines.size(); i++) {
        for (int j=0; j<lines[i].size(); j++) {
            data[lines[0][j]].push_back(lines[i][j]);
        }
    }
    
    file.close();
    return data;
}

std::vector<std::string> parse_csv_line(const std::string& line) { // parses a CSV line with `;` as the separator
    std::vector<std::string> parsedLine;
    std::istringstream stream(line);
    std::string cell;

    // Use getline with ';' as a delimiter to split the line
    while (std::getline(stream, cell, ';')) {
        // Remove potential leading/trailing spaces
        cell.erase(0, cell.find_first_not_of(" \t"));
        cell.erase(cell.find_last_not_of(" \t") + 1);
        parsedLine.push_back(cell);
    }
    return parsedLine;
}

CoolerTable::CoolerTable(const std::string& filepath) {
    std::vector<std::string> files = find_csv_files(filepath);
    std::map<std::string, std::vector<std::string>> csv_content;
    // display_vector(files); // DEBUG
    for (int i=0; i<files.size(); i++) {
        std::cout << "Loading file: " << files[i];
        if (files[i].find(FAN_FILENAME) != files[i].npos) {
            csv_content = read_csv_file(files[i]);
            if (files[i].find("FAN") != files[i].npos) _populate_fan_records(csv_content);
            std::cout << " -> Done!" << std::endl;
        }
        else if (files[i].find(HE_FILENAME) != files[i].npos) {}
        else if (files[i].find(ADIAB_FILENAME) != files[i].npos) {}
        else if (files[i].find(COOLER_FILENAME) != files[i].npos) {}
        else std::cout << " -> File " << files[i] << " not belonging to any alowed files." << std::endl;
    }
    for (auto item : _fan_records) std::cout << item.first << std::endl;
}

FanRecord* CoolerTable::get_fan_record(const std::string model)
{
    return &_fan_records[model];
}

HERecord *CoolerTable::get_he_record(const std::string model)
{
    return nullptr;
}

AdiabRecord *CoolerTable::get_adiab_record(const std::string model)
{
    return nullptr;
}

CoolerRecord *CoolerTable::get_cooler_record(const std::string model)
{
    return nullptr;
}

void CoolerTable::_populate_fan_records(std::map<std::string, std::vector<std::string>>& m)
{
    // populates the map fan record database with all the 
    // records retrieved from the CSV file
    
    for (int i=0; i<m["ID"].size(); i++) {
        int id = std::stoi(m["ID"][i]); // to int
        std::string model = m["MODEL"][i];
        std::vector<float> n_rpm = convert_vector<float>(m, "RPM", i, FLOAT);
        std::vector<float> pow = convert_vector<float>(m, "POW", i, FLOAT);
        std::vector<float> flow = convert_vector<float>(m, "", i, FLOAT);
        std::vector<float> dp = convert_vector<float>(m, "", i, FLOAT);
        
        std::string lw0 = m[MAP_FAN["LW0"][0]][0];

        std::vector<float> lw = convert_vector<float>(m, "LW", i, FLOAT);
        float volt = std::stof(m[MAP_FAN["VOLT"][0]][0]);;
        std::vector<float> cur = convert_vector<float>(m, "I", i, FLOAT);
        float nom_pow = std::stof(m[MAP_FAN["NOM POW"][0]][0]);
        float nom_rpm = std::stof(m[MAP_FAN["SPEED NOM"][0]][0]);
        float diam = std::stof(m[MAP_FAN["DIAM"][0]][0]);
        std::string cur_max = m[MAP_FAN["I MAX"][0]][0];
        FanRecord fan(id, model, n_rpm, pow, flow, dp, lw0, lw, volt, cur, nom_pow, nom_rpm, diam, cur_max);    
        _fan_records[model] = fan;
    }
}

void CoolerTable::_populate_he_records(std::map<std::string, std::vector<std::string>> &m)
{
}

void CoolerTable::_populate_adiab_records(std::map<std::string, std::vector<std::string>> &m)
{
}

void CoolerTable::_populate_cooler_records(std::map<std::string, std::vector<std::string>> &m)
{
}

template <typename T>
std::vector<T> convert_vector(std::map<std::string, std::vector<std::string>> &m, 
                              std::string key, 
                              int index, 
                              TYPES to_type) {
    std::vector<T> new_vec;
    T value;   
    std::vector<std::string> keys = MAP_FAN[key];

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
}

void CoolerLibrary::_load_standard_library()
{
    _fan_records = map_fan_std;
    // _he_records = map_he_std;
    // _adiab_records = map_adiab_std;
    // _cooler_records = map_cooler_std;
}

void CoolerLibrary::_merge_tables(const std::vector<CoolerTable> tables)
{
}

CoolerLibrary::CoolerLibrary() {
    _load_standard_library();
}

CoolerLibrary::CoolerLibrary(const std::vector<CoolerTable*> &tables={}, 
                             bool standard_library=true)
{   

    if (standard_library) _load_standard_library();

    // then merge the tables to be included into the library

    for (CoolerTable* table : tables) {
        
                
        }
}