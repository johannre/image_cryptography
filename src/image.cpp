#include "image.h"

my_image::image::image(int w, int h) : data(nullptr), w(w), h(h) { data = new pixel[w * h]; }

my_image::image::image(const std::string &filename) {

	png::image<png::rgb_pixel> image(filename);
	w = image.get_width();
	h = image.get_height();

	//writing all png-image-information into the data-array
	data = new pixel[w * h];
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; ++x) {
			data[y * w + x].r = image[y][x].red;
			data[y * w + x].g = image[y][x].green;
			data[y * w + x].b = image[y][x].blue;
		}
}

my_image::image::~image() {
	if (data != nullptr) delete [] data;
}

void my_image::image::save(const std::string &filename) {

	png::image<png::rgb_pixel> image(w, h);

	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; ++x) {
			image[y][x].red = (char)data[y * w + x].r;
			image[y][x].green = (char)data[y * w + x].g;
			image[y][x].blue = (char)data[y * w+ x].b;
		}

	for (int y = 0; y < h; ++y) 
		for (int x = 0; x < w; ++x) {
			if (image[y][x].red > 255) image[y][x].red = 255;
			if (image[y][x].green > 255) image[y][x].green = 255;
			if (image[y][x].blue > 255) image[y][x].blue = 255;
		}

	image.write(filename);

}
