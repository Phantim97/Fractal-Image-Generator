#ifndef PRESETS_H
#define PRESETS_H

enum ZoomPresets
{
	ZOOM_1
};

enum ColorPresets
{
	COLOR_1
};

void preset_setup(frctl::FractalCreator &fractal_creator, ZoomPresets zoom, ColorPresets color);

#endif