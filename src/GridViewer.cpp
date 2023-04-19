#include "../include/GridViewer.h"
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <cstring>

GridViewer::GridViewer(string titleP, int size, int cellSizeP) : ViewPortGL(titleP, size, size), cellSize(cellSizeP), gridSize(size/cellSizeP)
{
	if(size < 4 || size > 1024)
		throw std::logic_error("Size is " + std::to_string(size) + ", must be 4 - 1024");
	if((size & (size - 1)) == 1)
		throw std::logic_error("Size " + std::to_string(size) + " is not a power of two");
	if(cellSizeP < 4 || cellSizeP > 1024)
		throw std::logic_error("Cell size is " + std::to_string(cellSizeP) + ", must be 4 - 1024");
	if((cellSizeP & (cellSizeP - 1)) == 1)
		throw std::logic_error("Cell size " + std::to_string(cellSizeP) + " is not a power of two");

	int contentSize = pow(gridSize, 2);
	content = new unsigned int[contentSize];
	std::memset(content, 0, contentSize * sizeof(int));
}

GridViewer::~GridViewer()
{
	delete content;
}

Color GridViewer::colorFor(unsigned int value) 
{
	int red = value >> 24 & 255;
	int green = value >> 16 & 255;
	int blue = value >> 8 & 255;

	return Color(red, green, blue);
}

void GridViewer::prepareCell(int x, int y) 
{
	int cellX = x * cellSize;
	int cellY = y * cellSize;
	Color cellColor = colorFor(content[y * gridSize + x]);
	prepareBlock(cellX, cellY, cellSize, cellSize, cellColor.getRed(), cellColor.getGreen(), cellColor.getBlue());
}

void GridViewer::prepareCellBorder(int x, int y, int thickness, int colorDelta) 
{
	//get color of cell
    Color c = colorFor(content[y * gridSize + x]);
	//lighten/darken the color
	Color cLight = c.lighten(colorDelta);
	Color cDark = c.darken(colorDelta);

	//draw differently colored borders
	prepareBlock(x * cellSize, y * cellSize, thickness, cellSize, cDark.getRed(), cDark.getGreen(), cDark.getBlue());
	prepareBlock(x * cellSize, (y+1) * cellSize - thickness, cellSize, thickness, cDark.getRed(), cDark.getGreen(), cDark.getBlue());
	prepareBlock(x * cellSize, y * cellSize, cellSize, thickness, cLight.getRed(), cLight.getGreen(), cLight.getBlue());
	prepareBlock((x+1) * cellSize - thickness, y * cellSize, thickness, cellSize, cLight.getRed(), cLight.getGreen(), cLight.getBlue());

	//make corners even lighter/darker
	Color cExtraLight = cLight.lighten(colorDelta);
	Color cExtraDark = cDark.darken(colorDelta);
	prepareBlock((x+1) * cellSize - thickness, y * cellSize, thickness, thickness, cExtraLight.getRed(), cExtraLight.getGreen(), cExtraLight.getBlue());
	prepareBlock(x * cellSize, (y+1) * cellSize - thickness, thickness, thickness, cExtraDark.getRed(), cExtraDark.getGreen(), cExtraDark.getBlue());

}

unsigned int GridViewer::getCell(int x, int y) 
{
	try { checkIsInGrid(x, y); } 
	catch (std::logic_error e) { std::cout << e.what() << std::endl; }
	return content[y * gridSize + x];
}


void GridViewer::setCell(int x, int y, unsigned int value) 
{
	try { checkIsInGrid(x, y); } 
	catch (std::logic_error e) { std::cout << e.what() << std::endl; }
	content[y * gridSize + x] = value;
}

void GridViewer::draw() 
{
	//initialize some count
	int count = 0;
	//get maximum number of triangles and lines
	static const int maxPreparedTriangles = getMaxNumberOfPreparedTriangles();
	static const int maxPreparedLines = getMaxNumberOfPreparedLines();
	//iterate over the 2d grid with curret position = x,y
	for (int x = 0; x < gridSize; x++) {
		for (int y = 0; y < gridSize; y++) {
			//prepare a cell at x,y
			prepareCell(x, y);
			//prepare the border of said cell
			prepareCellBorder(x, y, cellSize / 4, 75);
			//increase the count
			count++;
			//check if the graphics buffer contains enough space for the boxes (therefore triangles) we want to draw
			if (maxPreparedTriangles - 1 <= count*2 || maxPreparedLines - 3 <= count * 4) {
				//if yes, send them
				sendTriangles();
				sendLines();
				sendPixels();
				count = 0;
			}
		}
	}
	//final send at the end
	if (count > 0) {
		sendTriangles();
		sendLines();
		sendPixels();
	}
}

int GridViewer::getGridSize() 
{
	return gridSize;
}

void GridViewer::checkIsInGrid(int x, int y)
{
	if(x < 0 || x >= gridSize)
		throw std::logic_error("Value x = " + std::to_string(x) + " is out of grid bounds");
	if(y < 0 || y >= gridSize)
		throw std::logic_error("Value y = " + std::to_string(y) + " is out of grid bounds");
}