#pragma once

#include <cstdlib>
#include <string>
class Color
{
private:
    int red;
    int green;
    int blue;
public:
    Color();
    Color(int r, int g, int b);
    int getRed();
    int getGreen();
    int getBlue();
    void setRed(int r);
    void setGreen(int g);
    void setBlue(int b);
    Color darken(int amount);
    Color lighten(int amount);
    Color averageWith(const Color& other) const;
    Color averageWith(const Color& other1, const Color& other2, const Color& other3) const;
    Color randomlyChange(int maxAmount) const;
    inline bool equals(const Color &other) const { return (red == other.red) && (green == other.green) && (blue == other.blue); }
    std::string toString();

    static Color nullColor;
    static Color randomColor();
};