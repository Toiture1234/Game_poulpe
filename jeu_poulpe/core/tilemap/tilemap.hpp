#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "../constants.hpp"
#include "../objects/object.hpp"

#define READ_FROM_IMAGE 1
#define MAX_STEPS 50
#define EPSILON 0.5f


// define type of blocks
#define SOLID_0 0

namespace game {

	// small utility class to easily use tilemaps
	class tileSet {
	private:
		// object used for drawing,
		// it saves the texture used for drawing
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
		int readTileDirect(sf::Vector2u pos) const;
		sf::Vector2u convertToMapPos(sf::Vector2f pos) const ;

		float intersect(sf::Vector2f pos, sf::Vector2f normDir, sf::Vector2f& normal); // obsolete
		bool traceRay(sf::Vector2f start, sf::Vector2f end, float& time, sf::Vector2f& normal);
	};
}