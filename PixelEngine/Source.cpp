#include "pch.h"
#include "System.h"
#include "Defines.h"

int main(int argc, char** argv)
{
    if (argc > 1 && argv[1] == "false") launchTextEditor = false;
    return System::Run();
}