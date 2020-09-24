all:
	g++ -std=c++2a -g -o crypt crypt.cpp crypter.cpp image.cpp -lpng
	g++ -std=c++2a -g -o encrypt encrypt.cpp encrypter.cpp image.cpp -lpng

.PHONY: clean 

clean: 
	find . -type f -not -name 'crypt.cpp' -not -name 'crypter.h' -not -name 'crypter.cpp' -not -name 'image.h' -not -name 'image.cpp' -not -name 'encrypt.cpp' -not -name 'encrypter.cpp' -not -name 'encrypter.h' -not -name 'Makefile' -delete
