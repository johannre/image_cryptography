#include "encrypter.h"

using namespace std;
using namespace png;

//extracts the size of the data from the (by i and j) given pixel
string encrypter::get_size_from_pixel(my_image::image &pic, int i, int j) {

	my_image::pixel &p = pic(i, j);
	string return_string = "";
	return_string += to_string(p.r % 10);
	return_string += to_string(p.g % 10);
	return_string += to_string(p.b % 10);

	return return_string;

}

//get size of the file and allocate the matching memory to store the data later
void encrypter::get_size(my_image::image &pic) {

	int j = 0;
	for (int i = 0; i < 3; i++) size_binary += get_size_from_pixel(pic, i, j);

	size = stoi(size_binary, nullptr, 2);
	size_of_bitvec = size * 8;
	data = new char[size];

}

//extracts the data from the picture and writes it into the data-member
void encrypter::extract_data_from_picture(my_image::image &pic) {

	get_size(pic);
	get_values_from_pixels(pic);
	make_binary_to_data();

}

//turns binary data into real characters. The bin_vec-vector holds the
//information with big-endian, so we have to read it the other way around.
void encrypter::make_binary_to_data() {

	for (int i = 0; i < size; i++) bin_vec.push_back("");

	int k = 0;
	for (int i = 0; i < (size * 8); i++) {
		if (i % 8 == 0 && i != 0) k++;
		bin_vec[k] += pixel_binaries[i];
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

//reads the binary values from the rgb-values of one pixel (given by i and j) and returns the binary
string encrypter::get_from_pixel(my_image::image &pic, int i, int j, int &sizeiterator) {

	my_image::pixel &p = pic(i, j);
	string return_string = "";

	return_string += to_string(p.r % 10);
	sizeiterator++;
	if (sizeiterator >= size_of_bitvec) return return_string;

	return_string += to_string(p.g % 10);
	sizeiterator++;
	if (sizeiterator >= size_of_bitvec) return return_string;

	return_string += to_string(p.b % 10);
	sizeiterator++;
	if (sizeiterator >= size_of_bitvec) return return_string;

	return return_string;

}

//writes the binary values of the first pixels into a string
void encrypter::get_values_from_pixels(my_image::image &pic) {

	int sizeiterator = 0;
	int loopiterator = size_of_bitvec / 3 + 3;
	if (size_of_bitvec % 3 != 0) loopiterator++;

	int j = 0;
	for (int i = 3; i < loopiterator; i++) pixel_binaries += get_from_pixel(pic, i, j, sizeiterator);

}
void encrypter::tell_data() {

	cout << "Encoded data:\t";
	for (int i = 0; i < size; i++) cout << data[i];
	cout << endl;

}
