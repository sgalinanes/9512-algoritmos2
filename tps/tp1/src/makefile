CXXFLAGS = -Wall -g
CXX = g++

all : tp1

tp1: main.o process.o diccionario.o errors.o cmdline.o
	$(CXX) $(CXXFLAGS) -o tp1 main.o process.o diccionario.o errors.o cmdline.o

errors.o: errors.cpp errors.h types.h
	$(CXX) $(CXXFLAGS) -o errors.o -c errors.cpp

cmdline.o: cmdline.cpp cmdline.h
	$(CXX) $(CXXFLAGS) -o cmdline.o -c cmdline.cpp

diccionario.o: diccionario.cpp diccionario.h types.h arreglo.h
	$(CXX) $(CXXFLAGS) -o diccionario.o -c diccionario.cpp

process.o: process.cpp process.h types.h diccionario.cpp diccionario.h 
	$(CXX) $(CXXFLAGS) -o process.o -c process.cpp

main.o: main.cpp process.cpp process.h diccionario.cpp diccionario.h cmdline.cpp cmdline.h types.h errors.cpp errors.h
	$(CXX) $(CXXLAGS) -o main.o -c main.cpp 

clean :
	rm *.o
