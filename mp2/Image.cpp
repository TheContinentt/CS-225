#include "Image.h"
#include "cs225/PNG.h"
#include <string>
#include "cs225/HSLAPixel.h"
#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;
using namespace cs225;

void Image::lighten()
{
	//Image A;
	for (unsigned int i = 0; i < height(); i++)
	{
		for (unsigned int j = 0; j < width(); j++)
		{
			HSLAPixel *pixel = getPixel(j, i);
			if (pixel->l > 0.9)
			{
				pixel->l = 1;
			}
			else
				pixel->l = pixel->l + 0.1;
		}
	}
}
void Image::lighten(double amount)
{
	//Image A;
	for (unsigned int i = 0; i < height(); i++)
	{
		for (unsigned int j = 0; j < width(); j++)
		{
			HSLAPixel *pixel = getPixel(j, i);
			if (pixel->l + amount >= 1)
			{
				pixel->l = 1;
			}
			else
				pixel->l = pixel->l + amount;
		}
	}
}
void Image::darken()
{
	//Image A;
	for (unsigned int i = 0; i < height(); i++)
	{
		for (unsigned int j = 0; j < width(); j++)
		{
			HSLAPixel *pixel = getPixel(j, i);
			if (pixel->l < 0.1)
			{
				pixel->l = 0;
			}
			else
				pixel->l = pixel->l - 0.1;
		}
	}
}
void Image::darken(double amount)
{
	//Image A;
	for (unsigned int i = 0; i < height(); i++)
	{
		for (unsigned int j = 0; j < width(); j++)
		{
			HSLAPixel *pixel = getPixel(j, i);
			if (pixel->l - amount <= 0)
			{
				pixel->l = 0;
			}
			else
				pixel->l = pixel->l - amount;
		}
	}
}
void Image::saturate()
{
	//Image A;
	for (unsigned int i = 0; i < height(); i++)
	{
		for (unsigned int j = 0; j < width(); j++)
		{
			HSLAPixel *pixel = getPixel(j, i);
			if (pixel->s + 0.1 >= 1)
			{
				pixel->s = 1;
			}
			else
				pixel->s = pixel->s + 0.1;
		}
	}
}
void Image::saturate(double amount)
{
	//Image A;
	for (unsigned int i = 0; i < height(); i++)
	{
		for (unsigned int j = 0; j < width(); j++)
		{
			HSLAPixel *pixel = getPixel(j, i);
			if (pixel->s + amount >= 1)
			{
				pixel->s = 1;
			}
			else
				pixel->s = pixel->s + amount;
		}
	}
}
void Image::desaturate()
{
	//Image A;
	for (unsigned int i = 0; i < height(); i++)
	{
		for (unsigned int j = 0; j < width(); j++)
		{
			HSLAPixel *pixel = getPixel(j, i);
			if (pixel->s - 0.1 <= 0)
			{
				pixel->s = 0;
			}
			else
				pixel->s = pixel->s - 0.1;
		}
	}
}
void Image::desaturate(double amount)
{
	//Image A;
	for (unsigned int i = 0; i < height(); i++)
	{
		for (unsigned int j = 0; j < width(); j++)
		{
			HSLAPixel *pixel = getPixel(j, i);
			if (pixel->s - amount <= 0)
			{
				pixel->s = 0;
			}
			else
				pixel->s = pixel->s - amount;
		}
	}
}
void Image::grayscale()
{
	//Image A;
	for (unsigned int i = 0; i < height(); i++)
	{
		for (unsigned int j = 0; j < width(); j++)
		{
			HSLAPixel *pixel = getPixel(j, i);
			pixel->s = 0;
		}
	}
}
void Image::rotateColor(double degrees)
{
	//Image A;
	for (unsigned int i = 0; i < height(); i++)
	{
		for (unsigned int j = 0; j < width(); j++)
		{
			HSLAPixel *pixel = getPixel(j, i);
			if (pixel->h + degrees >= 360)
			{
				pixel->h = pixel->h + degrees - 360;
			}
			else if (pixel->h + degrees <= 0)
			{
				pixel->h = pixel->h + degrees + 360;
			}
			else
			{
				pixel->h = pixel->h + degrees;
			}
		}
	}
}
void Image::illinify()
{
	//Image A;
	for (unsigned int i = 0; i < height(); i++)
	{
		for (unsigned int j = 0; j < width(); j++)
		{
			HSLAPixel *pixel = getPixel(j, i);
			if (113.5 <= pixel->h && pixel->h <= 293.5)
			{
				pixel->h = 216;
			}
			else
			{
				pixel->h = 11;
			}
		}
	}
}
void Image::scale(double factor)
{
	unsigned int newwidth = factor * width();
	unsigned int newheight = factor * height();
	PNG *A = new PNG(width(), height());
	for (unsigned int i = 0; i < height(); i++)
	{
		for(unsigned int j = 0; j < width(); j++)
		{
			HSLAPixel *newp = A->getPixel(j, i);
			HSLAPixel *oldp = getPixel(j, i);
			newp->l = oldp->l;
			newp->h = oldp->h;
			newp->s = oldp->s;
			newp->a = oldp->a;
		}
	}
	this->resize(newwidth, newheight);
	for (unsigned int i = 0; i < newheight; i++)
	{
		for(unsigned int j = 0; j < newwidth; j++)
		{
			HSLAPixel *newp = this->getPixel(j, i);
			HSLAPixel *oldp = A->getPixel(j/factor, i/factor);
			newp->l = oldp->l;
			newp->h = oldp->h;
			newp->s = oldp->s;
			newp->a = oldp->a;
		}
	}
	delete A;
}
void Image::scale(unsigned w, unsigned h)
{
	float widthfactor = (float)w / (float)width();
	float heightfactor = (float)h / (float)height();
	PNG *A = new PNG(width(), height());
	for (unsigned int i = 0; i < height(); i++)
	{
		for(unsigned int j = 0; j < width(); j++)
		{
			HSLAPixel *newp = A->getPixel(j, i);
			HSLAPixel *oldp = getPixel(j, i);
			newp->l = oldp->l;
			newp->h = oldp->h;
			newp->s = oldp->s;
			newp->a = oldp->a;
		}
	}
	this->resize(w, h);
	for (unsigned int i = 0; i < h; i++)
	{
		for(unsigned int j = 0; j < w; j++)
		{
			HSLAPixel *newp = this->getPixel(j, i);
			HSLAPixel *oldp = A->getPixel(j/widthfactor, i/heightfactor);
			newp->l = oldp->l;
			newp->h = oldp->h;
			newp->s = oldp->s;
			newp->a = oldp->a;
		}
	}
	delete A;
}
