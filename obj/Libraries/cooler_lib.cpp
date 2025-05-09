#include <iostream>
#include "cooler_lib.h"

// ===========================================================================
//                                  Table
// ===========================================================================

CoolerTable::CoolerTable() {
    // TODO: complete import of all the components
    std::vector<std::vector<std::string>> lines_fan_parsed;
    for (int i=0; i<FAN_STD_CSV_LINES.size(); i++) {
        lines_fan_parsed.push_back(parse_csv_line(FAN_STD_CSV_LINES[i]));
    }

    std::map<std::string, std::vector<std::string>> fan_std_map;
    build_csv_data_map(lines_fan_parsed, fan_std_map);
    // display_map_content(fan_std_map); // DEBUG
    _populate_fan_records(fan_std_map);
}

CoolerTable::CoolerTable(const std::string& filepath) {
    // import the csv files contained into a directory
    // the filenames contain the _FILENAME string
    std::vector<std::string> files = find_csv_files(filepath);
    std::map<std::string, std::vector<std::string>> csv_content;
    // display_vector(files); // DEBUG
    for (int i=0; i<files.size(); i++) {
        std::cout << "Loading file: " << files[i];
        if (files[i].find(FAN_FILENAME) != files[i].npos && !_fan_csv_imported) {
            csv_content = read_csv_file(files[i]);
            if (files[i].find("FAN") != files[i].npos) _populate_fan_records(csv_content);
            _fan_csv_imported = true;
            std::cout << " -> FAN Done!" << std::endl;
        }
        else if (files[i].find(HE_FILENAME) != files[i].npos) {
            _he_csv_imported = true;
            std::cout << " -> HE Done!" << std::endl;
        }
        else if (files[i].find(ADIAB_FILENAME) != files[i].npos) {
            _adiab_csv_imported = true;
            std::cout << " -> ADIAB Done!" << std::endl;
        }
        else if (files[i].find(COOLER_FILENAME) != files[i].npos) {
            _cooler_csv_imported = true;
            std::cout << " -> COOLER Done!" << std::endl;
        }
        else std::cout << " -> File " << files[i] << " cannot be imported." << std::endl;
    }
    // for (auto item : _fan_records) std::cout << item.first << std::endl; // DEBUG
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

void CoolerTable::get_fan_record_list()
{
    std::cout << "Fan Models:" << std::endl;
    
    for (auto item : _fan_records) {
        std::cout << item.first << std::endl;
    }
}

void CoolerTable::_populate_fan_records(std::map<std::string, std::vector<std::string>>& m)
{
    // populates the map fan record database with all the 
    // records retrieved from the CSV file
    
    for (int i=0; i<m["ID"].size(); i++) {
        int id = std::stoi(m["ID"][i]); // to int
        std::string model = m["MODEL"][i];

        std::vector<float> n_rpm = convert_vector<float>(m, "RPM", i, FLOAT, MAP_FAN["RPM"]);
        std::vector<float> pow = convert_vector<float>(m, "POW", i, FLOAT, MAP_FAN["POW"]);
        std::vector<float> flow = convert_vector<float>(m, "PORT", i, FLOAT, MAP_FAN["PORT"]);
        std::vector<float> dp = convert_vector<float>(m, "DP", i, FLOAT, MAP_FAN["DP"]);
        std::string lw0 = m[MAP_FAN["LW0"][0]][0];

        std::vector<float> lw = convert_vector<float>(m, "LW", i, FLOAT, MAP_FAN["LW"]);
        float volt = std::stof(m[MAP_FAN["VOLT"][0]][0]);;
        std::vector<float> cur = convert_vector<float>(m, "I", i, FLOAT, MAP_FAN["I"]);
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

// ===========================================================================
//                                  Library
// ===========================================================================

void CoolerLibrary::_load_standard_library()
{

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