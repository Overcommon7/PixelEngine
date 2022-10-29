#include "pch.h"
#include "System.h"

//------------------------------------------------------------------------------------------
// Main entry point
//------------------------------------------------------------------------------------------
#ifndef NDEBUG
int main(void)
#else
int wWinMain()
#endif
{
    return System::Run();
}
