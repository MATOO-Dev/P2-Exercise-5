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
	void buildColorPic(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
	static Color colorFor(unsigned int value);
	static unsigned int valueFor(Color color);

private:
	unsigned int* content;
	const int cellSize;
	const int gridSize;


protected:
	virtual void prepareCell(int x, int y);
	virtual void prepareCellBorder(int x, int y, int thickness, int colorDelta);
	void checkIsInGrid(int x, int y);
};

