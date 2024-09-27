#ifndef COOLER_LIB_H
#define COOLER_LIB_H

#include <vector>
#include <string>
#include <map>
#include "records.h"
#include "res/headers.h"
#include "res/CoolerStdLib11.h"
#include "../../tls/tls_csv_utils.h"


// #include "res/CoolerStdLib11.h"

const std::string FAN_FILENAME = "FAN";
const std::string COOLER_FILENAME = "ECODRY";
const std::string HE_FILENAME = "HE";
const std::string ADIAB_FILENAME = "ADIAB";

// enum TYPES {
//     STR,
//     INT,
//     FLOAT,
// };

// std::vector<std::string> find_csv_files(const std::string& fodler_path);

// std::map<std::string, std::vector<std::string>> read_csv_file(const std::string& filePath);

// void build_csv_data_map(const std::vector<std::vector<std::string>>& lines, std::map<std::string, std::vector<std::string>>& data_map);

// std::vector<std::string> parse_csv_line(const std::string& line);

// template <class T>
// std::vector<T> convert_vector(std::map<std::string, std::vector<std::string>> &m, std::string key, int index, TYPES to_type);

class CoolerTable {
    private:
        bool _fan_csv_imported=false;
        bool _he_csv_imported=false;
        bool _adiab_csv_imported=false;
        bool _cooler_csv_imported=false;
        std::map<std::string, FanRecord> _fan_records;
        std::map<std::string, HERecord> _he_records;
        std::map<std::string, AdiabRecord> _adiab_records;
        std::map<std::string, CoolerRecord> _cooler_records;
        void _populate_fan_records(std::map<std::string, std::vector<std::string>>& m);
        void _populate_he_records(std::map<std::string, std::vector<std::string>>& m);
        void _populate_adiab_records(std::map<std::string, std::vector<std::string>>& m);
        void _populate_cooler_records(std::map<std::string, std::vector<std::string>>& m);
    public:
        CoolerTable(); // Loads standard library
        CoolerTable(const std::string &filepath); // constructor to import a single file
        FanRecord* get_fan_record(const std::string model);
        HERecord* get_he_record(const std::string model);
        AdiabRecord* get_adiab_record(const std::string model);
        CoolerRecord* get_cooler_record(const std::string model);
        void get_fan_record_list();
};

class CoolerLibrary {
    private:
        std::map<std::string, FanRecord> _fan_records;
        std::map<std::string, HERecord> _he_records;
        std::map<std::string, AdiabRecord> _adiab_records;
        std::map<std::string, CoolerRecord> _cooler_records;
        void _load_standard_library();
        void _merge_tables(const std::vector<CoolerTable> table);
    public:
        CoolerLibrary(); // constructor for standard library
        CoolerLibrary(const std::vector<CoolerTable*> &tables, bool standard_library);
};

#endif // COOLER_LIB_H
