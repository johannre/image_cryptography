#include "image.h"
#include "encrypter.h"
#include <iostream>
#include <regex>
#include <vector>
#include <bitset>
#include <filesystem>
#include <png++/png.hpp>

using namespace std;
using namespace png;

int main (int argc, char **argv) {
	
	if (argc != 2) {

		cout << "failed to hide information: input has to be" << endl
		     << "./encrypt <name-of-the-picture-with-hidden-data>.png" << endl;

		return -1;

	} else {

		//checking if the input is correct 
		string picture_with_message = argv[1];
		if (!filesystem::exists(picture_with_message)) { cout << "failed to hide information in " << picture_with_message << ": the file \"" 
		                                              << picture_with_message << "\" doesn't exist" << endl; return - 1; }

		//checking if the file has the correct format
		regex its_a_png(".png$");
		smatch png_match;
		if (!regex_search(picture_with_message, png_match, its_a_png)) { 
			cout << "failed to hide information in " << picture_with_message << ": not in png format" << endl; 
		        return -1; 
		}

		//encrypting the data from the picture
		encrypter decodeInfo;
		my_image::image picture(picture_with_message);
		decodeInfo.extract_data_from_picture(picture);

		decodeInfo.tell_data();
	}
	return 0;
}
