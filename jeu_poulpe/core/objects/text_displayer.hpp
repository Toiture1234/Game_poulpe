#pragma once

// important to note that ONE line in a dialogue box is EXACTLY 52 characters

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
			drawingText = nullptr;
		}
		textDiplayer(sf::Texture* albedo, sf::Texture* normal) {
			objRef = new object(albedo, normal);
			isShowingText = false;
			possibleInteraction = false;
			littleTriangle = nullptr;
			drawingText = nullptr;
		}
		
		void setText(std::string txt);
		void onUpdate(playable& player, bool& stopMvmt);
		void draw(renderingObject* renderTex, float runTime, sf::Vector2f playerPos, int stage); // stage 0 is the sign on tilemap, stage 1 is dialogue box

		sf::Vector2f position;
		object* littleTriangle;
		sf::Text* drawingText;
	};
}