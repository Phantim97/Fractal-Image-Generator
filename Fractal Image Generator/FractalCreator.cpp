#include "FractalCreator.h"

namespace frctl
{
	void FractalCreator::run(std::string name)
	{
		calculateIteration();
		calculateTotalIterations();
		calculateRangeTotals();
		drawFractal();
		writeBitmap("test.bmp");
	}

	void FractalCreator::addRange(double rangeEnd, const RGB& rgb)
	{
		m_ranges.push_back(rangeEnd*Mandelbrot::MAX_ITERATIONS);
		m_colors.push_back(rgb);

		//detects if ranges were added
		if (m_bGotFirstRange)
		{
			m_rangeTotals.push_back(0);
		}

		m_bGotFirstRange = true; 
	}

	

	FractalCreator::FractalCreator(int width, int height) : m_width(width), m_height(height),
		m_histogram(new int[frctl::Mandelbrot::MAX_ITERATIONS]{ 0 }),
		m_fractal(new int[m_width*m_height]{ 0 }), m_bitmap(m_width, m_height), m_zoomList(m_width, m_height)
	{
		addZoom(frctl::Zoom(m_width / 2, m_height / 2, 4.0 / m_width)); //initial zoom 
	}

	int FractalCreator::getRange(int iterations) const
	{
		int range = 0;

		for (int i = 1; i < m_ranges.size(); i++)
		{
			range = i;

			if (m_ranges[i] > iterations)
			{
				break;
			}
		}

		range--;
		//bounds checking
		assert(range > -1);
		assert(range < m_ranges.size());

		return range;

	}

	FractalCreator::~FractalCreator()
	{
	}

	void FractalCreator::calculateIteration()
	{
		omp_set_dynamic(0);
		omp_set_num_threads(omp_get_num_procs());
		#pragma omp parallel for
		for (int y = 0; y < m_height; y++)
		{
			for (int x = 0; x < m_width; x++)
			{
				std::pair<double, double> coords = m_zoomList.doZoom(x, y);
				//we need a symetrical midpoint, range is from -1 to +1 
				//double xFractal = (x - WIDTH/2 -200 ) * 2.0/HEIGHT; //2.0 used to cast to a double 
				//double yFractal = (y - HEIGHT/2) * 2.0/HEIGHT; //scaling 

				int iterations = frctl::Mandelbrot::getIterations(coords.first, coords.second);

				m_fractal[y*m_width + x] = iterations;

				//elminate the maximum 
				if (iterations != frctl::Mandelbrot::MAX_ITERATIONS)
				{
					m_histogram[iterations]++;
				}

			}
		}
	}

	void FractalCreator::calculateRangeTotals()
	{
		int rangeIndex = 0;
		omp_set_dynamic(0);
		omp_set_num_threads(omp_get_num_procs());
		#pragma omp parallel for
		for (int i = 0; i < frctl::Mandelbrot::MAX_ITERATIONS; i++)
		{
			int pixels = m_histogram[i];

			if (i >= m_ranges[rangeIndex + 1])
			{
				rangeIndex++;
			}

			m_rangeTotals[rangeIndex] += pixels;
		}
	}

	void FractalCreator::calculateTotalIterations()
	{
		for (int i = 0; i < frctl::Mandelbrot::MAX_ITERATIONS; i++)
		{
			m_total += m_histogram[i];
		}
	}

	void FractalCreator::drawFractal()
	{
		omp_set_dynamic(0);
		omp_set_num_threads(omp_get_num_procs());
		//Drawing loop
		#pragma omp parallel for
		for (int y = 0; y < m_height; y++)
		{
			for (int x = 0; x < m_width; x++)
			{

				//color range
				int iterations = m_fractal[y*m_width + x];

				int range = getRange(iterations);
				int rangeTotal = m_rangeTotals[range];
				int rangeStart = m_ranges[range];

				RGB& startColor = m_colors[range];
				RGB& endColor = m_colors[range + 1]; //range is 0 based and range is 0 to 1 (hue)
				RGB& colorDiff = endColor - startColor;

				uint8_t red = 0;
				uint8_t green = 0;
				uint8_t blue = 0;
				
				//Makes the image sharper
				if (iterations != frctl::Mandelbrot::MAX_ITERATIONS)
				{
					int totalPixels = 0;
					//double hue = 0.0; //range 0 to 1
					for (int i = rangeStart; i <= iterations; i++)
					{
						totalPixels += m_histogram[i]; //histogram gives total pixels
					}

					red = startColor.r + colorDiff.r *(double)totalPixels/rangeTotal;
					green = startColor.g + colorDiff.g *(double)totalPixels/rangeTotal;
					blue = startColor.b + colorDiff.b *(double)totalPixels/rangeTotal;

				}
				m_bitmap.setPixel(x, y, red, green, blue); // color-state for pixels

			}
		}
	}


	void FractalCreator::addZoom(const frctl::Zoom& zoom)
	{
		m_zoomList.add(zoom);
	}

	void FractalCreator::writeBitmap(std::string name)
	{
		m_bitmap.write(name);
	}
}