#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "../constants.hpp"
#include "../objects/object.hpp"

#define READ_FROM_IMAGE 1

namespace game {

	// enum for every possible tile configuration, 16 now but will probably grow (up to 255 max), so I should probably put this to another file
	enum tilesIndex
	{
		// terrain (aka rocks), have to make variants so maybe rename everything
		UP = 0,
		DOWN = 1,
		LEFT = 2,
		RIGHT = 3,
		UP_LEFT = 4,
		UP_RIGHT = 5,
		DOWN_LEFT = 6,
		DOWN_RIGHT = 7,
		UP_DOWN = 8,
		LEFT_RIGHT = 9,
		LEFT_UP_RIGHT = 10,
		LEFT_DOWN_RIGHT = 11,
		UP_LEFT_DOWN = 12,
		UP_RIGHT_DOWN = 13,
		ALL_SIDES = 14,
		NO_SIDES = 16

		// objects
	};

	// small utility class to easily use tilemaps
	class tileSet {
	private:
		// object used for drawing
		object* objRef;
	public:
		tileSet() {
			objRef = nullptr;
		}
		tileSet(sf::Texture* albedo, sf::Texture* normal) {
			objRef = new object(albedo, normal);
		}
	};

	// main tilemap class 
	class tileMap {
	private:
		// maybe plan to move this to another location
		sf::Image tiles_img;

		sf::Vector2u size;

		// array of int to read tiles without relying on the sf::Image
		unsigned int* tiles_arr;
	public:
		tileMap() {
			tiles_arr = nullptr;
		}
		tileMap(std::string path) {
			if (!tiles_img.loadFromFile(path)) std::cout << "ERROR -- UNABLE TO LOAD TILEMAP\n";
			size = tiles_img.getSize();
			tiles_arr = new unsigned int[size.x * size.y];
		}

		void loadtilemap(std::string path);
		void drawTilemap(sf::RenderTexture* renderTex);

		int readTile(sf::Vector2f pos) const;
	};
}