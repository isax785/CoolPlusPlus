#ifndef COOLER_LIB_H
#define COOLER_LIB_H

#include <vector>
#include <string>
#include <map>
#include "records.h"
#include "res/headers.h"
#include "res/CoolerStdLib11.h"
#include "../../tls/tls_csv_utils.h"
#include "../../tls/tls_display.h" // DEBUG: for debugging purposes only

const std::string FAN_FILENAME = "FAN";
const std::string COOLER_FILENAME = "ECODRY";   
const std::string HE_FILENAME = "HE";
const std::string ADIAB_FILENAME = "ADIAB";

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
