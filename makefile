baumhausmake: bindir 
	g++ src/*.cpp src/pieces/*.cpp -o bin/baumhaus

bindir:
	mkdir -p bin