#pragma once
#include "ViewPortGL.h"
#include "Color.h"

class GridViewer : public ViewPortGL {
public:
	GridViewer(string titleP, int size, int cellSizeP);
	~GridViewer();
	unsigned int getCell(int x, int y);
	void setCell(int x, int y, unsigned int value);
	void draw();
	int getGridSize();

private:
	unsigned int* content;
	const int cellSize;
	const int gridSize;


protected:
	virtual Color colorFor(unsigned int value);
	virtual void prepareCell(int x, int y);
	virtual void prepareCellBorder(int x, int y, int thickness, int colorDelta);
	void checkIsInGrid(int x, int y);
};

