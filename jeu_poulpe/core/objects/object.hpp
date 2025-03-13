#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>

namespace game {
	class object_t {
	private:
		// pointer to textures so I don't need to load a texture for every sprite
		// the goal here is to have a dynamic lightning on objects
		// albedo texture
		sf::Texture* albedo;
		
		// normal texture
		sf::Texture* normal;

		// roughness texture
		sf::Texture* roughness;

		// if the object will collide with others, todo : implement AABB collisions
		bool collideable;
	public:
		// needed to be able to draw anything
		sf::Texture spriteNULLTexture = sf::Texture("assets/textures/null.png");
		sf::Sprite objSprite;

		object_t() : objSprite(spriteNULLTexture) { // idk what's going on with the constructor but that's really annoying
			collideable = false;
			albedo = nullptr;
			normal = nullptr;
			roughness = nullptr;
		}

		void setPtrs(sf::Texture* a_ptr, sf::Texture* n_ptr, sf::Texture* r_ptr);

		// I hesitate on the method here, I can return a pointer to the sprite so I draw it later or I draw directly on renderTexture
		void draw(sf::RenderTexture* renderTex, sf::Shader* shader);

		
	};
};