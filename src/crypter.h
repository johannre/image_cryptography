#ifndef _CRYPTING_HIDER_H_
#define _CRYPTING_HIDER_H_

#include "image.h"
#include <string>
#include <fstream>
#include <bitset>
#include <iomanip>
#include <png++/png.hpp>
#include <cmath>
#include <iostream>

struct bit_information {
	bit_information() : bitvec(std::vector<std::string> ( )), its("") { };
	std::vector<std::string> bitvec;
	//how many single numbers (0s and 1s) has bitvec at all?
	int size_of_bitvec;
	std::string its;
	std::string its_from_size;
};

class crypter {
	public:
		crypter(std::string);
		void hide_data_in_picture(my_image::image &);
		~crypter() { delete [] data; }
	private:
		char *data;
		int size;
		std::string dataname; 
		struct bit_information {
			bit_information() : bitvec(std::vector<std::string> ( )), its("") { };
			std::vector<std::string> bitvec;
			//how many single numbers (0s and 1s) has bitvec at all?
			int size_of_bitvec;
			std::string its;
			std::string its_from_size;
		};
		void make_binary();
		void make_size_binary();
		void embed_size(my_image::image &, int, int, int &);
		std::string size_in_binary;
		void embed(my_image::image &, int, int, int &, int &);
		void hide_information(my_image::image &);
		int size_of_size_in_byte;
		bit_information b;
};

#endif //_CRYPTING_HIDER_H_
