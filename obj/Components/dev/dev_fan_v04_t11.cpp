#include <iostream>
#include <string>
#include <filesystem>

#include "../../Libraries/cooler_lib.h"

using namespace std;
namespace fs = std::filesystem;

//   fs::directory_entry Entry{R"(hello.txt)"};

//   std::cout
//       << "The default working directory is:\n"
//       << fs::current_path().string();


int main() { 
    fs::path path="../../Libraries/res";
    fs::path current = fs::current_path();
    fs::path abs_path = current / path;
    // fs::path abs_path = fs::absolute(path);
    cout << abs_path << endl;

    CoolerTable table (abs_path.string());

    return 0;
}