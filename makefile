baumhausmake: bindir 
	g++ src/*.cpp -o bin/baumhaus

bindir:
	mkdir -p bin
