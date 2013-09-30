CXXFLAGS=-c -O2 -I.
CXX=g++

all: libtiny.a

libtiny.a:  string.o iostream.o
	ar rcu libtiny.a string.o iostream.o && ranlib libtiny.a

string.o: string.cpp string

iostream.o: iostream.cpp iostream

clean:
	rm *.o *.a

