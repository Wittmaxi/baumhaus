
compileFlags=-std=c++11 -pthread

baumhausmake: bindir
	g++  $(compileFlags) src/*.cpp src/pieces/*.cpp -o bin/baumhaus

bindir:
	mkdir -p bin

clean:
	rm -Rf bin/*
