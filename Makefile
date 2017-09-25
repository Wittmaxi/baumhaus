
CC=g++
CFLAGS=-std=c++11 -pthread
TARGET=bin/baumhaus

baumhausmake: bin
	$(CC)  $(CFLAGS) src/*.cpp src/pieces/*.cpp -o $(TARGET)

bin:
	mkdir -p bin

clean:
	rm -Rf bin/*
