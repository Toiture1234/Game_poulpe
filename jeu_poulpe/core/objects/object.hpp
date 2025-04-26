#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>

namespace game {
	// drawing handle class
	class renderingObject {
	public:
		sf::RenderTexture albedoTexture;
		sf::RenderTexture normalTexture;
		sf::RenderTexture depthTexture; // actually has info about material properties like roughness, emmisive (albedo color), BRDF response, etc

		bool resize(sf::Vector2u size);

		void setView(sf::View& view);

		void clear(sf::Color clearColor0, sf::Color clearColor1, sf::Color clearColor2);
	};

	class object {
	public:
		// pbr variables, public for ease of access
		float roughness;
		sf::Sprite albedoSP;
		sf::Sprite normalSP;

		bool colideable;

		object(sf::Texture* albedo_ptr, sf::Texture* normal_ptr) : 
			albedoSP(*albedo_ptr), normalSP(*normal_ptr)
		{
			colideable = false;
			roughness = 1.f;
		}

		void draw(renderingObject* renderTex, sf::Shader* shaderUsed);
		void setTextures(sf::Texture* albedo_ptr, sf::Texture* normal_ptr);
		void setPosition(sf::Vector2f position);

		sf::Vector2f getPosition() const { return albedoSP.getPosition(); }
	};
};