
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <thread>
#include "include/ColorBuf.h"
#include "include/GridViewer.h"
#include "include/PaletteGridViewer.h"
#include "include/ViewPortGL.h"

void ColorGrid(int width, int height)
{
    //create window and buffer
    ViewPortGL targetWindow = ViewPortGL("Schön Bunt!", width, height);
    ColorBuf targetBuffer = ColorBuf(width, height);
    

    //set buffer corners to random values
    targetBuffer.set(0, 0, Color::randomColor());
    targetBuffer.set(width - 1, 0, Color::randomColor());
    targetBuffer.set(0, height - 1, Color::randomColor());
    targetBuffer.set(width - 1, height - 1, Color::randomColor());

    targetWindow.sendPixels();

    targetBuffer.buildColorPic(0, 0, width - 1, height - 1, targetBuffer);
    targetBuffer.drawTo(targetWindow);

    targetWindow.swapBuffers();

    while(!targetWindow.windowShouldClose());
}

void ColorGridCells(int windowSize, int cellSize)
{
    //create window and buffer
    GridViewer targetGrid = GridViewer("Bunte Zellen", windowSize, cellSize);
    
    //set buffer corners to random values
    targetGrid.setCell(0, 0, GridViewer::valueFor(Color::randomColor()));
    targetGrid.setCell(windowSize / cellSize -1, 0, GridViewer::valueFor(Color::randomColor()));;
    targetGrid.setCell(0, windowSize / cellSize -1, GridViewer::valueFor(Color::randomColor()));;
    targetGrid.setCell(windowSize / cellSize -1, windowSize / cellSize -1, GridViewer::valueFor(Color::randomColor()));;

    targetGrid.buildColorPic(0, 0, windowSize / cellSize - 1, windowSize / cellSize - 1);

    targetGrid.draw();
    targetGrid.swapBuffers();

    while(!targetGrid.windowShouldClose());
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    try {
        //ColorGrid(1024, 1024);
        ColorGridCells(1024, 8);
    } catch (...) {
        cout << "Unknown error" << endl;
        getchar();
    }
	return 0;
}
