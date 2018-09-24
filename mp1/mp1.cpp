#include <string>
#include "mp1.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <iostream>

 using namespace cs225;

void rotate(std::string inputFile, std::string outputFile) {
	PNG A;
	A.readFromFile(inputFile);
	//B.readFromFile(inputFile);
	double th, ts, tl, ta, t, tt;
	//cout << A.height() << endl;
	//cout << A.width() << endl;
	for (unsigned x = 0; x < A.width(); x++) 
	{
		for (unsigned y = 0; y < A.height()/2; y++) 
		{
			HSLAPixel *pixel = A.getPixel(x, y);
			//HSLAPixel *pixel = A.getPixel(A.width() - x, A.height() - y);
			th = pixel->h;
			ts = pixel->s;
			tl = pixel->l;
			ta = pixel->a;
			t = A.width() - x - 1;
			tt = A.height() - y - 1;
			HSLAPixel *pixell = A.getPixel(t, tt);
			pixel->h = pixell->h;
			pixel->s = pixell->s;
			pixel->l = pixell->l;
			pixel->a = pixell->a;
			pixell->h = th;
			pixell->s = ts;
			pixell->l = tl;
			pixell->a = ta;
		}
	}
	if (A.height() % 2 == 1)
	{
		unsigned h = (A.height()-1)/2;
		//cout << h << endl;
		for (unsigned x = 0; x < A.width()/2; x++)
		{
			HSLAPixel *p = A.getPixel(x, h);
			th = p->h;
			ts = p->s;
			tl = p->l;
			ta = p->a;
			t = A.width() - x - 1;
			HSLAPixel *pp = A.getPixel(t, h);
			p->h = pp->h;
			p->s = pp->s;
			p->l = pp->l;
			p->a = pp->a;
			pp->h = th;
			pp->s = ts;
			pp->l = tl;
			pp->a = ta;
		}
	}
	A.writeToFile(outputFile);
	/*for (unsigned x = 0; x < A.width(); x++) 
	{
		for (unsigned y = 0; y < A.height(); y++) 
		{
			HSLAPixel *pixel = A.getPixel(x, y);	
			pixel->l = 0;
		}
	}
	A.writeToFile(outputFile);*/

}
