#include "FractalCreator.h"

namespace frctl
{
	void FractalCreator::run(const std::string& name)
	{
		_calculate_iteration();
		_calculate_total_iterations();
		_calculate_range_totals();
		_draw_fractal();
		_write_bitmap(name);
	}

	void FractalCreator::add_range(const double range_end, const RGB& rgb)
	{
		ranges_.push_back(static_cast<int>(range_end * Mandelbrot::MAX_ITERATIONS));
		colors_.push_back(rgb);

		//detects if ranges were added
		if (got_first_range_)
		{
			range_totals.push_back(0);
		}

		got_first_range_ = true;
	}

	FractalCreator::FractalCreator(const int width, const int height) : width_(width), height_(height),
	     histogram_(new int[frctl::Mandelbrot::MAX_ITERATIONS]{0 }), fractal_(new int[width_ * height_]{0 }),
		 bitmap_(width_, height_), zoom_list_(width_, height_)
	{
		add_zoom(frctl::Zoom(width_ / 2, height_ / 2, 4.0 / width_)); //initial zoom
	}

	int FractalCreator::get_range(int iterations) const
	{
		int range = 0;

		for (int i = 1; i < ranges_.size(); i++)
		{
			range = i;

			if (ranges_[i] > iterations)
			{
				break;
			}
		}

		range--;

		//bounds checking
		assert(range > -1);
		assert(range < ranges_.size());

		return range;
	}

	void FractalCreator::_calculate_iteration()
	{
		#ifdef _OPENMP
		omp_set_dynamic(0);
		omp_set_num_threads(omp_get_num_procs());
		#endif

		#pragma omp parallel for
		for (int y = 0; y < height_; y++)
		{
			for (int x = 0; x < width_; x++)
			{
				std::pair<double, double> coords = zoom_list_.do_zoom(x, y);

				const int iterations = frctl::Mandelbrot::get_iterations(coords.first, coords.second);

				fractal_[y * width_ + x] = iterations;

				//Eliminate the maximum
				if (iterations != frctl::Mandelbrot::MAX_ITERATIONS)
				{
					histogram_[iterations]++;
				}

			}
		}
	}

	void FractalCreator::_calculate_range_totals()
	{
		int range_index = 0;
		#ifdef _OPENMP
		omp_set_dynamic(0);
		omp_set_num_threads(omp_get_num_procs());
		#endif
		#pragma omp parallel for
		for (int i = 0; i < frctl::Mandelbrot::MAX_ITERATIONS; i++)
		{
			int pixels = histogram_[i];

			if (i >= ranges_[range_index + 1])
			{
				range_index++;
			}

			range_totals[range_index] += pixels;
		}
	}

	void FractalCreator::_calculate_total_iterations()
	{
		for (int i = 0; i < frctl::Mandelbrot::MAX_ITERATIONS; i++)
		{
			total_ += histogram_[i];
		}
	}

	void FractalCreator::_draw_fractal()
	{
		#ifdef _OPENMP
		omp_set_dynamic(0);
		omp_set_num_threads(omp_get_num_procs());
		#endif
		//Drawing loop
		#pragma omp parallel for
		for (int y = 0; y < height_; y++)
		{
			for (int x = 0; x < width_; x++)
			{
				//color range
				int iterations = fractal_[y * width_ + x];

				int range = get_range(iterations);
				int range_total = range_totals[range];
				int range_start = ranges_[range];

				RGB& start_color = colors_[range];
				RGB& end_color = colors_[range + 1]; //range is 0 based and range is 0 to 1 (hue)
				RGB color_diff = end_color - start_color;

				uint8_t red = 0;
				uint8_t green = 0;
				uint8_t blue = 0;
				
				//Makes the image sharper
				if (iterations != frctl::Mandelbrot::MAX_ITERATIONS)
				{
					int total_pixels = 0;

					for (int i = range_start; i <= iterations; i++)
					{
						total_pixels += histogram_[i]; //histogram gives total pixels
					}

					red = start_color.r + color_diff.r * (double)total_pixels / range_total;
					green = start_color.g + color_diff.g * (double)total_pixels / range_total;
					blue = start_color.b + color_diff.b * (double)total_pixels / range_total;

				}

				bitmap_.set_pixel(x, y, red, green, blue); // color-state for pixels
			}
		}
	}

	void FractalCreator::add_zoom(const frctl::Zoom& zoom)
	{
		zoom_list_.add(zoom);
	}

	void FractalCreator::_write_bitmap(const std::string& name)
	{
		bitmap_.write(name);
	}
}