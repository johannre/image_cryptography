#include "crypter.h"

using namespace std;
using namespace png;

crypter::crypter(std::string dataname) : dataname(dataname), size(0), data(nullptr) {
			//getting size of data
			ifstream input(dataname, ios::ate);
			size = input.tellg();
			input.seekg(0, ios::beg);
			//size_of_size_in_byte represents the size of the variable size in byte
			//so that we can allocate fitting memory
			size_of_size_in_byte = size * 8;
			size--;
			data = new char[size];
			//reads the informations from the file hiddenfile.txt into the array data
			input.read((char *)data, size);
			//thats so that the string is ending and doesnt put out random numbers
			data[size] = '\0';
}

void crypter::make_size_binary() { //WORKS
	size_in_binary = std::bitset<9>(size).to_string();
}

//this is the main hiding function. It hides the data in the picture.
void crypter::hide_data_in_picture(my_image::image &pic) {
	//creats binary of size (its_from_size) and binaries of data (itvec);
	make_size_binary();
	make_binary();
	hide_information(pic);
}

//this function embeds the information in each pixel. So far, to make it easy, 
//the function sets each color value of each pixel EQUAL to the bit, so 0 or 1.
//In the future im gonna change this to the wished setting, thats just for the first 
//test to make it more easy. Because we're using references, the settings change 
//with the function for the original pic. Its also iterating up if the binary_iterator
//for each single bit is gets to big for the string. Is that the case, the 
//binary_iterator sets to zero and starts iterating from the beginning and the 
//vector_iterator which iterates through the words increases.
void crypter::embed(my_image::image &pic, int i, int j, int &binary_iterator, int &vector_iterator) {
	my_image::pixel &p = pic(i, j);
	char c = b.bitvec[vector_iterator][binary_iterator];
	p.r = p.r - p.r % 10 + (c - 48);
	binary_iterator++;
	if (binary_iterator >= b.bitvec[vector_iterator].size()) {
		binary_iterator = 0; vector_iterator++;
	}
	if (vector_iterator >= b.bitvec.size()) { 
		return  ;
	}
	char d = b.bitvec[vector_iterator][binary_iterator];
	p.g = p.g - p.g % 10 + (d - 48);
	binary_iterator++;
	if (binary_iterator >= b.bitvec[vector_iterator].size()) {
		binary_iterator = 0; vector_iterator++;
	}
	if (vector_iterator >= b.bitvec.size()) { 
		return  ;
	}
	char e = b.bitvec[vector_iterator][binary_iterator];
	p.b = p.b - p.b % 10 + (e - 48);
	binary_iterator++;
	if (binary_iterator >= b.bitvec[vector_iterator].size()) {
		binary_iterator = 0; vector_iterator++;
	}
	if (vector_iterator >= b.bitvec.size()) { 
		return  ;
	}
}

void crypter::embed_size(my_image::image &pic, int i, int j, int &binary_iterator) {
	my_image::pixel &p = pic(i, j);
	char c = size_in_binary[binary_iterator];
	p.r = p.r - p.r % 10 + c - 48;
	binary_iterator++;
	char d = size_in_binary[binary_iterator];
	p.g = p.g - p.g % 10 + d - 48;
	binary_iterator++;
	char e = size_in_binary[binary_iterator];
	p.b = p.b - p.b % 10 + e - 48;
	binary_iterator++;
}

//it hides the information in each pixel by iterating threw it and calling the embed function
//which really changes each color value of each pixel. 
void crypter::hide_information(my_image::image &pic) {
	int loopiterator = b.size_of_bitvec / 3;
	if (b.size_of_bitvec % 3 != 0) loopiterator++;
	int j = 0;
	int binary_iterator = 0;
	for (int i = 0; i < 3; i++) {
		embed_size(pic, i, j, binary_iterator);
		my_image::pixel &x = pic(i, j);
	}
	binary_iterator = 0;
	int i2 = 3;
	int vector_iterator = 0;
	for (int i = 3; i < (loopiterator + 3); i++) {
		embed(pic, i2, j, binary_iterator, vector_iterator);
		if (i2 >= pic.w) { j++; i2 = 0; }
		i2++;
	}
	for (int i = 0; i < loopiterator + 3; i++) {
		my_image::pixel &x = pic(i, j);
	}
}

void crypter::make_binary() { //WORKS
	//turns the values of data into binaries and writes the binary in an extra string
	for (int i = 0; i < size; i++) {
		b.its = std::bitset<8>(data[i]).to_string();
		b.bitvec.push_back(b.its);
	}
	for (int i = 0; i < size; i++) {
		reverse(b.bitvec[i].begin(), b.bitvec[i].end());
	}
	b.its = std::bitset<8>(size).to_string();
	b.its_from_size = b.its;
	b.size_of_bitvec = 0;
	for (int i = 0; i < b.bitvec.size(); i++) 
		b.size_of_bitvec += b.bitvec[i].size();
}
