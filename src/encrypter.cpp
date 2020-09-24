#include "encrypter.h"

using namespace std;
using namespace png;

//prints the encrypted data
void encrypter::tell_data() { 
	std::cout << "Encoded data:\t";
	for (int i = 0; i < size; i++) std::cout << data[i]; 
	std::cout << std::endl;
}

std::string encrypter::get_size_from_pixel(my_image::image &pic, int i, int j) {
	my_image::pixel &p = pic(i, j);
	std::string retString = "";
	retString += std::to_string(p.r % 10);
	retString += std::to_string(p.g % 10);
	retString += std::to_string(p.b % 10);
	return retString;
}

void encrypter::get_size(my_image::image &pic) { //WORKS
	int j = 0;
	for (int i = 0; i < 3; i++) {
		size_binary += get_size_from_pixel(pic, i, j); 
	}
	size = std::stoi(size_binary, nullptr, 2);
	size_of_bitvec = size * 8;
	data = new char[size];
}

//extracts the data from the picture and writes it into the attribute data
void encrypter::extract_data_from_picture(my_image::image &pic) {
	get_size(pic);
	get_values_from_pixels(pic);
	make_binary_to_data();
}

//ATTENTION! THE VECTOR BINVEC HOLDS THE BINARY NUMBERS, BUT WITH BIG ENDIAN, SO THE
//"WRONG" WAY AROUND! BECAUSE OF THAT I CALCULATED IT THE OTHER WAY.
void encrypter::make_binary_to_data() { 
	for (int i = 0; i < size; i++) {
		bin_vec.push_back("");
	}
	int k = 0;
	for (int i = 0; i < (size * 8); i++) {
		if (i % 8 == 0 && i != 0) k++;
		bin_vec[k] += pixel_binaries[i];
		//if (i < 8) { bin_vec[0] += pixel_binaries[i]; }
		//else { bin_vec[1] += pixel_binaries[i]; }
	}
	for (int i = 0; i < size; i++) {
		int c = 0;
		for (int j = 0; j < 8; j++) {
			if (bin_vec[i][j] == '1') {
				c += pow(2, (j));
			}
		}
		data[i] = c;
	}
}

std::string encrypter::get_from_pixel(my_image::image &pic, int i, int j, int &sizeiterator) {
	my_image::pixel &p = pic(i, j); 
	std::string retString = "";
	retString += std::to_string(p.r % 10);
	sizeiterator++;
	if (sizeiterator >= size_of_bitvec) return retString;
	retString += std::to_string(p.g % 10);
	sizeiterator++;
	if (sizeiterator >= size_of_bitvec) return retString;
	retString += std::to_string(p.b % 10);
	sizeiterator++;
	if (sizeiterator >= size_of_bitvec) return retString;
	return retString;
}

//writes the binary values of first pixels into a string
void encrypter::get_values_from_pixels(my_image::image &pic) { 
	//TESTING:
	int sizeiterator = 0;
	int loopiterator = size_of_bitvec / 3 + 3;
	if (size_of_bitvec % 3 != 0) loopiterator++;
	int j = 0;
	for (int i = 3; i < loopiterator; i++) {
		pixel_binaries += get_from_pixel(pic, i, j, sizeiterator);
	}
}
