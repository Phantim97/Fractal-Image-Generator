#include <iostream>
#include "FractalCreator.h"
#include "RGB.h"
#include "Zoom.h"
#include "Presets.h"

int main()
{
	frctl::FractalCreator fractal_creator(800, 600);

#ifdef _WIN32
	const std::string clear = "cls";
#else
	const std::string clear = "clear";
#endif

	constexpr int preset_mode = 1;
	constexpr int test_mode = 2;

	int mode_select = 0;

	std::cout << "Select an option 1) Presets. 2) Test : ";
	do
	{
		std::cin >> mode_select;
		if (mode_select != preset_mode && mode_select != test_mode)
		{
			std::cerr << "Invalid Input.\n";
		}
	} while (mode_select != preset_mode && mode_select != test_mode);

	if (mode_select == preset_mode)
	{
		preset_setup(fractal_creator, ZOOM_1, COLOR_1);
	}
	else if (mode_select == test_mode)
	{
		std::cout << "Coloring Pixels...\n";

		fractal_creator.add_range(0.0, frctl::RGB(0, 0, 0));
		fractal_creator.add_range(0.05, frctl::RGB(5, 0, 0));
		fractal_creator.add_range(0.2, frctl::RGB(20, 0, 0));
		fractal_creator.add_range(0.3, frctl::RGB(137, 20, 0));
		fractal_creator.add_range(1.0, frctl::RGB(255, 0, 0));

		system(clear.c_str());
		std::cout << "Zooming into correct coordinates...\n";

		//add zooms_ to a point on the Fractal Image

		//Zone 1:
		fractal_creator.add_zoom(frctl::Zoom(295, 202, 0.1));
		fractal_creator.add_zoom(frctl::Zoom(312, 304, 0.1));
		fractal_creator.add_zoom(frctl::Zoom(581, 357, 0.1));
		fractal_creator.add_zoom(frctl::Zoom(381, 285, 0.1));
		//fractal_creator.add_zoom(frctl::Zoom(210, 210, 0.1));

		//Zone 2:
		//fractal_creator.add_zoom(frctl::Zoom(452, 300, 0.1));
	}

	system(clear.c_str());
	std::cout << "Rendering image...\n";

	fractal_creator.run("test.bmp");

	system(clear.c_str());
	std::cout << "Finished.\n";
#ifdef _WIN32
	system("pause");
	system("test.bmp");
#elif __APPLE__
	std::cin.get();
	system("open test.bmp");
#else
	std::cin.get();
	system("gimp test.bmp"); //GIMP dependency
#endif

	return 0;
}