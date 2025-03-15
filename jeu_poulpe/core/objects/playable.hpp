#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "../constants.hpp"
#include "object.hpp"

namespace game {
	class playable {
	private:
		// temporary texture just for initialisation, 
		// it has to be placed before the object idk why
		// we should avoid loading the texture in the class but there's only one player, so other stuff would use std::vector
		sf::Texture tmpTexture;
		object objRef;

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
		playable() : tmpTexture("assets/textures/null.png"), objRef(&tmpTexture, &tmpTexture, &tmpTexture) {
			canMove = false;
			applyGravity = false;
		}
		// same for this one
		playable(bool isMoving, bool apply_gravity) : tmpTexture("assets/textures/null.png"), objRef(&tmpTexture, &tmpTexture, &tmpTexture) {
			canMove = isMoving;
			applyGravity = apply_gravity;
		}
		// use this one if you already have the textures
		playable(sf::Texture* albedo_ptr, sf::Texture* normal_ptr, sf::Texture* rough_ptr) : objRef(albedo_ptr, normal_ptr, rough_ptr) {
			canMove = false;
			applyGravity = false;
		}

		void setTextures(sf::Texture* albedo_ptr, sf::Texture* normal_ptr, sf::Texture* rough_ptr);
		void move(float delta_time);
		void draw(sf::RenderTexture* renderTex, sf::Shader* shader);

		
	};
}