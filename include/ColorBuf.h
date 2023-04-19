#pragma once
#include "Color.h"
#include "ViewPortGL.h"

class ColorBuf {

public:
	ColorBuf(unsigned int widthP, unsigned int heightP);
	~ColorBuf();
	Color& get(unsigned int x, unsigned int y);
	void set(unsigned int x, unsigned int y, const Color& c);
	void drawTo(ViewPortGL& vp);
	void clear();

private:
	Color** colorState;
	const unsigned int width, height;
};

