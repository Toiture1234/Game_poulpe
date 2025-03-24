#include "tilemap.hpp"

//////////////////////////////////////////////////// main tilemap class ////////////////////////////////////////////////////

// consider the position given is the world position
int game::tileMap::readTile(sf::Vector2f pos) const {
	sf::Vector2f tilePos = sf::Vector2f(pos.x / 32.f, pos.y / 32.f);

	// equivalent to clamping (as I don't made any function for clamping yet), to change later maybe
	tilePos.x = fminf(size.x - 1, fmaxf(0, tilePos.x));
	tilePos.y = fminf(size.y - 1, fmaxf(0, tilePos.y));

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

// intersection, returns the minimal value from the position to the tilemap
float game::tileMap::intersect(sf::Vector2f pos, sf::Vector2f normDir) {
	// returned distance
	float t = 0;

	bool signX = normDir.x >= 0.f;
	bool signY = normDir.y >= 0.f;

	sf::Vector2f pos0 = pos;
	for (int i = 0; i < MAX_STEPS; i++) {
		int tileIdx = readTile(pos);
		if (tileIdx <= 10) break;

		float deltaX = signX * TILE_SIZE - (int)pos.x % TILE_SIZE;
		float deltaY = signY * TILE_SIZE - (int)pos.y % TILE_SIZE;

		// we can do this because dividing by 0 is allowed in c++
		// I hope deltaXY would never be 0
		float tX = fabsf(deltaX / normDir.x);
		float tY = fabsf(deltaY / normDir.y);

		bool isX = fminf(tX, tY) == tX;
		t += fminf(tX, tY) + EPSILON * (isX ? !signX : !signY);
		pos = pos0 + normDir * t;
	}
	return t;
}