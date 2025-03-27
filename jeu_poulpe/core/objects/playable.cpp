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

	// converion to m.s^(-2)
	baseAcceleration.x *= 32.f;
	baseAcceleration.y *= 32.f;

	// tilemap collision test
	float nearDistance = 1e10;
	sf::Vector2f normal = sf::Vector2f(0.f, 0.f);
	if (velocity.length() > 0.f) {
		sf::Vector2f normVelocity = velocity.normalized();

		sf::Vector2f normal0;
		sf::Vector2f normal1;
		sf::Vector2f normal2;
		sf::Vector2f normal3;

		float distUpLeft = refTileMap.intersect(position + sf::Vector2f(2.f,2.f), normVelocity, normal0);
		float distUpRight = refTileMap.intersect(position + sf::Vector2f(TILE_SIZE - 2, 2.f), normVelocity, normal1);
		float distDownLeft = refTileMap.intersect(position + sf::Vector2f(2.f, TILE_SIZE - 2), normVelocity, normal2);
		float distDownRight = refTileMap.intersect(position + sf::Vector2f(TILE_SIZE - 2, TILE_SIZE - 2), normVelocity, normal3);
		nearDistance = fminf(distUpLeft, fminf(distUpRight, fminf(distDownLeft, distDownRight)));

		if (distUpLeft <= distUpRight && distUpLeft <= distDownLeft && distUpLeft <= distDownRight) {
			normal = normal0;
			std::cout << "NORMAL0\n" << normal.x << " " << normal.y << "\n";
		}
		else if (distUpRight <= distUpLeft && distUpRight <= distDownLeft && distUpRight <= distDownRight) {
			normal = normal1;
			std::cout << "NORMAL1\n" << normal.x << " " << normal.y << "\n";
		}
		else if (distDownLeft <= distUpLeft && distDownLeft <= distUpRight && distDownLeft <= distDownRight) {
			normal = normal2;
			std::cout << "NORMAL2\n" << normal.x << " " << normal.y << "\n";
		}
		else if (distDownRight <= distUpLeft && distDownRight <= distUpRight && distDownRight <= distDownLeft) {
			normal = normal3;
			std::cout << "NORMAL3\n" << normal.x << " " << normal.y << "\n";
		}

		std::cout << position.x / 32.f << " " << position.y / 32.f << "\n";
	}
	// calculations
	velocity += baseAcceleration * delta_time; // this gives m.s^(-1)
	
	sf::Vector2f translationFactor = velocity * delta_time;

	bool hit = false;
	if (translationFactor.length() >= nearDistance) { // we are gonna hit the surface
		hit = true;
		translationFactor *= fminf(nearDistance / translationFactor.length(), 1.f); // make sure it doesn't go to infinity
	}

	// add translation factor to position
	position += translationFactor;

	if (hit) {
		//position += normal;
		position -= velocity * delta_time * 2.f;
		velocity = sf::Vector2f(0.f,0.f);
		std::cout << "HIT : " << normal.x << " " << normal.y << "\n";
	}

	objRef->setPosition(position);
}
void game::playable::draw(sf::RenderTexture* renderTex, sf::Shader* shader) {
	objRef->draw(renderTex, shader);
}