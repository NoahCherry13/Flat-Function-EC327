CC=g++ -g -std=c++17

OBJS=main.o Course.o FileIn.o FindConflicts.o Professor.o

default: Algorithm

Algorithm: $(OBJS)
	$(CC) -o Algorithm $(OBJS) 

Professor.o: Professor.cpp Professor.h
	$(CC) -c Professor.cpp -o Professor.o

Course.o: Course.cpp Course.h Professor.h
	$(CC) -c Course.cpp -o Course.o 
	
FileIn.o: FileIn.cpp FileIn.h
	$(CC) -c FileIn.cpp -o FileIn.o 

FindConflicts.o: FindConflicts.cpp FindConflicts.h Professor.h
	$(CC) -c FindConflicts.cpp -o FindConflicts.o 

main.o: main.cpp Professor.h FileIn.h Course.h VariadicTable.h
	$(CC) -c main.cpp -o main.o

Algorithm: main.o Professor.o Course.o FileIn.o FindConflicts.o
	$(CC) -o Algorithm.exe main.o Professor.o Course.o FileIn.o FindConflicts.o
	
clean: 
	rm $(OBJS) Algorithm *.exe

