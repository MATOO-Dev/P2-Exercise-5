#include "../include/Color.h"
#include <stdexcept>
#include <string>

Color::Color()
{
    red = 0;
    green = 0;
    blue = 0;
}

Color::Color(int r, int g, int b)
{
    //first, check that all values are within range
    if(r < 0 || r > 255)
        throw std::logic_error("Error, value for red is " + std::to_string(r) + ", should be 0-255");
    if(g < 0 || g > 255)
        throw std::logic_error("Error, value for green is " + std::to_string(g) + ", should be 0-255");
    if(b < 0 || b > 255)
        throw std::logic_error("Error, value for blue is " + std::to_string(b) + ", should be 0-255");
    
    red = r;
    green = g;
    blue = b;
}

int Color::getRed()
{
    return red;
}

int Color::getGreen()
{
    return green;
}

int Color::getBlue()
{
    return blue;
}

void Color::setRed(int r)
{
    if(r < 0 || r > 255)
        throw std::logic_error("Error, value for red is " + std::to_string(r) + ", should be 0-255");
    red = r;
}

void Color::setGreen(int g)
{
    if(g < 0 || g > 255)
        throw std::logic_error("Error, value for green is " + std::to_string(g) + ", should be 0-255");
    green = g;
}

void Color::setBlue(int b)
{
    if(b < 0 || b > 255)
        throw std::logic_error("Error, value for blue is " + std::to_string(b) + ", should be 0-255");
    blue = b;
}

Color Color::darken(int amount)
{
    if(amount < 0 || amount > 255)
        throw std::logic_error("Error, amount to darken is " + std::to_string(amount) + ", should be 0-255");
    int newRed = (red - amount) < 0 ? 0 : (red - amount);
    int newGreen = (green - amount) < 0 ? 0 : (green - amount);
    int newBlue = (blue - amount) < 0 ? 0 : (blue - amount);

    return Color(newRed, newGreen, newBlue);
}

Color Color::lighten(int amount)
{
    if(amount < 0 || amount > 255)
        throw std::logic_error("Error, amount to lighten is " + std::to_string(amount) + ", should be 0-255");
    int newRed = (red + amount) > 255 ? 255 : (red + amount);
    int newGreen = (green + amount) > 255 ? 255 : (green + amount);
    int newBlue = (blue + amount) > 255 ? 255 : (blue + amount);
    return Color(newRed, newGreen, newBlue);
}