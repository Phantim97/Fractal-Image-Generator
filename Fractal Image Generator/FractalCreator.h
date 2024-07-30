#pragma once

#include <cassert>
#include <cstdint>
#include <string>
#include <memory>
#include <vector>
#ifdef _OPENMP
#include <omp.h>
#endif
#include "Zoom.h"
#include "ZoomList.h"
#include "Mandelbrot.h"
#include "Bitmap.h"
#include "RGB.h"

namespace frctl {
	class FractalCreator {
	private:
		int m_width{ 0 };
		int m_height{ 0 };
		int m_total{ 0 };
		std::unique_ptr<int[]> m_histogram; // +1 to count 0
		std::unique_ptr<int[]> m_fractal; //Store iterations
		frctl::Bitmap m_bitmap;
		frctl::ZoomList m_zoomList;

		std::vector<int> m_ranges;
		std::vector<RGB> m_colors;
		std::vector<int> m_rangeTotals;

		bool m_bGotFirstRange{ false };

	private:

		void calculateIteration();
		void calculateTotalIterations();
		void calculateRangeTotals();
		void drawFractal();	
		void writeBitmap(std::string name);
		int getRange(int iterations) const;

	public:
		
		FractalCreator(int width, int hieght);
		~FractalCreator();
		void addRange(double rangeEnd, const RGB& rgb);
		void addZoom(const frctl::Zoom& zoom);
		void run(std::string name);
		
	};

}