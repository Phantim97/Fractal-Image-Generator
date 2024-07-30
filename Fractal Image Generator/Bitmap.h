#ifndef BITMAP_H
#define BITMAP_H

#include <cstdint>
#include <string>
#include <memory>

namespace frctl
{
	class Bitmap
	{
	private:
		int width_ = 0;
		int height_ = 0;
		std::unique_ptr<uint8_t[]> pixels_ =  nullptr ;

	public:
		Bitmap(int width, int height);
		virtual ~Bitmap() = default;

		bool write(const std::string& filename);
		void set_pixel(int x, int y, uint8_t red, uint8_t green, uint8_t);
	};
}

#endif