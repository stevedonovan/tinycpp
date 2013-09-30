CXXFLAGS=-c -O2 -Itiny
CXX=g++

ifdef ComSpec
	TARGET=ohello.exe
	RM=del
else
	TARGET=ohello
	RM=rm
endif

all: $(TARGET)

$(TARGET):  ohello.o tiny/libtiny.a
	g++ -o $(TARGET) ohello.o -Wl,-s -Ltiny -ltiny

ohello.o: ohello.cpp

clean:
	$(RM) $(TARGET) ohello.o

