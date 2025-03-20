#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "constants.hpp"

namespace game {
	// a kinda small class used to make a specific position following view
	// it can follow any position of any object (if the variable is still in the memory)
	class followView {
	private:
		// this is a pointer to the direction we want to follow
		sf::Vector2f* pos_ptr;
	public:
		followView() {
			pos_ptr = nullptr;
		}
		followView(sf::Vector2f* ptr, sf::View View) {
			pos_ptr = ptr;
			this->view = View;
		}

		void onUpdate(sf::RenderTexture* renderTex);
		void setPtr(sf::Vector2f* ptr);

		// the view this is refered to
		// made public for sake of ease
		sf::View view;
	};
}