#include "app_handler.hpp"

void game::app::init() {
    this->thisGame.init(&delta_time, &runTime, &window_width, &window_height);
}

void game::app::run() {
    // clock
    sf::Clock mainClock;
    mainClock.restart();

    //window.setFramerateLimit(30);

    // main loop
    while (window.isOpen())
    {
        handleEvents();

        std::cout << "NEW FRAME :\n";

        window.clear();
        thisGame.onUpdate();
        thisGame.drawToWindow(&window);

        window.display();

        // time evaluation
        this->delta_time = mainClock.restart().asSeconds();
        this->runTime += delta_time;

        std::cout << "Runtime : " << this->runTime << ", deltaTime : " << this->delta_time << ", fps : " << 1./ this->delta_time << "\n";
        
    }
}
void game::app::handleEvents() {
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            window.close();
        if (event->is<sf::Event::Resized>()) {
            window_width = window.getSize().x;
            window_height = window.getSize().y;
        }
    }
}