#include <Windows.h>
#include <iostream>
#include <string>
#include <locale>
#include <codecvt>


bool isRunning(LPCWSTR pName)
{
    HWND hwnd;
    hwnd = FindWindow(NULL, pName);
    if (hwnd != 0) {
        return true;
    }
    else {
        return false;
    }
}



void startup(LPCTSTR lpApplicationName, LPCWSTR directory)
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    // set the size of the structures
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // start the program up
    std::cout << CreateProcess(lpApplicationName,   // the path
        (LPWSTR)L"",        // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        0,              // No creation flags
        NULL,           // Use parent's environment block
        directory,           // Use parent's starting directory 
        &si,            // Pointer to STARTUPINFO structure
        &pi             // Pointer to PROCESS_INFORMATION structure (removed extra parentheses)
    );
    // Close process and thread handles. 
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

bool RunTextEditor(const wchar_t* name, const wchar_t* dir)
{
    if (isRunning(L"Pixel Engine Script Editor")) return false;
    startup(name, dir);
    return true;
}

int main(int argc, char** argv)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::string dir(argv[0]);
    dir.erase(dir.find("\\PixelEngine") + strlen("\\PixelEngine"));
    std::string name = dir + "\\TextEditor\\TextEditorFrontEnd.exe";
    dir += "\\PixelEngine\\";
    std::wstring workingDir = converter.from_bytes(dir);
    std::wstring appName = converter.from_bytes(name);
    RunTextEditor(appName.c_str(), workingDir.c_str());
    //return CloseTextEditor();
}

    


