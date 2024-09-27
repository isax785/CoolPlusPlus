#include <iostream>
// #include <vector>
// #include <string>
// #include <map>
// #include "../res/CoolerStdLib11.h"
#include "../cooler_lib.h"
// #include "../records.h"
#include "../../../tls/tls_display.h"
// #include "../../../tls/tls_csv_utils.h"

using namespace std;

int main() {
    // ======= find csv files
    string path = "../res";
    vector<string> files = find_csv_files(path);
    display_vector(files);  // DEBUG

    // ======= read first csv
    // map<string, vector<string>> csv_content = read_csv_file(files[0]);
    // display_map_vector(csv_content); // DEBUG

    // ======= instantiate STD Table
    // CoolerTable* table_std = new CoolerTable();
    // // table_std->get_fan_record_list();

    // // ======= instantiate Table from files
    // CoolerTable* table = new CoolerTable("../res/csv");
    // FanRecord* fan = table->get_fan_record("EBM_A3G800KU2103");
    // display_vector(fan->_n_rpm);

    // ======= instantiate Library
    // vector<CoolerTable*> tables = {table};
    // CoolerLibrary* library = new CoolerLibrary();

}