# DOC - Tables and Libraries

- [DOC - Tables and Libraries](#doc---tables-and-libraries)
- [Tables](#tables)
- [Libraries](#libraries)
- [Standard Library](#standard-library)

---

Overview of the `Table`s classes and `Library`s classes implementations. 

Here are reported all the `Table`/`Library` classes without any reference to a specific machine. 

The general structure of the classes is here described: all the notes here reported are to be applied to all the machine-specific tables and libraries.

# Tables

The table class is aimed at importing a full, single set of components that defines a range of machines. 

The class imports multiple files included into a folder, by avoiding files having the same content type (e.g. `FAN.csv` and `FAN1.csv` into the same folder).

The scope of each table is containing a full set of machines with their components. It follows that a table contains a complete set of components to fully characterize a machine.

If multiple set of machines or components (i.e. multiple files with the same content type) are needed, a `Library` class is to be instantiated.

# Libraries

A library is a set of 

- [ ] describe the multiple different declarations

# Standard Library

`StdLibraryXYZ.h`

- [ ] generation (i.e. `ipynb` file)
- [ ] structure
- [ ] import into `Library`