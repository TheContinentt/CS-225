#include <cstdlib>
#include <cmath>
#include <iostream>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
using namespace cs225;

// sets up the output image
PNG* setupOutput(unsigned w, unsigned h) {
    PNG* image = new PNG(w, h);
    return image;
}

// Returns my favorite color
HSLAPixel* myFavoriteColor(double saturation) {
    static HSLAPixel pixel(60, saturation, 0.5);
    return &pixel;
}

void sketchify(std::string inputFile, std::string outputFile) {
    // Load in.png
    PNG* original = new PNG();
//cout << "Reached line 23" << endl;
    original->readFromFile(inputFile);
    unsigned width = original->width();
    unsigned height = original->height();
//cout << "Reached line 27" << endl;
    // Create out.png
    PNG* output; //= new PNG();
    output = setupOutput(width, height);
//cout << "Reached line 31" << endl;
    // Load our favorite color to color the outline
    HSLAPixel* myPixel = myFavoriteColor(0.5);
//cout << "Reached line 34" << endl;
    // Go over the whole image, and if a pixel differs from that to its upper
    // left, color it my favorite color in the output
    for (unsigned y = 1; y < height; y++) {
        for (unsigned x = 1; x < width; x++) {
            // Calculate the pixel difference
		//cout << height << endl;
            HSLAPixel* prev = original->getPixel(x - 1, y - 1);
            HSLAPixel* curr = original->getPixel(x, y);
            double diff = std::fabs(curr->h - prev->h);
		//cout << "Reached line 44" << endl;
		//cout << diff << endl;
		//cout << height << endl;
		//cout << width << endl;
		//cout << x << endl;
		//cout << y << endl;
            // If the pixel is an edge pixel,
            // color the output pixel with my favorite color
            HSLAPixel* currOutPixel = output->getPixel(x, y);
            if (diff > 20) {
                currOutPixel->l = myPixel->l;
		currOutPixel->s = myPixel->s;
		currOutPixel->h = myPixel->h;
		/*cout << currOutPixel->l << endl;
		cout << currOutPixel->s << endl;
		cout << currOutPixel->h << endl;*/
			//cout << "00000000000000000000000" << currOutPixel->h << endl;
            }
        }
    }
//cout << "Reached line 53" << endl;
    // Save the output file
    output->writeToFile(outputFile);////////////
	/*PNG A;
	A.readFromFile(outputFile);
	for (unsigned y = 1; y < A.height(); y++) {
        for (unsigned x = 1; x < A.width(); x++) {
	HSLAPixel *pixel = A.getPixel(x, y);
	cout << pixel->l << endl;
		cout << pixel->s << endl;
		cout << pixel->h << endl;}
}*/
//cout << "Reached line 56" << endl;
    // Clean up memory
    //delete myPixel;
    delete output;
    delete original;
}
