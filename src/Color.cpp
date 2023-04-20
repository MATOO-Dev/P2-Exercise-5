#include "../include/Color.h"
#include <cstdlib>
#include <stdexcept>
#include <string>
#include <iostream>

Color Color::nullColor;

Color::Color()
{
    red = 0;
    green = 0;
    blue = 0;
}

Color::Color(int r, int g, int b)
{
    if(r == -1 && g == -1 && b == -1)
    {
        red = -1;
        green = -1;
        blue = -1;
        return;
    }
    
    //first, check that all values are within range
    if(r < 0 || r > 255)
        throw std::logic_error("Error, constructor value for red is " + std::to_string(r) + ", should be 0-255");
    if(g < 0 || g > 255)
        throw std::logic_error("Error, constructor value for green is " + std::to_string(g) + ", should be 0-255");
    if(b < 0 || b > 255)
        throw std::logic_error("Error, constructor value for blue is " + std::to_string(b) + ", should be 0-255");
    
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
        throw std::logic_error("Error, set value for red is " + std::to_string(r) + ", should be 0-255");
    red = r;
}

void Color::setGreen(int g)
{
    if(g < 0 || g > 255)
        throw std::logic_error("Error, set value for green is " + std::to_string(g) + ", should be 0-255");
    green = g;
}

void Color::setBlue(int b)
{
    if(b < 0 || b > 255)
        throw std::logic_error("Error, set value for blue is " + std::to_string(b) + ", should be 0-255");
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

Color Color::averageWith(const Color& other) const
{
    int avgRed = (red + other.red) / 2;
    int avgGreen = (green + other.green) / 2;
    int avgBlue = (blue + other.blue) / 2;

    return Color(avgRed, avgGreen, avgBlue);
}

Color Color::averageWith(const Color& other1, const Color& other2, const Color& other3) const
{
    int avgRed = (red + other1.red + other2.red + other3.red) / 4;
    int avgGreen = (green + other1.green + other2.green + other3.green) / 4;
    int avgBlue = (blue + other1.blue + other2.blue + other3.blue) / 4;

    return Color(avgRed, avgGreen, avgBlue);
}

Color Color::randomlyChange(int maxAmount) const
{
    //generate random numbers between -maxAmount and maxAmount
    int randomRed = rand() % maxAmount * 2 - maxAmount;
    int randomGreen = rand() % maxAmount * 2 - maxAmount;
    int randomBlue = rand() % maxAmount * 2 - maxAmount;

    //add color + delta
    int newRed = red + randomRed;
    int newGreen = green + randomGreen;
    int newBlue = blue + randomBlue;

    //clamp to valid range
    newRed = (newRed < 0) ? 0 : newRed;
    newRed = (newRed > 255) ? 255 : newRed;
    newGreen = (newGreen < 0) ? 0 : newGreen;
    newGreen = (newGreen > 255) ? 255 : newGreen;
    newBlue = (newBlue < 0) ? 0 : newBlue;
    newBlue = (newBlue > 255) ? 255 : newBlue;

    //return shifted color
    return Color(newRed, newGreen, newBlue);
}

Color Color::randomColor()
{
    int randomRed = rand() % 256;
    int randomGreen = rand() % 256;
    int randomBlue = rand() % 256;
    return Color(randomRed, randomGreen, randomBlue); 
}

std::string Color::toString()
{
    return std::to_string(red) + "," + std::to_string(green) + "," + std::to_string(blue);
}
