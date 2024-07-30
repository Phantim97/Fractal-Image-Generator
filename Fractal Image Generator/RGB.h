#ifndef RGB_H
#define RGB_H

namespace frctl
{
	struct RGB
	{
		double r = 0.0;
		double g = 0.0;
		double b = 0.0;

		RGB(double r, double g, double b);
	};

	RGB operator-(const RGB& first, const RGB& second);
}

#endif