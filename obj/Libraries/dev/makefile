table:
	g++ -c dev_table_library.cpp ../cooler_lib.cpp ../../../tls/tls_csv_utils.cpp ../res/headers.cpp 
	g++ dev_table_library.o cooler_lib.o tls_csv_utils.o headers.o -o dev_table_library
	rm -f *.o
	./dev_table_library.exe