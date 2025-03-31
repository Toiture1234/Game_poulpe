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
int game::tileMap::readTileDirect(sf::Vector2u pos) const {
	return tiles_img.getPixel(pos).r;
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
float game::tileMap::intersect(sf::Vector2f pos, sf::Vector2f normDir, sf::Vector2f& normal) {
	// returned distance
	float t = 0;
    
	bool signX = normDir.x >= 0.f;
	bool signY = normDir.y >= 0.f;

	sf::Vector2f pos0 = pos;
	normal = sf::Vector2f(0.f, 0.f);
	for (int i = 0; i < MAX_STEPS; i++) {
		// break after normal calculations
		int tileIdx = readTile(pos);
		if (tileIdx <= 10) break;

		float deltaX = signX * TILE_SIZE - (int)pos.x % TILE_SIZE;
		float deltaY = signY * TILE_SIZE - (int)pos.y % TILE_SIZE;

		// we can do this because dividing by 0 is allowed in c++
		// I hope deltaXY would never be 0
		float tX = fabsf(deltaX / normDir.x);
		float tY = fabsf(deltaY / normDir.y);

		bool isX = fminf(tX, tY) == tX;
		normal = isX ? sf::Vector2f(-1.f, 0.f) * (normDir.x >= 0.f ? 1.f : -1.f) : sf::Vector2f(0.f, -1.f) * (normDir.y >= 0.f ? 1.f : -1.f);

		t += fminf(tX, tY) + EPSILON;
		pos = pos0 + normDir * t;
	}
	return t;
	
}

bool game::tileMap::traceRay(sf::Vector2f start, sf::Vector2f end, float& time, sf::Vector2f& normal) {

	time = 0.f;
	normal = sf::Vector2f(0.f, 0.f);

	int tileValue = readTile(start);
	if (tileValue <= 10) return true;

	sf::Vector2f dir = end - start;
	float dirL = dir.length();
	std::cout << dirL << "\n";
	if (dir.length() == 0.f) return false;
	dir = dir.normalized();

	int mX = dir.x >= 0.f ? 1 : 0;
	int mY = dir.y >= 0.f ? 1 : 0;

	sf::Vector2f tilePos = sf::Vector2f((int)start.x / 32.f, (int)start.y / 32.f);
	sf::Vector2f pos = start;
	for (int i = 0; i < MAX_STEPS; i++) {
		float dX = mX * TILE_SIZE - (pos.x - tilePos.x * TILE_SIZE);
		float dY = mY * TILE_SIZE - (pos.y - tilePos.y * TILE_SIZE);

		float tX = dX / dir.x;
		float tY = dY / dir.y;

		if (tX <= tY) {
			tilePos.x += -1 + 2 * mX;
			time += tX;
			pos += dir * tX;
			normal = sf::Vector2f(1 - 2 * mX, 0.f);
		}
		else {
			tilePos.y += -1 + 2 * mY;
			time += tY;
			pos += dir * tY;
			normal = sf::Vector2f(0.f, 1 - 2 * mY);
		}
		if (time >= dirL) {
			time = fminf(time, dirL);
			std::cout << "END 02\n";
			return false;
		}
		if (tiles_img.getPixel(sf::Vector2u(tilePos.x, tilePos.y)).r <= 10) {
			//time /= dirL;
			std::cout << "END 01\n";
			return true;
		}
		
	}
	return false;
}

sf::Vector2u game::tileMap::convertToMapPos(sf::Vector2f pos) const {
	sf::Vector2f tilePos = sf::Vector2f(pos.x / 32.f, pos.y / 32.f);

	// equivalent to clamping (as I don't made any function for clamping yet), to change later maybe
	tilePos.x = fminf(size.x - 1, fmaxf(0, tilePos.x));
	tilePos.y = fminf(size.y - 1, fmaxf(0, tilePos.y));

	return sf::Vector2u(tilePos.x, tilePos.y);
}