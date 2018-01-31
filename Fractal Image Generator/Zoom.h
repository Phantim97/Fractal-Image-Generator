#pragma once

namespace frctl
{
	struct Zoom
	{
		int x;
		int y;
		double scale;

		Zoom(int x, int y, double scale)
		{
			this->x = x;
			this->y = y;
			this->scale = scale;
		}

	};
}