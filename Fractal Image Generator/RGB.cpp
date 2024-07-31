#include "RGB.h"

namespace frctl
{
	RGB::RGB(const double r, const double g, const double b) : r(r), g(g), b(b)
	{

	}

	RGB operator-(const RGB& first, const RGB& second)
	{
		return RGB(first.r - second.r, first.g - second.g, first.b - second.b);
	}
}