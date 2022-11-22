#pragma once
class Events
{
public:
    Events() = delete;
    Events(const Events& e) = delete;
    Events& operator=(const Events& e) = delete;

    static void OnScriptLoaded();
    static void OnScriptInit();
    static void OnNewFrame();
};

