#include "image.h"
#include "crypter.h"
#include <iostream>
#include <regex>
#include <filesystem>

using namespace std;
using namespace png;

//if the entered text-size is too high, this turns true and the rest of the program won't be executed
bool size_error = false;

//if all inputs have the right format, exist when they should exist and so on, the function returns true, otherwise false.
bool check_if_input_is_correct(const string &source_picture, const string &picture_with_message, const string &secret_file) {
	
	if (!filesystem::exists(source_picture)) { 
		cout << "failed to hide information in " << source_picture << ": the file \"" << source_picture << "\" doesn't exist" << endl; 
		return false; 
	}

	if (!filesystem::exists(secret_file)) { 
		cout << "failed to hide information from " << secret_file << ": the file \"" << secret_file << "\" doesn't exist" << endl; 
		return false; 
	}

	//checking if the files have the correct format
	regex its_a_png(".png$");
	smatch png_match;
	if (!regex_search(source_picture, png_match, its_a_png)) { 
		cout << "failed to hide information in " << source_picture << ": not in png format" << endl; 
		return false; 
	}

	if (!regex_search(picture_with_message, png_match, its_a_png)) { 
		cout << "failed to hide information in " << picture_with_message << ": not in png format" << endl; 
		return false; 
	}

	return true;

}

int main (int argc, char **argv) {

	if (argc != 4) {

		cout << "failed to hide information: input has to be" << endl 
		     << "./crypt <source-picture-name>.png <new-picture-with-hidden-data>.png <file-with-message-to-crypt>" << endl;

		return -1;

	} else {

		string source_picture = argv[1];
		string picture_with_message = argv[2];
		string secret_file = argv[3];

		if (check_if_input_is_correct(source_picture, picture_with_message, secret_file)) {

			//hide the data in the picture 
			my_image::image pic(source_picture);
			crypter hide_the_info(secret_file);
			if (!size_error) {
				hide_the_info.hide_data_in_picture(pic);
				pic.save(picture_with_message);
			}

		}
	}

	return 0;

}
