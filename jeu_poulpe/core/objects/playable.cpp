#include "playable.hpp"

void game::playable::setTextures(sf::Texture* albedo_ptr, sf::Texture* normal_ptr) {
	objRef->setTextures(albedo_ptr, normal_ptr);
}
void game::playable::move(float delta_time, tileMap& refTileMap) {
	// derived from the Newton's second law
	// in px.s^(-2)
	sf::Vector2f baseAcceleration = applyGravity ? sf::Vector2f(0.f, 9.81f) : sf::Vector2f(0.f, 0.f); 

	// friction force in air, using stokes's law, this is theorically incorect but this is a game
	// this means F = -6*pi*airViscosity*radius*velocity
	// this almost does nothing but who cares
	// TODO : have multiple frictions forces (for floor, etc)
	baseAcceleration += sf::Vector2f(-6.f * m_PI * airViscosity * 0.5f * velocity.x / mass, -6.f * m_PI * airViscosity * 0.5f * velocity.y / mass);

	// tilemap collision test, switch to clamp based system
	// check 2 tiles for each point of the hitbox
	// position initialisation
	sf::Vector2u tileUL = refTileMap.convertToMapPos(position);
	sf::Vector2u tileUR = refTileMap.convertToMapPos(position + sf::Vector2f(32, 0));
	sf::Vector2u tileDL = refTileMap.convertToMapPos(position + sf::Vector2f(0, 32));
	sf::Vector2u tileDR = refTileMap.convertToMapPos(position + sf::Vector2f(32, 32));

	// 8 values
	bool leftUL = refTileMap.readTileDirect(tileUL - sf::Vector2u(1, 0)) <= 10;
	bool upUL = refTileMap.readTileDirect(tileUL - sf::Vector2u(0, 1)) <= 10;
	bool rightUR = refTileMap.readTileDirect(tileUR + sf::Vector2u(1, 0)) <= 10;
	bool upUR = refTileMap.readTileDirect(tileUR - sf::Vector2u(0, 1)) <= 10;
	bool leftDL = refTileMap.readTileDirect(tileDL - sf::Vector2u(1, 0)) <= 10;
	bool downDL = refTileMap.readTileDirect(tileDL + sf::Vector2u(0, 1)) <= 10;
	bool rightDR = refTileMap.readTileDirect(tileDR + sf::Vector2u(1, 0)) <= 10;
	bool downDR = refTileMap.readTileDirect(tileDR + sf::Vector2u(0, 1)) <= 10;

	// final test booleans
	bool up = upUL || upUR;
	bool down = downDL || downDR;
	bool left = leftUL || leftDL;
	bool right = rightUR || rightDR;

	bool touchingUp = up && tileUL.y * 32 - position.y > -0.006;
	bool touchingDown = down && position.y + 0.005 - tileDL.y * 32 > -0.006;
	bool touchingLeft = left && tileUL.x * 32 - position.x > -0.006;
	bool touchingRight = right && position.x + 0.005 - tileUR.x * 32 > -0.006;

	// key inputs
	if (canMove) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
			baseAcceleration.y += -10.f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
			baseAcceleration.y += 10.f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
			baseAcceleration.x += 10.f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
			baseAcceleration.x -= 10.f;
		}
	}

	// friction force of medium we're on
	if (touchingDown || touchingLeft || touchingRight || touchingUp)
		baseAcceleration += -velocity * 0.05f;
	
	// converion to m.s^(-2)
	baseAcceleration.x *= 32.f;
	baseAcceleration.y *= 32.f;

	// velocity change
	velocity += baseAcceleration * delta_time; // this works as long there is no single short events (like jumping)

	// velocity change factor
	if(touchingUp) { // we touch ceiling
		std::cout << "Up touching\n";
		velocity.y *= velocity.dot(sf::Vector2f(0, 1)) > 0.f ? 1.f : 0.f;
	}
	if(touchingDown) { // we touch floor
		std::cout << "Down touching\n";
		velocity.y *= velocity.dot(sf::Vector2f(0, -1)) > 0.f ? 1.f : 0.f; 
	}
	if(touchingLeft) { // we touch left wall
		std::cout << "Left touching\n";
		velocity.x *= velocity.dot(sf::Vector2f(1, 0)) > 0.f ? 1.f : 0.f;
	}
	if(touchingRight) { // we touch right wall
		std::cout << "Right touching\n"; 
		velocity.x *= velocity.dot(sf::Vector2f(-1, 0)) > 0.f ? 1.f : 0.f;
	}

	// I need the ability to change the velocity
	bool isJumping = canMove && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && touchingDown;
	if (isJumping) {
		velocity.y -= 144;
		std::cout << "ONE JUMP\n";
	}

	position += velocity * delta_time;
	if (isJumping) std::cout << velocity.y << " " << delta_time << "\n";
	std::cout << velocity.y << "\n";

	// we can use only one of the positions to clamp the values
	// maybe I can add optimisation but not now
	if (up) position.y = fmaxf(tileUL.y * 32 + 0.005f, position.y);
	if (down) position.y = fminf(tileDL.y * 32 - 0.005f, position.y);
	if (left) position.x = fmaxf(tileUL.x * 32 + 0.005f, position.x);
	if (right) position.x = fminf(tileUR.x * 32 - 0.005f, position.x);

	objRef->setPosition(position);
}
void game::playable::draw(sf::RenderTexture* renderTex, sf::Shader* shader) {
	objRef->draw(renderTex, shader);
}