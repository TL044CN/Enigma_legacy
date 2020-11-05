#pragma once
#include <fstream>

namespace Enigma {

	typedef struct png_color {
		uint8_t red;
		uint8_t green;
		uint8_t blue;
	};

	typedef struct png_color_16 {
		uint8_t index;
		uint16_t red;
		uint16_t green;
		uint16_t blue;
		uint16_t gray;
	};

	typedef struct png_color_8 {
		uint8_t red;
		uint8_t green;
		uint8_t blue;
		uint8_t gray;
		uint8_t alpha;
	}

	struct pnginfo {

	};

	

}
