#ifndef FRACTAL_CREATOR_H
#define FRACTAL_CREATOR_H

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

namespace frctl
{
	class FractalCreator
	{
	private:
		int width_ = 0;
		int height_ = 0;
		int total_ = 0;
		std::unique_ptr<int[]> histogram_ = nullptr; // +1 to count 0
		std::unique_ptr<int[]> fractal_ = nullptr; //Store iterations
		frctl::Bitmap bitmap_;
		frctl::ZoomList zoom_list_;

		std::vector<int> ranges_;
		std::vector<RGB> colors_;
		std::vector<int> range_totals;

		bool got_first_range_ = false;

		void _calculate_iteration();
		void _calculate_total_iterations();
		void _calculate_range_totals();
		void _draw_fractal();
		void _write_bitmap(const std::string& name);
		[[nodiscard]] int get_range(int iterations) const;

	public:
		FractalCreator(int width, int height);
		~FractalCreator() = default;
		void add_range(double range_end, const RGB& rgb);
		void add_zoom(const frctl::Zoom& zoom);
		void run(const std::string& name);
	};
}

#endif