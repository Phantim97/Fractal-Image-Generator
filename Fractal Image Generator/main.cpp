#include <iostream>
#include "FractalCreator.h"
#include "RGB.h"
#include "Zoom.h"
#include "Presets.h"

int main()
{
	frctl::FractalCreator fractalCreator(800, 600);

	int modeSelect;
	std::cout << "Select an option 1) Presets. 2) Test : ";
	do {
		std::cin >> modeSelect;
	} while (modeSelect != 1 && modeSelect != 2);

	if (modeSelect == 1)
	{
		presetSetup(fractalCreator);
	}
	else if (modeSelect == 2)
	{
		std::cout << "Coloring Pixels...\n";

		fractalCreator.addRange(0.0, frctl::RGB(0, 0, 0));
		//fractalCreator.addRange(0.05, frctl::RGB(0, 0, 255));
		//fractalCreator.addRange(0.2, frctl::RGB(0, 255, 255));
		fractalCreator.addRange(0.3, frctl::RGB(137, 137, 0));
		fractalCreator.addRange(1.0, frctl::RGB(255, 0, 0));

		system("cls");
		std::cout << "Zooming into correct coordinates...\n";

		//add zooms to a point on the Fractal Image

		//Zone 1:
		//fractalCreator.addZoom(frctl::Zoom(295, 202, 0.1));
		//fractalCreator.addZoom(frctl::Zoom(312, 304, 0.1));
		//fractalCreator.addZoom(frctl::Zoom(581, 357, 0.1));
		//fractalCreator.addZoom(frctl::Zoom(381, 285, 0.1));
		//fractalCreator.addZoom(frctl::Zoom(210, 210, 0.1));

		//Zone 2:
		fractalCreator.addZoom(frctl::Zoom(452, 300, 0.1));
	}
	system("cls");
	std::cout << "Rendering image...\n";

	fractalCreator.run("test.bmp");

	system("cls");
	std::cout << "Finished.\n";
	system("pause");
	system("test.bmp");
	return 0;
}