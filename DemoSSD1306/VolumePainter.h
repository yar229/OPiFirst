#pragma once

#ifdef __cplusplus
extern "C"
{
#endif
	#include "fonts.h"
#ifdef __cplusplus
}
#endif

class VolumePainter
{
	public:
		VolumePainter();
		~VolumePainter();
		void Draw(int num);

	private:
		font_info_t * _fontBig = (font_info_t *)(fonts[4]);
		char _printBuffer[4];
};

