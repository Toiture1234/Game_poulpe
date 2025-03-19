#include "playable.hpp"

void game::playable::setTextures(sf::Texture* albedo_ptr, sf::Texture* normal_ptr, sf::Texture* rough_ptr) {
	objRef->setTextures(albedo_ptr, normal_ptr, rough_ptr);
}
void game::playable::move(float delta_time) {
	// derived from the Newton's second law
	// in m.s^(-2)
	sf::Vector2f baseAcceleration = applyGravity ? sf::Vector2f(0.f, 9.81f) : sf::Vector2f(0.f, 0.f); 

	// friction force in air, using stokes's law, this is theorically incorect but this is a game
	// this means F = -6*pi*airViscosity*radius*velocity
	// this almost does nothing but who cares
	// TODO : have multiple frictions forces (for floor, etc)
	baseAcceleration += sf::Vector2f(-6.f * m_PI * airViscosity * 0.5f * velocity.x / mass, -6.f * m_PI * airViscosity * 0.5f * velocity.y / mass);

	// key inputs
	if (canMove) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
			baseAcceleration.y += -30.f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
			baseAcceleration.y += 30.f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
			baseAcceleration.x += 30.f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
			baseAcceleration.x -= 30.f;
		}
	}

	// calculations
	velocity += baseAcceleration * delta_time; // this gives m.s^(-1)
	position += velocity * delta_time; // this gives m

	objRef->setPosition(position);
}
void game::playable::draw(sf::RenderTexture* renderTex, sf::Shader* shader) {
	objRef.draw(renderTex, shader);
}