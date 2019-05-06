CXXFLAGS = -Wall -g
CXX = g++

all : tm_tp1

tm_tp1: tm_main.o process.o diccionario.o errors.o cmdline.o
	$(CXX) $(CXXFLAGS) -o tm_tp1 tm_main.o process.o diccionario.o errors.o cmdline.o

errors.o: errors.cpp errors.h types.h
	$(CXX) $(CXXFLAGS) -o errors.o -c errors.cpp

cmdline.o: cmdline.cpp cmdline.h
	$(CXX) $(CXXFLAGS) -o cmdline.o -c cmdline.cpp

diccionario.o: diccionario.cpp diccionario.h types.h arreglo.h
	$(CXX) $(CXXFLAGS) -o diccionario.o -c diccionario.cpp

process.o: process.cpp process.h types.h diccionario.cpp diccionario.h 
	$(CXX) $(CXXFLAGS) -o process.o -c process.cpp

tm_main.o: tm_main.cpp process.cpp process.h diccionario.cpp diccionario.h cmdline.cpp cmdline.h types.h errors.cpp errors.h
	$(CXX) $(CXXLAGS) -o tm_main.o -c tm_main.cpp 

clean :
	rm *.o
