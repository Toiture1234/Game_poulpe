#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>

#include "game.hpp"

namespace game {
	class app {
	private :
		sf::RenderWindow window;

		unsigned int window_width;
		unsigned int window_height;
		std::string window_name;

		float runTime;
		float delta_time;

		gameClass thisGame;
	public :
		app() {
			window_width = 200;
			window_height = 200;
			window_name = "NULL WINDOW";
			window = sf::RenderWindow(sf::VideoMode({ window_width, window_height }), window_name.c_str());
			runTime = 0.f;
			delta_time = 1.f;
			thisGame = gameClass();
		}
		app(unsigned int wW, unsigned int wH, std::string wN) {
			window_width = wW;
			window_height = wH;
			window_name = wN;
			window = sf::RenderWindow(sf::VideoMode({ window_width, window_height }), window_name.c_str());
			runTime = 0.f;
			delta_time = 0.f; // this avoid excessive moving when starting
			thisGame = gameClass();
		}

		void init();
		void run();
		void handleEvents();
	};
}