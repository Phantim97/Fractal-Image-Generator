#include <complex>
#include "Mandelbrot.h"

namespace frctl
{
	//Mandelbrot Algorithm here
	int Mandelbrot::get_iterations(const double x, const double y)
	{
		std::complex<double> z = 0;
		std::complex<double> c(x, y); //passing in two numbers into this;

		int iterations = 0;

		while (iterations < MAX_ITERATIONS)
		{
			z = z * z + c; //Mandelbrot algorithm

			if (abs(z) > 2) //catches numbers not in mandelbrot set (nums approaching infinity)
			{
				break;
			}

			iterations++;

		}

		return iterations;
	}

}