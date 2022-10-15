#pragma once
#include "pch.h"

namespace Utils
{
    static string ToLowerString(const string& s)
    {
        string temp;
        temp.reserve(s.length());
        for (auto& c : s)
            temp.push_back(tolower(c));
        return temp;
    }

    static string ToUpperString(const string& s)
    {
        string temp;
        temp.reserve(s.length());
        for (auto& c : s)
            temp.push_back(toupper(c));
        return temp;
    }

    static bool IsDigit(const string& str)
    {
        short i = 0;
        if (str.front() == '+' || str.front() == '-') ++i;
        for (; i < str.length(); i++)
            if (!isdigit(str[i])) return false;
        return true;
    }

    static bool IsFloat(const string& str)
    {
        short numOfDeciamls = 0;
        short i = 0, j = 0;
        if (str.front() == '+' || str.front() == '-') ++i;
        if (str.back() == 'f') ++j;
        for (; i < str.length() - j; i++)
        {
            if (str[i] != '.' && !isdigit(str[i])) return false;
            if (str[i] == '.') ++numOfDeciamls;
            if (numOfDeciamls > 1) return false;
        }
        return true;
    }

	static void DrawRectangle(const Rectangle& rec, const Color& c = GRAY)
	{
		DrawRectangle(rec.x, rec.y, rec.width, rec.height, c);
	}

	static void DrawRectangleLines(const Rectangle& rec, const Color& c = RED)
	{
		DrawRectangleLines(rec.x, rec.y, rec.width, rec.height, c);
	}

    static bool Equals(const Vector2& v1, const Vector2& v2)
    {
        return v1.x == v2.x && v1.y == v2.y;
    }

    static bool Equals(const Vector3& v1, const Vector3& v2)
    {
        return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
    }

    static bool Equals(const Color& v1, const Color& v2)
    {
        return v1.r == v2.r && v1.g == v2.g && v1.b == v2.b && v1.a == v2.a;
    }
    
    static Color StringToColor(const string& s)
    {
        string str = ToUpperString(s);
        if (str == "LIGHTGRAY" || str == "LIGHTGREY") return LIGHTGRAY;
        if (str == "GRAY" || str == "GREY") return GRAY;
        if (str == "DARKGRAY") return DARKGRAY;
        if (str == "YELLOW") return YELLOW;
        if (str == "GOLD") return GOLD;
        if (str == "ORANGE") return ORANGE;
        if (str == "PINK") return PINK;
        if (str == "RED") return RED;
        if (str == "MAROON") return MAROON;
        if (str == "GREEN") return GREEN;
        if (str == "LIME") return LIME;
        if (str == "DARKGREEN") return DARKGREEN;
        if (str == "SKYBLUE") return SKYBLUE;
        if (str == "BLUE") return BLUE;
        if (str == "DARKBLUE") return DARKBLUE;
        if (str == "PURPLE") return PURPLE;
        if (str == "VIOLET") return VIOLET;
        if (str == "DARKPURPLE") return DARKPURPLE;
        if (str == "BEIGE") return BEIGE;
        if (str == "BROWN") return BROWN;
        if (str == "DARKBROWN") return DARKBROWN;
        if (str == "WHITE") return WHITE;
        if (str == "BLACK") return BLACK;
        if (str == "BLANK") return BLANK;
        if (str == "MAGENTA") return MAGENTA;
        if (str == "RAYWHITE") return RAYWHITE;
        return WHITE;
    }

    static bool TryParse(const string& str, float& num)
    {
        if (IsFloat(str))
        {
            num = stof(str);
            return true;
        }
        return false;
    }

    static bool TryParse(const string& str, int& num)
    {
        if (IsDigit(str))
        {
            num = stoi(str);
            return true;
        }
        return false;
    }

    static Color LerpColor(const Color& c1, const Color& c2, const float& t)
    {
        return Color(
            std::lerp(c1.r, c2.r, t),
            std::lerp(c1.g, c2.g, t),
            std::lerp(c1.b, c2.b, t),
            255
        );
    }

   /* static Color LerpColor(const Color& c1, const Color& c2, const float& numOfPoints, const float& currentPoint)
    {
        return Color(
            (c1.r + currentPoint) / (numOfPoints * (c1.r * c2.r)),
            (c1.b + currentPoint) / (numOfPoints * (c1.b * c2.b)),
            (c1.g + currentPoint) / (numOfPoints * (c1.g * c2.g)),
            255
        );
    }*/
}