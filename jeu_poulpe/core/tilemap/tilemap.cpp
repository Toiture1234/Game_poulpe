#include "tilemap.hpp"

//////////////////////////////////////////////////// main tilemap class ////////////////////////////////////////////////////

// consider the position given is the world position
int game::tileMap::readTile(sf::Vector2f pos) const {
	sf::Vector2f tilePos = sf::Vector2f(pos.x / 32.f, pos.y / 32.f);

	// equivalent to clamping (as I don't made any function for clamping yet), to change later maybe
	tilePos.x = fminf(size.x - 1, fmaxf(0, tilePos.x));
	tilePos.y = fminf(size.y - 1, fmaxf(0, tilePos.y));

	int idx = convertToIndex(sf::Vector2u(tilePos.x, tilePos.y));

#if READ_FROM_IMAGE
	// read only the red channel, this allows to have 255 different indicies, it should be enough
	return tiles_img.getPixel(sf::Vector2u(tilePos.x, tilePos.y)).r;
#else
	return pixelArray[idx];
#endif
}

// read from the position in image space
int game::tileMap::readTileDirect(sf::Vector2u pos) const {
#if READ_FROM_IMAGE
	// read only the red channel, this allows to have 255 different indicies, it should be enough
	return tiles_img.getPixel(pos).r;
#else
	return pixelArray[convertToIndex(pos)];
#endif
}

// basically the same as the constructor
void game::tileMap::loadtilemap(std::string path) {
	if (!tiles_img.loadFromFile(path)) std::cout << "ERROR -- UNABLE TO LOAD TILEMAP\n";
	size = tiles_img.getSize();
	pixelArray = tiles_img.getPixelsPtr();
}

void game::tileMap::drawTilemap(sf::RenderTexture* renderTex, sf::Vector2f viewCenter) {

	// 7 for x and 5 for y 
	sf::Vector2f position0 = viewCenter - sf::Vector2f(32 * 7, 5 * 32);
	position0.x = floorf(position0.x / 32.f) * 32.f;
	position0.y = floorf(position0.y / 32.f) * 32.f;

	// trying to do dual grid system
	for (int x = 0; x < 15; x++) {
		for (int y = 0; y < 10; y++) {
			sf::Vector2f currentPosition = position0 + sf::Vector2f(x, y) * 32.f + sf::Vector2f(16, 16);
			
			// read neighbourg tiles
			bool up_left = readTile(currentPosition) == SOLID_0;
			bool up_right = readTile(currentPosition + sf::Vector2f(32.f,0.f)) == SOLID_0;
			bool down_left = readTile(currentPosition + sf::Vector2f(0., 32.f)) == SOLID_0;
			bool down_right = readTile(currentPosition + sf::Vector2f(32.f, 32.f)) == SOLID_0;
			
			// draw bare terrain
			sf::IntRect toSelect = EMPTY;
			if (up_left || up_right || down_left || down_right) {
				if (up_left && up_right && down_left && down_right) toSelect = FULL;

				else if (up_left && up_right && !down_left && !down_right) toSelect = DOWN;
				else if (!up_left && !up_right && down_left && down_right) toSelect = UP;
				else if (up_left && !up_right && down_left && !down_right) toSelect = RIGHT;
				else if (!up_left && up_right && !down_left && down_right) toSelect = LEFT;

				else if (!up_left && up_right && down_left && down_right) toSelect = CORNER_UP_LEFT;
				else if (up_left && !up_right && down_left && down_right) toSelect = CORNER_UP_RIGHT;
				else if (up_left && up_right && !down_left && down_right) toSelect = CORNER_DOWN_LEFT;
				else if (up_left && up_right && down_left && !down_right) toSelect = CORNER_DOWN_RIGHT;

				else if (up_left && !up_right && !down_left && !down_right) toSelect = DOWN_RIGHT;
				else if (!up_left && up_right && !down_left && !down_right) toSelect = DOWN_LEFT;
				else if (!up_left && !up_right && down_left && !down_right) toSelect = UP_RIGHT;
				else if (!up_left && !up_right && !down_left && down_right) toSelect = UP_LEFT;

				else if (!up_left && up_right && down_left && !down_right) toSelect = DIAGONAL_RIGHT_LEFT;
				else if (up_left && !up_right && !down_left && down_right) toSelect = DIAGONAL_LEFT_RIGHT;


				usedTileSet.draw(renderTex, currentPosition, toSelect);
			} 
			{ // draw another type of decor
				// read the direct tile --> do not use offset grid based system
				currentPosition = currentPosition - sf::Vector2f(16, 16);

				int tileIdx = readTile(currentPosition);

				if (tileIdx == LADDER) usedTileSet.draw(renderTex, currentPosition, LADDER_);
			}
		}
	}
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
int game::tileMap::convertToIndex(sf::Vector2u mapPos) const {
	return (mapPos.x + mapPos.y * size.x) * 4;
}