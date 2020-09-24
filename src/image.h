#ifndef _MY_IMAGE_H_
#define _MY_IMAGE_H_

#include <png++/png.hpp>
#include <cassert>
#define PI 3.14159265359
#define eulersche_zahl_e 2.718281828459

//the namespace is necessary to avoid conflicts with the png-library
namespace my_image {

	//the basic structure all images are made up of
	struct pixel {
		pixel() : r(0), g(0), b(0) {}
		pixel(int r, int g, int b) : r(r), g(g), b(b) {}
		int r, g, b;
	};

	//a little struct which is supposed to make the work with the png-images easier by converting them into an 
	//array in the beginning and back-converting them after the job is done.
	struct image {

		//making an instance of our image-class by telling the height and width
		image(int w, int h);

		//making an instance of our image-class by naming the image
		image(const std::string &filename);

		~image();

		//converts the in data stored pixel-information into a real png-image
		void save(const std::string &filename);

		//these operators make the access to the data-array more intuitive
		pixel& operator()(int y, int x) { return data[y * w + x]; } 
		pixel& operator()(int y, int x) const { return data[y * w + x]; }

		//width and height of the image
		int w, h; 

		//holds the information of each pixel "in a line" to make the access easier. Later, the data will be converted into a real png-image
		pixel *data; 
	};
};

#endif //_MY_IMAGE_H_
