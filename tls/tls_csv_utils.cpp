#include "tls_csv_utils.h"

std::vector<std::string> parse_csv_line(const std::string& line) { // parses a CSV line with `;` separator
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
};

std::vector<std::string> find_csv_files(const std::string& folder_path) { // scans a folder and find all CSV files
    std::vector<std::string> csvFiles;

    for (const auto& entry : fs::directory_iterator(folder_path)) {
        if (entry.is_regular_file() && entry.path().extension() == ".csv") {
            csvFiles.push_back(entry.path().string());
        }
    }

    return csvFiles;
};

void build_csv_data_map(const std::vector<std::vector<std::string>>& lines_vector, std::map<std::string, std::vector<std::string>> &data_map) {
    // allocate each column into the map

    for (int i=0; i<lines_vector[0].size(); i++) { // headers row
        data_map[lines_vector[0][i]] = {};
        // cout << i << " " << lines[0][i] << endl;
    }
    for (int i=1; i<lines_vector.size(); i++) {
        for (int j=0; j<lines_vector[i].size(); j++) {
            // std::cout << lines_vector[i][j] << std::endl; // DEBUG
            data_map[lines_vector[0][j]].push_back(lines_vector[i][j]);
        }
    }
};

std::map<std::string, std::vector<std::string>> read_csv_file(const std::string& filePath) {
    // NOTE: 1. reads the csv file
    //       2. parses each line (row) into vector<string>
    //       3. arranges the rows into columns as  map<string, vector<string>
    //          (first: column header - second> content vector<string>)
    //       4. returns the map (map<string, vector<string>)

    std::map<std::string, std::vector<std::string>> data_map;
    std::ifstream file(filePath);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filePath << std::endl;
        return data_map;
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

    // // allocate each column into the map
    // for (int i=0; i<lines[0].size(); i++) { // headers row
    //     data_map[lines[0][i]] = {};
    //     // cout << i << " " << lines[0][i] << endl;
    // }
    // for (int i=1; i<lines.size(); i++) {
    //     for (int j=0; j<lines[i].size(); j++) {
    //         data_map[lines[0][j]].push_back(lines[i][j]);
    //     }
    // }

    build_csv_data_map(lines, data_map);
    
    file.close();
    return data_map;
};