#include <iostream>
#include <string>
#include <filesystem>

#include "../../Libraries/cooler_lib.h"
#include "../fan_v04_t11.h"

using namespace std;
namespace fs = std::filesystem;

//   fs::directory_entry Entry{R"(hello.txt)"};

//   std::cout
//       << "The default working directory is:\n"
//       << fs::current_path().string();


int main() { 
    fs::path path="../../Libraries/dev/csv";
    fs::path current = fs::current_path();
    fs::path abs_path = current / path;
    // fs::path abs_path = fs::absolute(path);
    cout << abs_path << endl;

    CoolerTable table (abs_path.string());

    table.get_fan_record_list();

    FanRecord* fan_rec = table.get_fan_record("EBM_A3G800-AY21-71");
    cout << typeid(fan_rec).name() << endl;
    // Fan ebm_fan(fan_rec);

    return 0;
}