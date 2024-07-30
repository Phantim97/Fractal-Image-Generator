#include "ZoomList.h"

namespace frctl
{
	ZoomList::ZoomList(int width, int height)
	{
		this->m_height = height;
		this->m_width = width;
	}

	void ZoomList::add(const Zoom& zoom)
	{
		zooms.push_back(zoom);


		m_xCenter += (zoom.x - m_width / 2) * m_scale;
		m_yCenter += -(zoom.y - m_height / 2) * m_scale; //- for GIMP coordinate system

		m_scale *= zoom.scale;
	}

	std::pair<double, double> ZoomList::do_zoom(int x, int y)
	{
		double xFractal = (x - m_width / 2) *m_scale + m_xCenter;
		double yFractal = (y - m_height / 2) *m_scale + m_yCenter;

		return std::pair<double, double>(xFractal, yFractal);
	}
}