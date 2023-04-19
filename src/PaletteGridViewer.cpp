#include "../include/PaletteGridViewer.h"
#include <stdexcept>
#include <string>
#include <cstring>

PaletteGridViewer::PaletteGridViewer(string title, int size, int cellSize, int paletteSizeP) : GridViewer(title, size, cellSize)
{
    if(paletteSizeP < 1 || paletteSizeP > 256)
        throw std::logic_error("Error, pallet size is " + std::to_string(paletteSizeP) + ", should be 1 - 256");

    paletteSize = paletteSizeP;
    palette = new Color[paletteSize];
	std::memset(palette, 0, paletteSize * sizeof(Color));
}	

PaletteGridViewer::~PaletteGridViewer()
{
    delete palette;
}

void PaletteGridViewer::setColor(unsigned int value, Color c)
{
    if(value < 0 || value > 255)
        throw std::logic_error("Error, color value is " + std::to_string(value) + ", should be 0 - 255");

    palette[value] = c;
}

Color PaletteGridViewer::getColor(unsigned int value)
{
    if(value < 0 || value > 255)
        throw std::logic_error("Error, color value is " + std::to_string(value) + ", should be 0 - 255");

    return palette[value];
}

Color PaletteGridViewer::colorFor(unsigned int value)
{
    if(value >= 0 && value <= 255)
        return palette[value];

    return GridViewer::colorFor(value);
}