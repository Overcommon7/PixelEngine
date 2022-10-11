#pragma once
#include "pch.h"

namespace Utils
{
    static void ToLowerString(string& s)
    {
        for (auto& c : s)
            c = tolower(c);
    }

    static void ToUpperString(string& s)
    {
        for (auto& c : s)
            c = toupper(c);
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
    
    static Color StringToColor(string str)
    {
        ToUpperString(str);
        if (str == "LIGHTGRAY") return LIGHTGRAY;
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
}