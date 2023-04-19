#include "../include/GridViewer.h"
#include <stdexcept>




Color GridViewer::colorFor(unsigned int value) {
    // Bitte implementieren!
}

void GridViewer::prepareCell(int x, int y) {
    // Bitte implementieren!
}

void GridViewer::prepareCellBorder(int x, int y) {
    // Bitte implementieren!
}

unsigned int GridViewer::getCell(int x, int y) {
    // Bitte implementieren!
}


void GridViewer::setCell(int x, int y, unsigned int value) {
	testCoordinates(x, y);
	content[y * gridSize + x] = value;
}

void GridViewer::draw() {
	int count = 0;
	static const int maxPreparedTriangles = getMaxNumberOfPreparedTriangles();
	static const int maxPreparedLines = getMaxNumberOfPreparedLines();
	for (int x = 0; x < gridSize; x++) {
		for (int y = 0; y < gridSize; y++) {
			prepareCell(x, y);
			prepareCellBorder(x, y);
			count++;
			if (maxPreparedTriangles - 1 <= count*2 || maxPreparedLines - 3 <= count * 4) {
				sendTriangles();
				sendLines();
				sendPixels();
				count = 0;
			}
		}
	}
	if (count > 0) {
		sendTriangles();
		sendLines();
		sendPixels();
	}
}

int GridViewer::getGridSize() {
	return gridSize;
}
