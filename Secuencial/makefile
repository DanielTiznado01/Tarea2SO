CC = g++
CFLAGS = -std=c++11 $(shell pkg-config --cflags opencv4)
LIBS = $(shell pkg-config --libs opencv4)

all: secuencial

secuencial: secuencial.cpp
	$(CC) $(CFLAGS) secuencial.cpp -o secuencial $(LIBS)

clean:
	rm -f secuencial
