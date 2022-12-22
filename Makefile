run:
	g++ ./src/*.cpp -o ./build/cipher && ./build/cipher

clean:
	rm ./build/cipher
