#include <iostream>
#include "FractalCreator.h"
#include "RGB.h"
#include "Zoom.h"
#include "Presets.h"

int main()
{
	frctl::FractalCreator fractal_creator(800, 600);

	int modeSelect = 0;
	std::cout << "Select an option 1) Presets. 2) Test : ";
	do
	{
		std::cin >> modeSelect;
	} while (modeSelect != 1 && modeSelect != 2);

	if (modeSelect == 1)
	{
		preset_setup(fractal_creator, ZOOM_1, COLOR_1);
	}
	else if (modeSelect == 2)
	{
		std::cout << "Coloring Pixels...\n";

		fractal_creator.add_range(0.0, frctl::RGB(0, 0, 0));
		//fractal_creator.add_range(0.05, frctl::RGB(0, 0, 255));
		//fractal_creator.add_range(0.2, frctl::RGB(0, 255, 255));
		fractal_creator.add_range(0.3, frctl::RGB(137, 137, 0));
		fractal_creator.add_range(1.0, frctl::RGB(255, 0, 0));

		system("cls");
		std::cout << "Zooming into correct coordinates...\n";

		//add zooms to a point on the Fractal Image

		//Zone 1:
		//fractal_creator.add_zoom(frctl::Zoom(295, 202, 0.1));
		//fractal_creator.add_zoom(frctl::Zoom(312, 304, 0.1));
		//fractal_creator.add_zoom(frctl::Zoom(581, 357, 0.1));
		//fractal_creator.add_zoom(frctl::Zoom(381, 285, 0.1));
		//fractal_creator.add_zoom(frctl::Zoom(210, 210, 0.1));

		//Zone 2:
		fractal_creator.add_zoom(frctl::Zoom(452, 300, 0.1));
	}

	system("cls");
	std::cout << "Rendering image...\n";

	fractal_creator.run("test.bmp");

	system("cls");
	std::cout << "Finished.\n";
	system("pause");
	system("test.bmp");
	return 0;
}