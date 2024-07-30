#include <iostream>
#include "FractalCreator.h"
#include "RGB.h"
#include "Zoom.h"
#include "Presets.h"

static void color_preset1(frctl::FractalCreator &fractal_creator)
{
	fractal_creator.add_range(0.0, frctl::RGB(0, 0, 0));
	fractal_creator.add_range(0.05, frctl::RGB(0, 0, 255));
	fractal_creator.add_range(0.2, frctl::RGB(0, 255, 255));
	//fractal_creator.add_range(0.3, frctl::RGB(137, 137, 0)); //Optional Range
	fractal_creator.add_range(1.0, frctl::RGB(0, 255, 255));
}

static void zoom_preset1(frctl::FractalCreator &fractal_creator)
{
	fractal_creator.add_zoom(frctl::Zoom(295, 202, 0.1));
	fractal_creator.add_zoom(frctl::Zoom(312, 304, 0.1));
	fractal_creator.add_zoom(frctl::Zoom(581, 357, 0.1));
}

void preset_setup(frctl::FractalCreator &fractal_creator, ZoomPresets zoom, ColorPresets color)
{
	if (color == COLOR_1)
	{
		color_preset1(fractal_creator);
	}

	if (zoom == ZOOM_1)
	{
		zoom_preset1(fractal_creator);
	}
}