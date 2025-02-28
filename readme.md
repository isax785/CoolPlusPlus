# Readme

- [Readme](#readme)
- [Project Overview](#project-overview)
- [MOC](#moc)

---

- [ ] `#a` MOC of the project


# Project Overview

- `/doc`: documentation and notes
- `/obj`: 
  - `/Components`
  - `/Libraries`
  - `/Machines`
- `/res`: 
- `/src`: 
- `/tls`: tools for general usage, mainly for development purposes (e.g. vector printout, map printout). Files `.h` to be included into each script (`.cpp`) [^1].
  - `/dev`: development of tools;
  - `/tls_display.h`

[^1]: `.h` files includ both declarations and definitions. This ease writing the compiling instruction for the `.cpp` that imports them.

# MOC

- **Components**
  - [DOC - Fan](./obj/Components/doc/doc_fan_v04_t11.md)
- **Libraries**
  - [DOC - Tables and Libraries](./obj/Libraries/doc/doc_tables_libraries.md): general documentation for all the `Table` and `Library` classes.
  - [DOC - Cooler Table and Library](./obj/Libraries/doc/doc_cooler_table_library.md): documentation of `CoolerTable` and `CoolerLibrary` classes, i.e. table and library related to the `Cooler` machine class.
  - [DRW - Tablse and Libraries](./obj/Libraries/doc/drw_tables_libraries.excalidraw): all the drawings belonging to the tables and libraryes documentation.
- **Machines**
- **Tools**
  - [DOC - Tools](./tls/doc/doc_tools.md): tools for development purposes.