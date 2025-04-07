#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "../constants.hpp"
#include "object.hpp"
#include "../tilemap/tilemap.hpp"

#define DEV_MODE 0

namespace game {
	class playable {
	private:
		// reference to drawable object
		object* objRef;

		// physical constants
		// hardcoded now but this is maybe planned to change
		// player's mass in kg
		float mass = 1.f;

	public:
		// player action manager (for cinematics etc)
		bool canMove;
		bool applyGravity;

		// moving related stuff
		// player's velocity
		sf::Vector2f velocity = sf::Vector2f(0, 0);
		// player's position
		sf::Vector2f position = sf::Vector2f(0, 0);

		// this constructor allows to declare a playable object without already knowing it's textures
		playable() {
			canMove = false;
			applyGravity = false;
			objRef = nullptr;
		}
		// same for this one
		playable(bool isMoving, bool apply_gravity)  {
			canMove = isMoving;
			applyGravity = apply_gravity;
			objRef = nullptr;
		}
		// use this one if you already have the textures
		playable(sf::Texture* albedo, sf::Texture* normal){
			canMove = false;
			applyGravity = false;
			objRef = new object(albedo, normal);
		}

		void setTextures(sf::Texture* albedo_ptr, sf::Texture* normal_ptr);
		void move(float delta_time, tileMap& refTileMap);
		void draw(sf::RenderTexture* renderTex, sf::Shader* shader);

		sf::Vector2f* getPosition_ptr() const { return (sf::Vector2f*)&position; };
		sf::Vector2f getVelocity() const { return velocity; };
		sf::Vector2f getPosition() const { return position; };
	};
}