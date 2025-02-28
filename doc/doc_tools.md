# DOC - Tools

- [DOC - Tools](#doc---tools)
- [Display](#display)
- [CSV Utilities](#csv-utilities)
- [Polynomial](#polynomial)
  - [References](#references)

---

The **Tools** are geenral purpose functions/classes to be used (mainly for debugging purposes) for the development of the various classes or functions.

All the tools are implemented into `.h` files in order to ease the compilation process of the scripts/projects into which they are included.

# Display

Functions to display (i.e. printout) data structures of mid/high complexity.

All the function definitions are included into the headers (i.e. `.h`) file are templated funcitons, in order to run with any type of content (compatible with the `<<` operator):

- `display_vector`: the content of a vector;
- `display_map_content`: printout of a map content, all the key-value pairs. Two declarations depending on the value:
  1. simple value: single variable;
  2. vector value: array.
- `display_map_keys`: all the keys of a map.

Declarations:

```cpp
// vector printout
template<class T> void display_vector(std::vector<T>& vec) {...};

// map printout, items are vectors
template<class T, class S> void display_map_content(std::map<T, std::vector<S>>& m) {...};

// map printout, items (i.e. second) are simple elements (e.g. string, int, ...)
template<class T, class S> void display_map_content(std::map<T, S>& m) {...};

// mpa keys (i.e. first) printout
template<class T, class S> void display_map_keys(std::map<T, std::vector<S>>& m) {...};
```

# CSV Utilities

Functions to read and import the content of a CSV file:

- `parse_csv_line`: parsing of a line of the CSV, splitting the content on `;`;
- `find_csv_file`: find the list of all the CSV files contained into a folder;
- `build_csv_data_map`: build the data map with the CSV content;
- `read_csv_file`: read a CSV file;
- `convert_vector`: conversion of a vector from string to the specified type.

Also the `enum` to handle the conversion is declared in `.h`:

```cpp
enum TYPES {
    STR,
    INT,
    FLOAT,
};
```

All the functions are declared in `.h` and defined into the corresponding `.cpp` file.

```cpp
// parse a CSV line with `;` separator
std::vector<std::string> parse_csv_line(const std::string& line); 

// scan a folder and find all CSV files
std::vector<std::string> find_csv_files(const std::string& folder_path); 

// build a data map with the CSV content
void build_csv_data_map(const std::vector<std::vector<std::string>>& lines_vector, std::map<std::string, std::vector<std::string>> &data_map);

// read a full CSV file
std::map<std::string, std::vector<std::string>> read_csv_file(const std::string& filePath);
```

Diffferently, the `convert_vector` is defined into the `.h` file[^1].

[^1]: dealing with a templated function, the compilation process needs its definition into the headers file to properly compile and link all the function possible variants.

```cpp
template <typename T>
std::vector<T> convert_vector(std::map<std::string, std::vector<std::string>> &m, 
                              std::string key, 
                              int index, 
                              TYPES to_type,
                              std::vector<std::string> &keys) {...}
```

# Polynomial

Functions to deal with polynomials.

## References

- [Numpy `polyfit`](https://numpy.org/doc/stable/reference/generated/numpy.polynomial.polynomial.polyfit.html): Least-squares fit of a polynomial to data.
- [Numpy `polyval`](https://numpy.org/doc/stable/reference/generated/numpy.polynomial.polynomial.polyval.html): Evaluate a polynomial at points x.
- [Theory and C# Implementation](https://www.codeproject.com/Articles/63170/Least-Squares-Regression-for-Quadratic-Curve-Fitti)