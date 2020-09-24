all:
	g++ -std=c++2a -g -o crypt crypt.cpp crypter.cpp image.cpp -lpng
	g++ -std=c++2a -g -o encrypt encrypt.cpp encrypter.cpp image.cpp -lpng

.PHONY: clean 

clean: encrypt crypt
	rm -rf encrypt crypt
