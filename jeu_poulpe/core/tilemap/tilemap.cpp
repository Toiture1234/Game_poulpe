#include "tilemap.hpp"

//////////////////////////////////////////////////// main tilemap class ////////////////////////////////////////////////////

// consider the position given is the world position
int game::tileMap::readTile(sf::Vector2f pos) const {
	sf::Vector2f tilePos = sf::Vector2f((int)pos.x % 32, (int)pos.y % 32);

	// equivalent to clamping (as I don't made any function for clamping yet), to change later maybe
	tilePos.x = fminf(size.x, fmaxf(0, tilePos.x));
	tilePos.y = fminf(size.y, fmaxf(0, tilePos.y));

	int idx = tilePos.x + tilePos.y * size.x;

#if READ_FROM_IMAGE
	// read only the red channel, this allows to have 255 different indicies, it should be enough
	return tiles_img.getPixel(sf::Vector2u(tilePos.x, tilePos.y)).r;
#else
	return tiles_arr[idx];
#endif
}

// basically the same as the constructor
void game::tileMap::loadtilemap(std::string path) {
	if (!tiles_img.loadFromFile(path)) std::cout << "ERROR -- UNABLE TO LOAD TILEMAP\n";
	size = tiles_img.getSize();
	tiles_arr = new unsigned int[size.x * size.y];
}

void game::tileMap::drawTilemap(sf::RenderTexture* renderTex) {
	// ye this is a terrible idea, I have to change this really quickly because it's REALLY dangerous
	sf::Texture tileTex(tiles_img);
	// init the sprite here
	sf::Sprite drawer(tileTex);
	drawer.setScale(sf::Vector2f(TILE_SIZE, TILE_SIZE));
	renderTex->draw(drawer);
}