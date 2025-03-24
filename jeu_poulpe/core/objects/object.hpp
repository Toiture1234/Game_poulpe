#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>

namespace game {
	class object {
	private :
		sf::Sprite albedoSP;
		sf::Sprite normalSP;

		

		bool colideable;
	public:
		// pbr variables, public for ease of access
		float roughness;

		object(sf::Texture* albedo_ptr, sf::Texture* normal_ptr) : 
			albedoSP(*albedo_ptr), normalSP(*normal_ptr)
		{
			colideable = false;
			roughness = 1.f;
		}

		void draw(sf::RenderTexture* renderTex, sf::Shader* shaderUsed);
		void setTextures(sf::Texture* albedo_ptr, sf::Texture* normal_ptr);
		void setPosition(sf::Vector2f position);

		sf::Vector2f getPosition() const { return albedoSP.getPosition(); }
	};
};