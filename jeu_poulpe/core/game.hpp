#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>
#include <vector>

#include "objects/object.hpp"
#include "objects/playable.hpp"

namespace game {
	class gameClass {
	private :
		// objects vector
		std::vector<sf::Texture> textureAtlas;
		std::vector<sf::Shader> shaderAtlas;
		std::vector<object> objectAtlas;

		// player def
		playable player;

		bool isOnPause;

		// pointers to time variables refered in the app, this gives global time to game
		float* deltaT_ptr;
		float* runT_ptr;

		// pointers to window size, needed to rescale the view
		unsigned int* windowW_ptr;
		unsigned int* windowH_ptr;

		// view
		unsigned int view_width;
		unsigned int view_height;
		unsigned int view_posX;
		unsigned int view_posY;
		sf::View worldView;

		// rendering, the game renders on a virtual screen that would later be displayed on window
		sf::RenderTexture gameRenderTexture;
	public:
		gameClass() {
			isOnPause = false;
			deltaT_ptr = runT_ptr = nullptr;
			view_width = 1280;
			view_height = 720;
			view_posX = view_posY = 0;
			windowH_ptr = windowW_ptr = nullptr;
		}

		void init(float* dtPtr, float* rtPtr, unsigned int* wW, unsigned int* wH);
		void initTextures();
		void initShaders();
		void initRenderTexContext();

		void onUpdate();
		void drawToWindow(sf::RenderWindow* window);
	};
}