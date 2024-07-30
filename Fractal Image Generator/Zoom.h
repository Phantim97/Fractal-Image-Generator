#ifndef ZOOM_H
#define ZOOM_H

namespace frctl
{
	struct Zoom
	{
		int x = 0;
		int y = 0;
		double scale = 0.0;

		Zoom(const int x_coord, const int y_coord, const double scale_factor)
		{
			x = x_coord;
			y = y_coord;
			scale = scale_factor;
		}
	};
}

#endif