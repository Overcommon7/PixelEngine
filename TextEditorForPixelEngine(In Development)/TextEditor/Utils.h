#pragma once
#include "pch.h"
#include "Defines.h"

namespace Utils
{
    template<typename T>
    static T Random(const T& includedMax, const T& includedMin = 0, const std::pair<T, T>& ExcludeRange = { 0, 0 }, const vector<T>& exclude = {})
    {
        bool range = false;
        bool isValid = true;
        T value{};
        if (ExcludeRange.first != ExcludeRange.second) range = true;
        std::random_device r;

        do
        {
            isValid = true;
            std::mt19937 gen(r());
            std::uniform_int_distribution<T> dist(includedMin, includedMax);
            value = dist(gen);
            for (const auto& i : exclude)
                if (i == value)
                {
                    isValid = false;
                    break;
                }
            if (range && isValid)
                if (value >= ExcludeRange.first && value <= ExcludeRange.second)
                    isValid = false;
        } while (!isValid);
        return value;
    }

    static void DrawRectangle(const Rectangle& r, const Color& c = BLACK)
    {
        DrawRectangle(r.x, r.y, r.width, r.height, c);
    }

    static void DrawRectangleLines(const Rectangle& r, const Color& c = BLACK)
    {
        DrawRectangleLines(r.x, r.y, r.width, r.height, c);
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
}
