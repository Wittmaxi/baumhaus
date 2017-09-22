
CC=g++
CFLAGS=-std=c++11 -pthread
TARGET=bindir/baumhaus

baumhausmake: bindir
	$(CC)  $(CFLAGS) src/*.cpp src/pieces/*.cpp -o $(TARGET)

bindir:
	mkdir -p bindir

clean:
	rm -Rf bindir/*
