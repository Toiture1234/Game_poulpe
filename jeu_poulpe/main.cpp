#include <SFML/Graphics.hpp>

#include <windows.h>

#include <iostream>
#include <string>

#include "core/app_handler.hpp"

int main()
{
    game::app mainApp(1280, 720, std::string("Game"));

    mainApp.init();
    mainApp.run();
    return 0;
}

/*int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
    MessageBoxA(NULL, (LPCSTR)"hello", (LPCSTR)"hello", 0);
    game::app mainApp(1280, 720, std::string("Game"));

    mainApp.init();
    mainApp.run();
    return 0;
}*/