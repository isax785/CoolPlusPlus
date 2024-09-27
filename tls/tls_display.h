#ifndef TLS_DISPLAY_H
#define TLS_DISPLAY_H

#include <iostream>
#include <map>
#include <vector>

template<class T>
void display_vector(std::vector<T>& vec) {
    for (int i=0; i<vec.size(); i++) std::cout << vec[i] << " ";
    std::cout << std::endl;
};

template<class T, class S>
void display_map_content(std::map<T, std::vector<S>>& m) {
    for ( auto item : m ) {
        std::cout << item.first << ": ";
        display_vector(item.second);
    }
};

template<class T, class S>
void display_map_content(std::map<T, S>& m) {
    for ( auto item : m ) {
        std::cout << item.first << ": " << item.second << std::endl;
    }
};

template<class T, class S>
void display_map_keys(std::map<T, std::vector<S>>& m) {
    for ( auto item : m ) {
        std::cout << item.first << ": ";
    }
};

#endif // TLS_DISPLAY_H