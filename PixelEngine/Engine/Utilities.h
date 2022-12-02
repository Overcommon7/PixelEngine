#pragma once
#include "pch.h"

namespace Utils
{

    const inline static std::unordered_map<string, Color> colors = {
        {"LIGHTGRAY", LIGHTGRAY },
        {"GRAY",      GRAY      },
        {"DARKGRAY",  DARKGRAY  },
        {"YELLOW",    YELLOW    },
        {"GOLD",      GOLD      },
        {"ORANGE",    ORANGE    },
        {"PINK",      PINK      },
        {"RED",       RED       },
        {"MAROON",    MAROON    },
        {"GREEN",     GREEN     },
        {"LIME",      LIME      },
        {"DARKGREEN", DARKGREEN },
        {"SKYBLUE",   SKYBLUE   },
        {"BLUE",      BLUE      },
        {"DARKBLUE",  DARKBLUE  },
        {"PURPLE",    PURPLE    },
        {"VIOLET",    VIOLET    },
        {"DARKPURPLE",DARKPURPLE},
        {"BEIGE",     BEIGE     },
        {"BROWN",     BROWN     },
        {"DARKBROWN", DARKBROWN },
        {"WHITE",     WHITE     },
        {"BLACK",     BLACK     },
        {"BLANK",     BLANK     },
        {"MAGENTA",   MAGENTA   },
        {"RAYWHITE",  RAYWHITE  }
    };


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

    static bool Equals(const float& a, const float& b)
    {
        return abs(a - b) < 0.01f;
    }

    static bool Equals(const Vector2& v1, const Vector2& v2)
    {
        return Equals(v1.x, v2.x) && Equals(v1.y, v2.y);
    }

    static bool Equals(const Vector3& v1, const Vector3& v2)
    {
        return  Equals(v1.x, v2.x) && Equals(v1.y, v2.y) && Equals(v1.z, v2.z);
    }

    static bool Equals(const Color& v1, const Color& v2)
    {
        return v1.r == v2.r && v1.g == v2.g && v1.b == v2.b && v1.a == v2.a;
    }
    
    static Color StringToColor(const string& s)
    {
        string str = ToUpperString(s);
        if (colors.contains(str)) return colors.at(str);
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

    static bool TryParse(const vector<string>& params, vector<float>& values)
    {
        values.resize(params.size(), 0);
        for (short i = 0; i < params.size(); i++)
            if (!TryParse(params[i], values[i])) return false;
        return true;
    }

    static bool TryParse(const vector<string>& params, vector<int>& values)
    {
        values.resize(params.size(), 0);
        for (short i = 0; i < params.size(); i++)
            if (!TryParse(params[i], values[i])) return false;
        return true;
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

    static bool IsUnitColor(const Color& c)
    {
        return (c.r < 1.01f && c.b < 1.01f && c.g < 1.01f);
    }

    static bool IsUnitColor(const float& r, const float& g, const float& b)
    {
        return (r < 1.01f && b < 1.01f && g < 1.01f);
    }

    static Color UnitTo8BitColor(const float& r, const float& g, const float& b, const float& a = 1)
    {
        return Color(
            (unsigned char)std::min(r * 255.f, 255.f),
            (unsigned char)std::min(g * 255.f, 255.f),
            (unsigned char)std::min(b * 255.f, 255.f),
            (unsigned char)std::min(a * 255.f, 255.f));
    }

    static Color UnitTo8BitColor(const Color& c)
    {
        return Color(
            (unsigned char)std::min(c.r * 255.f, 255.f),
            (unsigned char)std::min(c.g * 255.f, 255.f),
            (unsigned char)std::min(c.b * 255.f, 255.f),
            (unsigned char)std::min(c.a * 255.f, 255.f));
    }

    static Vector3 MultiplyRaylibVector3(const Vector3& v1, const Vector3& v2)
    {
        return Vector3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
    }

    static Color MultiplyColor(const Color& c1, const Color& c2)
    {
        Vector3 v1 = { (float)c1.r / 255.f, (float)c1.g / 255.f, (float)c1.b / 255.f };
        Vector3 v2 = { (float)c2.r / 255.f, (float)c2.g / 255.f, (float)c2.b / 255.f };
        Vector3 v3 = MultiplyRaylibVector3(v1, v2);
        return UnitTo8BitColor(v3.x, v3.y, v3.z);
    }

    static Color MultiplyColor(const Color& c, const float& f)
    {
        Color color;
        if (f > 1.01f)
            color = Color(f, f, f, 255);
        else color = Color(f * 255, f * 255, f * 255, f * 255);
        return MultiplyColor(c, color);
    }


    static Color AddColor(const Color& c1, const Color& c2)
    {
        Color color1 = c1, color2 = c2;
        if (IsUnitColor(c1))
            color1 = UnitTo8BitColor(c1);
        if (IsUnitColor(c2))
            color2 = UnitTo8BitColor(c2);

        return Color(
            (unsigned char)std::min((int)color1.r + (int)color2.r, 255),
            (unsigned char)std::min((int)color1.g + (int)color2.g, 255),
            (unsigned char)std::min((int)color1.b + (int)color2.b, 255),
            (unsigned char)255);
    }
}