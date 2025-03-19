#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>

namespace game {
	class object {
	private :
		sf::Sprite albedoSP;
		sf::Sprite normalSP;
		sf::Sprite roughSP;

		bool colideable;
	public:
		object(sf::Texture* albedo_ptr, sf::Texture* normal_ptr, sf::Texture* rough_ptr) : 
			albedoSP(*albedo_ptr), normalSP(*normal_ptr), roughSP(*rough_ptr) 
		{
			colideable = false;
		}

		void draw(sf::RenderTexture* renderTex, sf::Shader* shaderUsed);
		void setTextures(sf::Texture* albedo_ptr, sf::Texture* normal_ptr, sf::Texture* rough_ptr);
		void setPosition(sf::Vector2f position);

		sf::Vector2f getPosition() const { return albedoSP.getPosition(); }
	};
};