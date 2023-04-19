#pragma once
#include "../include/GridViewer.h"
#include "../include/Color.h"


class PaletteGridViewer : public GridViewer {

public:
	PaletteGridViewer(string title, int size, int cellSize, int paletteSizeP);	
	void setColor(unsigned int value, Color c);
	Color getColor(unsigned int value);

private:
	unsigned int paletteSize;
	Color* palette;

protected:
	Color colorFor(unsigned int value);

};

