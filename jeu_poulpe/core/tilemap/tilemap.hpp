#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "../constants.hpp"
#include "../objects/object.hpp"

#define READ_FROM_IMAGE 1
#define MAX_STEPS 50
#define EPSILON 0.5f


// boring thing to do
#define UP {{96, 0}, {32, 32}}
#define LEFT {{32, 0}, { 32, 32}}
#define RIGHT {{96, 64}, { 32, 32}}
#define DOWN {{32, 64}, { 32, 32}}

#define UP_LEFT {{32, 96}, { 32, 32}}
#define UP_RIGHT {{0, 0}, { 32, 32}}
#define DOWN_LEFT {{0, 64}, { 32, 32}}
#define DOWN_RIGHT {{96, 96}, { 32, 32}}

#define CORNER_UP_LEFT {{32, 32}, { 32, 32}}
#define CORNER_UP_RIGHT {{64, 0}, { 32, 32}}
#define CORNER_DOWN_LEFT {{64, 64}, { 32, 32}}
#define CORNER_DOWN_RIGHT {{96, 32}, { 32, 32}}

#define DIAGONAL_LEFT_RIGHT {{0, 32}, { 32, 32}}
#define DIAGONAL_RIGHT_LEFT {{64, 96}, { 32, 32}}
#define FULL {{64, 32}, {32, 32}}
#define EMPTY {{0, 96}, { 32, 32}}

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

		inline void draw(sf::RenderTexture* renderTex, sf::Vector2f position, sf::IntRect toSelect) {
			objRef->albedoSP.setTextureRect(toSelect);
			objRef->setPosition(position);
			objRef->draw(renderTex, nullptr);
		}
	};

	// //////////////////////////////////////////////////// main tilemap class ////////////////////////////////////////////////
	class tileMap {
	private:
		// maybe plan to move this to another location
		sf::Image tiles_img;

		sf::Vector2u size;

		// array of int to read tiles without relying on the sf::Image
		const uint8_t* pixelArray;
	public:
		tileSet usedTileSet;

		tileMap() {
			pixelArray = nullptr;
		}
		tileMap(std::string path) {
			if (!tiles_img.loadFromFile(path)) std::cout << "ERROR -- UNABLE TO LOAD TILEMAP\n";
			size = tiles_img.getSize();
			pixelArray = tiles_img.getPixelsPtr();
		}

		~tileMap() {}

		void loadtilemap(std::string path);
		void drawTilemap(sf::RenderTexture* renderTex, sf::Vector2f viewCenter);

		int readTile(sf::Vector2f pos) const;
		int readTileDirect(sf::Vector2u pos) const;
		sf::Vector2u convertToMapPos(sf::Vector2f pos) const ;
		int convertToIndex(sf::Vector2u mapPos) const;

		float intersect(sf::Vector2f pos, sf::Vector2f normDir, sf::Vector2f& normal); // obsolete
		bool traceRay(sf::Vector2f start, sf::Vector2f end, float& time, sf::Vector2f& normal);
	};
}