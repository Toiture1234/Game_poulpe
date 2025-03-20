#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "../constants.hpp"
#include "object.hpp"

namespace game {
	class playable {
	private:
		// reference to drawable object
		object* objRef;

		// moving related stuff
		// player's velocity
		sf::Vector2f velocity;
		// player's position
		sf::Vector2f position;

		// physical constants
		// hardcoded now but this is maybe planned to change
		
		// player's mass in kg
		float mass = 1.f;

	public:
		bool canMove;
		bool applyGravity;

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
		playable(sf::Texture* albedo, sf::Texture* normal, sf::Texture* rough){
			canMove = false;
			applyGravity = false;
			objRef = new object(albedo, normal, rough);
		}

		void setTextures(sf::Texture* albedo_ptr, sf::Texture* normal_ptr, sf::Texture* rough_ptr);
		void move(float delta_time);
		void draw(sf::RenderTexture* renderTex, sf::Shader* shader);

		sf::Vector2f* getPosition_ptr() const { return (sf::Vector2f*)&position; };
	};
}