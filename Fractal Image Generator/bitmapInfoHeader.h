#ifndef BITMAP_INFO_HEADER_H
#define BITMAP_INFO_HEADER_H

#include <cstdint>

#pragma pack(push, 2)
namespace frctl
{
	struct BitmapInfoHeader
	{
		int32_t header_size = 40; //size of struct in bytes
		int32_t width = 0;
		int32_t height = 0;
		int16_t planes = 1 ;
		int16_t bits_per_pixel = 24 ; //1 byte (8 bits) per color RGB
		int32_t compression = 0;
		int32_t data_size = 0;
		int32_t horizontal_resolution = 2400;
		int32_t vertical_resolution = 2400;
		int32_t colors = 0; //may not be used
		int32_t important_colors = 0; //may not be used
	};
}

#pragma pack(pop)

#endif