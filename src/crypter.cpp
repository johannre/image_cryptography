#include "crypter.h"

using namespace std;
using namespace png;

extern bool size_error;

crypter::crypter(std::string dataname) : dataname(dataname), size(0), data(nullptr) {

				//getting size of the file-data
				ifstream input(dataname, ios::ate);
				size = input.tellg();
				input.seekg(0, ios::beg);

				size_of_size_in_byte = size * 8;
				size--;

				if (size > 159) {
					cout << "failed to hide text: text is too long (max. 159 signs)" << endl;
					size_error = true;
				}

				data = new char[size];

				//reading the data from the file
				input.read((char *)data, size);

}

//converts the size in binary to store it in the picture
void crypter::make_size_binary() { size_in_binary = std::bitset<9>(size).to_string(); }

void crypter::hide_data_in_picture(my_image::image &pic) {

	if (!size_error) {
		make_size_binary();
		make_binary();
		hide_information(pic);
	}

}

//stores information in the pixels
void crypter::embed(my_image::image &pic, int i, int j, int &binary_iterator, int &vector_iterator) {

	my_image::pixel &p = pic(i, j);

	char c = b.bitvec[vector_iterator][binary_iterator];
	p.r = p.r - p.r % 10 + (c - 48);
	binary_iterator++;
	if (binary_iterator >= b.bitvec[vector_iterator].size()) { binary_iterator = 0; vector_iterator++; }
	if (vector_iterator >= b.bitvec.size()) return;

	char d = b.bitvec[vector_iterator][binary_iterator];
	p.g = p.g - p.g % 10 + (d - 48);
	binary_iterator++;
	if (binary_iterator >= b.bitvec[vector_iterator].size()) { binary_iterator = 0; vector_iterator++; }
	if (vector_iterator >= b.bitvec.size()) return;

	char e = b.bitvec[vector_iterator][binary_iterator];
	p.b = p.b - p.b % 10 + (e - 48);
	binary_iterator++;
	if (binary_iterator >= b.bitvec[vector_iterator].size()) { binary_iterator = 0; vector_iterator++; }
	if (vector_iterator >= b.bitvec.size()) return;

}

//stores the size of the file in the first pixels
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

//hiding the information in the pixels by iterating through them and calling the embed function
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
	int k = 3;
	int vector_iterator = 0;
	for (int i = 3; i < (loopiterator + 3); i++) {
		embed(pic, k, j, binary_iterator, vector_iterator);
		if (k >= pic.w) j++, k = 0;
		k++;
	}

	for (int i = 0; i < loopiterator + 3; i++) my_image::pixel &x = pic(i, j);

}

//turns the values of data into binaries and writes the binary in an extra string
void crypter::make_binary() {

	for (int i = 0; i < size; i++) {
		b.its = std::bitset<8>(data[i]).to_string();
		b.bitvec.push_back(b.its);
	}

	for (int i = 0; i < size; i++) reverse(b.bitvec[i].begin(), b.bitvec[i].end());

	b.its = std::bitset<8>(size).to_string();
	b.its_from_size = b.its;
	b.size_of_bitvec = 0;

	for (int i = 0; i < b.bitvec.size(); i++) b.size_of_bitvec += b.bitvec[i].size();

}
