#ifndef HEADFILE_H
#define HEADFILE_H

namespace cs225{
	class HSLAPixel {
      public:
	double h, s, l, a;
	HSLAPixel(double hue, double saturation, double luminance, double alpha);
	HSLAPixel(double hue, double saturation, double luminance);
	HSLAPixel();	}
		;}
	

#endif
