#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>

#include "core/app_handler.hpp"

int main()
{
    game::app mainApp(300, 300, std::string("Hello"));

    mainApp.init();
    mainApp.run();
    return 0;
}