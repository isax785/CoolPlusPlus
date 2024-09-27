# DOC - Tools

- [DOC - Tools](#doc---tools)
- [Display](#display)

---

The **Tools** are geenral purpose functions/classes to be used (mainly for debugging purposes) for the development of the various classes or functions.

All the tools are implemented into `.h` files in order to ease the compilation process of the scripts/projects into which they are included.

# Display

Functions to display (i.e. printout) data structures of mid/high complexity.

```cpp
// vector printout
template<class T> void display_vector(std::vector<T>& vec) {...};

template<class T, class S> void display_map(std::map<T, S>& m) {...};

// map printout, items are vectors
template<class T, class S> void display_map_content(std::map<T, std::vector<S>>& m) {...};

// map printout, items (i.e. second) are simple elements (e.g. string, int, ...)
template<class T, class S> void display_map_content(std::map<T, S>& m) {...};

// mpa keys (i.e. first) printout
template<class T, class S> void display_map_keys(std::map<T, std::vector<S>>& m) {...};
```