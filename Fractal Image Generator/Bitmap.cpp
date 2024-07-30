#include <fstream>
#include "Bitmap.h"
#include "bitmapInfoHeader.h"
#include "bitmapFileHeader.h"

namespace frctl
{
	Bitmap::Bitmap(const int width, const int height) : pixels_(new uint8_t[width * height * 3]{})
	{
		width_ = width;
		height_ = height;
	}

	bool Bitmap::write(const std::string& filename)
	{
		frctl::BitmapFileHeader fileHeader; 
		frctl::BitmapInfoHeader infoHeader;

		//File header contains info about file (needs to take size of everything)
		fileHeader.file_size = sizeof(frctl::BitmapFileHeader) + sizeof(frctl::BitmapInfoHeader) + width_ * height_ * 3;
		fileHeader.data_offset = sizeof(frctl::BitmapFileHeader) + sizeof(frctl::BitmapInfoHeader); //starts where pixels do and where info ends

		//Info contains info about the bitmap
		infoHeader.width = width_;
		infoHeader.height = height_;

		//Creating a binary file
		std::ofstream file;
		file.open(filename, std::ios::out|std::ios::binary);

		if (!file)
		{
			return false;
		}

		//writes to file with a char pointer with also the size of that buffer
		file.write((char *)&fileHeader, sizeof(fileHeader));
		file.write((char *)&infoHeader, sizeof(infoHeader));
		file.write((char *)pixels_.get(), width_ * height_ * 3); //.get() to obtain a raw pointer

		file.close();

		//checks if file cannot be closed
		if (!file)
		{
			return false;
		}

		return true;
	}

	void Bitmap::set_pixel(const int x, const int y, const uint8_t red, const uint8_t green, const uint8_t blue)
	{
		uint8_t* pixel = pixels_.get(); // get the data for the memory block

		//pointer arithmetic
		pixel += (y * 3) * width_ + (x * 3);
		//references the bytes of the pixel
		pixel[0] = blue;
		pixel[1] = green;
		pixel[2] = red;
		
	}

}