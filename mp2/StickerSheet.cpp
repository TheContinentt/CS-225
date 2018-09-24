#include "StickerSheet.h"
#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

using namespace cs225;
using namespace std;

StickerSheet::StickerSheet(const Image &picture, unsigned max)
{
	array_ = new Image[max + 1];
	A = picture;
	x_ = new unsigned int[max + 1];
	y_ = new unsigned int[max + 1];
	check = new unsigned int[max + 1];
	index_ = 0;
	max_ = max + 1;
	for (unsigned int i = 0; i < max + 1; i++)
	{
		/*x_[i] = -1;
		y_[i] = -1;*/
		check[i] = 0;
	}
}
StickerSheet::~StickerSheet()
{
	delete [] array_;
	delete [] x_;
	delete [] y_;
	delete [] check;
	array_ = NULL;
	x_ = NULL;
	y_ = NULL;
	check = NULL;
}
StickerSheet::StickerSheet(const StickerSheet &other)
{
	/*delete [] array_;
	delete [] x_;
	delete [] y_;*/
	A = other.A;
	max_ = other.max_;
	index_ = other.index_;
	array_ = new Image[max_];
	for (unsigned int i = 0; i < max_; i++)
	{
		array_[i] = other.array_[i];
	}
	x_ = new unsigned int[max_];
	for (unsigned int i = 0; i < max_; i++)
	{
		x_[i] = other.x_[i];
	}
	y_ = new unsigned int[max_];
	for (unsigned int i = 0; i < max_; i++)
	{
		y_[i] = other.y_[i];
	}
	check = new unsigned int[max_];
	for (unsigned int i = 0; i < max_; i++)
	{
		check[i] = other.check[i];
	}
}
const StickerSheet & StickerSheet::operator = (const StickerSheet &other)
{
	this->A = other.A;
	this->max_ = other.max_;
	this->index_ = other.index_;
	this->array_ = new Image[max_];
	for (unsigned int i = 0; i < max_; i++)
	{
		array_[i] = other.array_[i];
	}
	this->x_ = new unsigned int[max_];
	for (unsigned int i = 0; i < max_; i++)
	{
		x_[i] = other.x_[i];
	}
	this->y_ = new unsigned int[max_];
	for (unsigned int i = 0; i < max_; i++)
	{
		y_[i] = other.y_[i];
	}
	this->check = new unsigned int[max_];
	for (unsigned int i = 0; i < max_; i++)
	{
		check[i] = other.check[i];
	}
	return *this;
}
void StickerSheet::changeMaxStickers(unsigned max)
{
	Image *arr = new Image[max_];
	unsigned int *xx_ = new unsigned int[max_];
	unsigned int *yy_ = new unsigned int[max_];
	unsigned int *cc = new unsigned int[max_];
	for (unsigned int i = 0; i < max_; i++)
	{
		arr[i] = array_[i];
		xx_[i] = x_[i];
		yy_[i] = y_[i];
		cc[i] = check[i];
	}
	delete [] array_;
	delete [] x_;
	delete [] y_;
	delete [] check;
	array_ = NULL;
	x_ = NULL;
	y_ = NULL;
	check = NULL;
	array_ = new Image[max + 1];
	x_ = new unsigned int[max + 1];
	y_ = new unsigned int[max + 1];
	check = new unsigned int[max + 1];
	if (max + 1 < max_)
	{
		for (unsigned int i = 0; i < max; i++)
		{
			array_[i] = arr[i];
			x_[i] = xx_[i];
			y_[i] = yy_[i];
			check[i] = cc[i];
		}
		check[max + 1] = 0;
	}
	else
	{
		for (unsigned int i = 0; i < max_ ; i++)
		{
			array_[i] = arr[i];
			x_[i] = xx_[i];
			y_[i] = yy_[i];
			check[i] = cc[i];
		}
		for (unsigned int i = max_; i < max + 1; i++)
		{
			check[i] = 0;
		}
	}
	max_ = max + 1;
	delete [] arr;
	delete [] xx_;
	delete [] yy_;
	delete [] cc;
	arr = NULL;
	xx_ = NULL;
	yy_ = NULL;
	cc = NULL;
	unsigned int counter = 0;
	while (check[counter] != 0)
	{
		counter++;
	}
	index_ = counter;
}
int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y)
{
	if (index_ >= max_)
		return -1;
	array_[index_] = sticker;
	x_[index_] = x;
	y_[index_] = y;
	check[index_] = 1;
	index_ = index_ + 1;
	unsigned int ret = index_ - 1;
	return ret;
}
bool StickerSheet::translate(unsigned index, unsigned x, unsigned y)
{
	if (check[index] == 0)
		return false;
	x_[index] = x;
	y_[index] = y;
	return true;
}
void StickerSheet::removeSticker(unsigned index)
{
	for (unsigned int i = index; i < max_ - 1; i++)
	{
		array_[i] = array_[i + 1];
		x_[i] = x_[i + 1];
		y_[i] = y_[i + 1];
		check[i] = check[i + 1];
	}
	//array_[max_ - 1] = NULL;
	//delete array_[max_ - 1];
	check[max_ - 1] = 0;
	index_--;
}
Image *StickerSheet::getSticker(unsigned index) const
{
	if (check[index] == 0)
	{
		return NULL;
	}
	Image *r = &array_[index];
	//Image *r = &ret;
	return r;
}
Image StickerSheet::render() const
{
	PNG *ret = new PNG();
	Image *B = new Image();
	Image C = A;
	unsigned int width = A.width();
	unsigned int height = A.height();
	ret->resize(width, height);
	B->resize(width, height);
	for (unsigned int i = 0; i < width; i++)
	{
		for (unsigned int j = 0; j < height; j++)
		{
			HSLAPixel *base = C.getPixel(i, j);
			HSLAPixel *draw = ret->getPixel(i, j);
			draw->l = base->l;
			draw->h = base->h;
			draw->s = base->s;
			draw->a = base->a;
		}
	}
	unsigned int counter = 0;
	while (check[counter] == 1)
	{
		Image temp = array_[counter];
		int startx = x_[counter];
		int starty = y_[counter];
		unsigned int sw = temp.width();
		unsigned int sh = temp.height();
		int flag = 0;
		PNG *ns = new PNG();
		if (sw + startx >= width)
		{	
			ns->resize(sw + startx, height);
			flag++;
		}
		if (sh + starty >= height)
		{
			if (sw +startx >= width)
			{
				ns->resize(sw + startx, sh + starty);
			}
			else
			{
				unsigned int tpp = sh + starty;
				ns->resize(width, tpp);
			}
			flag++;
		}
		/*if (startx < 0)
		{
			ns->resize(width - startx, height);
			flag++;
		}
		if (starty < 0)
		{
			if (startx < 0)
			{
				ns->resize(width - startx, height - starty);
			}
			else
			{
				ns->resize(width, height - starty);
			}
			flag++;
		}*/
		if (flag != 0)
		{
			for (unsigned int i = 0; i < width; i++)
			{
				for (unsigned int j = 0; j < height; j++)
				{
					HSLAPixel *base = ret->getPixel(i, j);
					HSLAPixel *draw = ns->getPixel(i, j);
					draw->l = base->l;
					draw->h = base->h;
					draw->s = base->s;
					draw->a = base->a;
				}
			}
			ret->resize(ns->width(), ns->height());
			for (unsigned int i = 0; i < ns->width(); i++)
			{
				for (unsigned int j = 0; j < ns->height(); j++)
				{
					HSLAPixel *base = ns->getPixel(i, j);
					HSLAPixel *draw = ret->getPixel(i, j);
					draw->l = base->l;
					draw->h = base->h;
					draw->s = base->s;
					draw->a = base->a;
				}
			}
		}
		delete ns;
		for (unsigned int i = startx; i < startx + sw; i++)
		{
			for (unsigned int j = starty; j < starty + sh; j++)
			{
				HSLAPixel *layer = temp.getPixel(i-startx, j-starty);
				HSLAPixel *draw = ret->getPixel(i, j);
				if (layer->a == 0)
					continue;
				draw->l = layer->l;
				draw->h = layer->h;
				draw->s = layer->s;
				draw->a = layer->a;
			}
		}
		counter++;
	}
	B->resize(ret->width(), ret->height());
	for (unsigned int i = 0; i < ret->width(); i++)
	{
		for (unsigned int j = 0; j < ret->height(); j++)
		{
			HSLAPixel *base = ret->getPixel(i, j);
			HSLAPixel *draw = B->getPixel(i, j);
			draw->l = base->l;
			draw->h = base->h;
			draw->s = base->s;
			draw->a = base->a;
		}
	}
	C.resize(ret->width(), ret->height());
	for (unsigned int i = 0; i < ret->width(); i++)
	{
		for (unsigned int j = 0; j < ret->height(); j++)
		{
			HSLAPixel *base = ret->getPixel(i, j);
			HSLAPixel *draw = C.getPixel(i, j);
			draw->l = base->l;
			draw->h = base->h;
			draw->s = base->s;
			draw->a = base->a;
		}
	}
	delete ret;
	ret = NULL;
	delete B;
	return C;
}
