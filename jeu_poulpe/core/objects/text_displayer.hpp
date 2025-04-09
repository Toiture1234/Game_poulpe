#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "../constants.hpp"
#include "object.hpp"
#include "playable.hpp"

namespace game {
	class textDiplayer {
	private:
		object* objRef;

		std::string text;
		bool isShowingText;
		bool possibleInteraction;
	public:
		textDiplayer() {
			objRef = nullptr;
			isShowingText = false;
			possibleInteraction = false;
			littleTriangle = nullptr;
		}
		textDiplayer(sf::Texture* albedo, sf::Texture* normal) {
			objRef = new object(albedo, normal);
			isShowingText = false;
			possibleInteraction = false;
			littleTriangle = nullptr;
		}
		
		void setText(std::string txt);
		void onUpdate(playable& player, bool& stopMvmt);
		void draw(sf::RenderTexture* renderTex, float runTime);

		sf::Vector2f position;
		object* littleTriangle;
	};
}