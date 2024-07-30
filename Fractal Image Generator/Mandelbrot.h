#ifndef MANDELBROT_H
#define MANDELBROT_H

namespace frctl
{
	struct Mandelbrot
	{
		static constexpr int MAX_ITERATIONS = 1000; //rendering quality
		static int getIterations(double x, double y); //no instance varuables needed
	};
}

#endif