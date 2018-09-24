#ifndef STICKERSHEET_H
#define STICKERSHEET_H

#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

class StickerSheet
{
public:
	StickerSheet(const Image &picture, unsigned max);
	~StickerSheet();
	StickerSheet(const StickerSheet &other);
	const StickerSheet & operator = (const StickerSheet &other);
	void changeMaxStickers(unsigned max);
	int addSticker(Image &sticker, unsigned x, unsigned y);
	bool translate(unsigned index, unsigned x, unsigned y);
	void removeSticker(unsigned index);
	Image *getSticker(unsigned index) const;
	Image render() const;
private:
	Image A;
	unsigned int index_;
	unsigned int *x_;
	unsigned int *y_;
	Image *array_;
	unsigned int max_;
	unsigned int*check;
};

#endif
