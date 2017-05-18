baumhausmake: bindir 
	g++ -std=c++11 src/*.cpp src/pieces/*.cpp -o bin/baumhaus

bindir:
	mkdir -p bin
