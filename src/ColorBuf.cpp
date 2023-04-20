#include "../include/ColorBuf.h"
#include <cmath>
#include <cstring>
#include <stdexcept>
#include <string>
#include <iostream>

ColorBuf::ColorBuf(unsigned int widthP, unsigned int heightP) : width(widthP), height(heightP)
{
    //fill color state array with array pointers (x axis)
    colorState = new Color*[width];
    //then fill those array pointers with array to create a 2d array (y axis)
    for(int i = 0; i < width; i++)
        colorState[i] = new Color[height];
    
    //clear buffer by filling it with nullColor
    clear();
}

ColorBuf::~ColorBuf()
{
    //delete pointers to vertical lines
    for(int i = 0; i < width; i++)
        delete colorState[i];
    //delete overall grid
    delete colorState;
}

Color& ColorBuf::get(unsigned int x, unsigned int y)
{
    return colorState[x][y];
}

void ColorBuf::set(unsigned int x, unsigned int y, const Color& c)
{
    colorState[x][y] = c;
}

void ColorBuf::clear()
{
    //reset all to nullColor
    for(int w = 0; w < width; w++)
        for(int h = 0; h < height; h++)
            colorState[w][h] = Color::nullColor;
}


void ColorBuf::drawTo(ViewPortGL& vp)
{
    if(width != vp.getXSize() || height != vp.getYSize())
    {
        string bufferDimensions = std::to_string(width) + "," + std::to_string(height);
        string viewPortDimensions = std::to_string(vp.getXSize()) + "," + std::to_string(vp.getYSize());
        throw std::logic_error("Error, color buffer dimensions " + bufferDimensions + " do not match viewport dimensions " + viewPortDimensions);
    }

    int currentPrepareCount = 0;
    int maxPrepareCount = ViewPortGL::getMaxNumberOfPreparedPixels();

    for(int w = 0; w < width; w++)
        for(int h = 0; h < height; h++)
        {
            if(colorState[w][h].equals(Color::nullColor))
                continue;
            
            vp.preparePix(w, h, colorState[w][h].getRed(), colorState[w][h].getGreen(), colorState[w][h].getBlue());
            currentPrepareCount++;

            if(currentPrepareCount == maxPrepareCount)
            {
                vp.sendPixels();
                currentPrepareCount = 0;
            }
        }
        
    //final send pixels
    vp.sendPixels();
}


void ColorBuf::buildColorPic(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, ColorBuf& cBuf)
{
    int xDelta = abs((int)x2 - (int)x1);
    int yDelta = abs((int)y2 - (int)y1);

    if(xDelta <= 1 && yDelta <= 1)
        return;

    int randomChangeMaxAmount = 50;

    Color topLeftColor = cBuf.get(x1, y1);
    Color topRightColor = cBuf.get(x2, y1);
    Color bottomLeftColor = cBuf.get(x1, y2);
    Color bottomRightColor = cBuf.get(x2, y2);

    int middleX = (x2 + x1) / 2;
    int middleY = (y2 + y1) / 2;

    //check for width/height here first
    if(xDelta > 1)
    {
        //set top middle
        if(cBuf.get(middleX, y1).equals(Color::nullColor))
            cBuf.set(middleX, y1, topLeftColor.averageWith(topRightColor).randomlyChange(randomChangeMaxAmount));
        //set bottom middle
        if(cBuf.get(middleX, y2).equals(Color::nullColor))
            cBuf.set(middleX, y2, bottomLeftColor.averageWith(bottomRightColor).randomlyChange(randomChangeMaxAmount));
    }
    if(yDelta > 1)
    {
        //set left middle
        if(cBuf.get(x1, middleY).equals(Color::nullColor))
            cBuf.set(x1, middleY, topLeftColor.averageWith(bottomLeftColor).randomlyChange(randomChangeMaxAmount));
        //set right middle
        if(cBuf.get(x2, middleY).equals(Color::nullColor))
            cBuf.set(x2, middleY, topRightColor.averageWith(bottomRightColor).randomlyChange(randomChangeMaxAmount));
    }
    //set center
    if(cBuf.get(middleX, middleY).equals(Color::nullColor))
            cBuf.set(middleX, middleY, topLeftColor.averageWith(topRightColor, bottomLeftColor, bottomRightColor).randomlyChange(randomChangeMaxAmount));

    //run recursively
    buildColorPic(x1, y1, middleX, middleY, cBuf);
    buildColorPic(middleX, y1, x2, middleY, cBuf);
    buildColorPic(x1, middleY, middleX, y2, cBuf);
    buildColorPic(middleX, middleY, x2, y2, cBuf);
}