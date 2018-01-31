#include <iostream>
#include "FractalCreator.h"
#include "RGB.h"
#include "Zoom.h"

void colorPreset1(frctl::FractalCreator &fractalCreator)
{
	fractalCreator.addRange(0.0, frctl::RGB(0, 0, 0));
	fractalCreator.addRange(0.05, frctl::RGB(0, 0, 255));
	fractalCreator.addRange(0.2, frctl::RGB(0, 255, 255));
	//fractalCreator.addRange(0.3, frctl::RGB(137, 137, 0));
	fractalCreator.addRange(1.0, frctl::RGB(0, 255, 255));
}

void zoomPreset1(frctl::FractalCreator &fractalCreator)
{
	fractalCreator.addZoom(frctl::Zoom(295, 202, 0.1));
	fractalCreator.addZoom(frctl::Zoom(312, 304, 0.1));
	fractalCreator.addZoom(frctl::Zoom(581, 357, 0.1));
}

void presetSetup(frctl::FractalCreator &fractalCreator)
{
	int cpresetNumber;
	std::cout << "Select a color preset: ";
	do {
		std::cin >> cpresetNumber;
	} while (cpresetNumber != 1);

	switch (cpresetNumber)
	{
	case (1):
		colorPreset1(fractalCreator);
		break;
	}

	int zpresetNumber;
	std::cout << "Enter a zoom preset: ";
	do {
		std::cin >> zpresetNumber;
	} while (zpresetNumber != 1);

	switch (zpresetNumber)
	{
		zoomPreset1(fractalCreator);
		break;
	}

}