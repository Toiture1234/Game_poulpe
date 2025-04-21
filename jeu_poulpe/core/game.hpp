#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>
#include <vector>

#include "objects/object.hpp"
#include "tilemap/tilemap.hpp"
#include "objects/playable.hpp"
#include "follow_view.hpp"
#include "objects/text_displayer.hpp"

namespace game {
	class gameClass {
	private :
		// objects vector
		std::vector<sf::Texture> textureAtlas;
		std::vector<object> objectAtlas;

		// text displayers
		std::vector<textDiplayer> text_dspAtlas;

		// player def
		playable player;

		// tilemap
		tileMap worldTilemap;

		// font
		std::vector<sf::Font> fontAtlas;
		
		// shaders
		sf::Shader dark;

		bool isOnPause; // stops every game logic
		bool stopMovement;

		// pointers to time variables refered in the app, this gives global time to game without need to refresh it on every frame
		float* deltaT_ptr;
		float* runT_ptr;

		// pointers to window size, needed to rescale the view
		unsigned int* windowW_ptr;
		unsigned int* windowH_ptr;

		// view parameters
		unsigned int view_width;
		unsigned int view_height;
		unsigned int view_posX;
		unsigned int view_posY;

		// follower view on player
		sf::View worldView;

		// rendering, the game renders on a virtual screen that would later be displayed on window
		sf::RenderTexture gameRenderTexture; // draw the world without GUI
		sf::RenderTexture GUI_renderTexture; // draw everything
	public:
		gameClass() {
			isOnPause = false;
			deltaT_ptr = runT_ptr = nullptr;
			view_width = 416;
			view_height = 234;
			view_posX = view_posY = 0;
			windowH_ptr = windowW_ptr = nullptr;
			worldView = sf::View(sf::FloatRect(sf::Vector2f(view_posX, view_posY), sf::Vector2f(view_width, view_height)));
			stopMovement = false;
		}

		void init(float* dtPtr, float* rtPtr, unsigned int* wW, unsigned int* wH);
		void initTextures();
		void initShaders();
		void initRenderTexContext();

		void onUpdate();
		void drawToWindow(sf::RenderWindow* window);
	};
}