#ifndef MYMAP_H
#define MYMAP_H

#include <iostream>
#include <map>
#include <string>

// Define the custom structure CustStr
struct CustStr {
    int a;  // Attribute 'a'
    double b;  // Attribute 'b'

    // Constructor for easy initialization
    CustStr(int a_val, double b_val) : a(a_val), b(b_val) {}
};

// Create a type alias for the map with string keys and CustStr values
using MyMapType = std::map<std::string, CustStr>;

// Function to initialize and return the map
MyMapType initializeMap() {
    // Initialize the map with some records
    MyMapType myMap = {
        {"Record1", CustStr(1, 1.1)},
        {"Record2", CustStr(2, 2.2)},
        {"Record3", CustStr(3, 3.3)},
        {"Record4", CustStr(4, 4.4)},
        {"Record5", CustStr(5, 5.5)},
        {"Record6", CustStr(6, 6.6)},
        {"Record7", CustStr(7, 7.7)},
        {"Record8", CustStr(8, 8.8)},
        {"Record9", CustStr(9, 9.9)},
        {"Record10", CustStr(10, 10.1)}
    };

    return myMap;
}

#endif // MYMAP_Hr