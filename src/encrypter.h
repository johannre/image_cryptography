#ifndef _CRYPTING_DECODER_H_
#define _CRYPTING_DECODER_H_

#include "image.h"
#include <png++/png.hpp>
#include <iostream>
#include <cmath>

class encrypter {
	public:
		encrypter() : pixel_binaries(""), size_binary("") { };
		void extract_data_from_picture(my_image::image &);
		void tell_data();
		~encrypter() { delete [] data; }
	private:
		int size;
		std::string pixel_binaries;
		std::string size_binary;
		std::vector <std::string> bin_vec;
		
		//unimportant shit which is used in the function
		void get_values_from_pixels(my_image::image &);
		void make_binary_to_data();
		void get_size(my_image::image &);
		std::string get_size_from_pixel(my_image::image &, int, int);
		std::string get_from_pixel(my_image::image &, int, int, int &);
		char *data;
		int size_of_bitvec;
		int size_of_bitvec_double;
};

#endif //_CRYPTING_DECODER_H_
