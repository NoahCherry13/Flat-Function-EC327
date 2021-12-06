CC=g++ -g -std=c++11

OBJS=Algorithm.o Course.o FileIn.o FindConflicts.o Professor.o

default: Algorithm

Algorithm: $(OBJS)
	$(CC) -o Algorithm $(OBJS) 

Course.o: Course.cpp Course.h Professor.h
	$(CC) -c Course.cpp -o Course.o 
	
FileIn.o: FileIn.cpp FileIn.h
	$(CC) -c FileIn.cpp -o FileIn.o 

Professor.o: Professor.cpp Professor.h
	$(CC) -c Professor.cpp -o Professor.o

FindConflicts.o: FindConflicts.cpp FindConflicts.h Professor.h
	$(CC) -c FindConflicts.cpp -o FindConflicts.o 

Algorithm.o: Algorithm.cpp Professor.h FileIn.h Course.h
	$(CC) -c Algorithm.cpp -o Algorithm.o

Algorithm: Algorithm.o Professor.o Course.o FileIn.o FindConflicts.o
	$(CC) -o Algorithm.exe Algorithm.o Professor.o Course.o FileIn.o FindConflicts.o
	
clean: 
	rm $(OBJS) Algorithm *.exe

