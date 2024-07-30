#pragma once

#include <cstdint>

#pragma pack(push, 2) //makes c++ allign the struct on 2 byte boundaries rather than using extra padding to bound it

namespace frctl//cave of programming
{
	struct BitmapFileHeader //the pack allows this to be a readable file
	{
		int32_t fileSize; // this makes sure we can be portable and use a 32 byte type int
		int32_t reserved{ 0 };
		int32_t dataOffset; //how much into the file the data begins
		char header[2]{ 'B','M' };
	};
}

#pragma pack(pop)
