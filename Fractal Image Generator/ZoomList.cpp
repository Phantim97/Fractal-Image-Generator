#include "ZoomList.h"

namespace frctl
{
	ZoomList::ZoomList(const int width, const int height)
	{
		height_ = height;
		width_ = width;
	}

	void ZoomList::add(const Zoom& zoom)
	{
		zooms_.push_back(zoom);

		x_center_ += (zoom.x - width_ / 2) * scale_;
		y_center_ += -(zoom.y - height_ / 2) * scale_; //- for GIMP coordinate system

		scale_ *= zoom.scale;
	}

	std::pair<double, double> ZoomList::do_zoom(const int x, const int y)
	{
		double x_fractal = (x - width_ / 2.0) * scale_ + x_center_;
		double y_fractal = (y - height_ / 2.0) * scale_ + y_center_;

		return {x_fractal, y_fractal};
	}
}