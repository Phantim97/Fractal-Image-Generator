#pragma once

namespace frctl
{

	class Mandelbrot {
	private:
	public:
		Mandelbrot();
		~Mandelbrot();

		static const int MAX_ITERATIONS = 1000; //rendering quality

		static int getIterations(double x, double y); //no instance varuables needed
		
	};

}