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
    if(r > 255)
        throw std::logic_error("Error, value for red is " + std::to_string(r) + ", should be 255 maximum");
    if(g > 255)
        throw std::logic_error("Error, value for green is " + std::to_string(g) + ", should be 255 maximum");
    if(b > 255)
        throw std::logic_error("Error, value for blue is " + std::to_string(b) + ", should be 255 maximum");
    
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
    if(r > 255)
        throw std::logic_error("Error, value for red is " + std::to_string(r) + ", should be 255 maximum");
    red = r;
}

void Color::setGreen(int g)
{
    if(g > 255)
        throw std::logic_error("Error, value for green is " + std::to_string(g) + ", should be 255 maximum");
}

void Color::setBlue(int b)
{
    if(b > 255)
        throw std::logic_error("Error, value for blue is " + std::to_string(b) + ", should be 255 maximum");
}

Color Color::darken(int amount)
{
    if(amount < 0 || amount > 255)
        throw std::logic_error("Error, amount to darken is " + std::to_string(amount) + ", should be 0-255");
    int newRed = std::min(red - amount, 0);
    int newGreen = std::min(green - amount, 0);
    int newBlue = std::min(blue - amount, 0);
    return Color(newRed, newGreen, newBlue);
}

Color Color::lighten(int amount)
{
    if(amount < 0 || amount > 255)
        throw std::logic_error("Error, amount to lighten is " + std::to_string(amount) + ", should be 0-255");
    int newRed = std::max(red + amount, 255);
    int newGreen = std::max(green + amount, 255);
    int newBlue = std::max(blue + amount, 255);
    return Color(newRed, newGreen, newBlue);
}