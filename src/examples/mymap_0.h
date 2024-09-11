#ifndef MYMAP_H
#define MYMAP_H

#include <iostream>
#include <map>
#include <string>
#include <vector>

// Define the custom structure CustStr
struct CustStr {
    std::vector<float> a;  // Attribute 'a' is a vector of floats
    std::vector<float> b;  // Attribute 'b' is a vector of floats
};

// Create a type alias for the map with string keys and CustStr values
using MyMapType = std::map<std::string, CustStr>;

// Function to initialize and return the map
MyMapType initializeMap() {
    // Initialize the map with some records
    MyMapType myMap = {
        {"Record1", {{1.1f, 2.2f, 3.3f}, {4.4f, 5.5f, 6.6f}}},
        {"Record2", {{2.2f, 3.3f, 4.4f}, {5.5f, 6.6f, 7.7f}}},
        {"Record3", {{3.3f, 4.4f, 5.5f}, {6.6f, 7.7f, 8.8f}}},
        {"Record4", {{4.4f, 5.5f, 6.6f}, {7.7f, 8.8f, 9.9f}}},
        {"Record5", {{5.5f, 6.6f, 7.7f}, {8.8f, 9.9f, 10.0f}}},
        {"Record6", {{6.6f, 7.7f, 8.8f}, {9.9f, 10.0f, 11.1f}}},
        {"Record7", {{7.7f, 8.8f, 9.9f}, {10.0f, 11.1f, 12.2f}}},
        {"Record8", {{8.8f, 9.9f, 10.0f}, {11.1f, 12.2f, 13.3f}}},
        {"Record9", {{9.9f, 10.0f, 11.1f}, {12.2f, 13.3f, 14.4f}}},
        {"Record10", {{10.0f, 11.1f, 12.2f}, {13.3f, 14.4f, 15.5f}}}
    };

    return myMap;
}

#endif // MYMAP_H
