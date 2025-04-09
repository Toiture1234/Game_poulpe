#include "text_displayer.hpp"

void game::textDiplayer::setText(std::string txt) {
	text.clear();
	text = txt;
}

void game::textDiplayer::onUpdate(playable& player, bool& stopMvmt) 
{
	objRef->setPosition(position);

	possibleInteraction = false;

	// check for distance to player
	float dst = (position - player.position).length();
	if (dst > TILE_SIZE * 1.5f) return;
	if (player.velocity.length() >= 64) return;

	possibleInteraction = true;

	// check for events
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) isShowingText = true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) isShowingText = false;

	if (isShowingText) {
		stopMvmt = true;
		possibleInteraction = false;
	}
	else {
		stopMvmt = false;
	}

}

void game::textDiplayer::draw(sf::RenderTexture* renderTex, float runTime) {
	objRef->draw(renderTex, nullptr);

	if (possibleInteraction) {
		int animHeight = int(sinf(runTime * 5.f) * 3);
		littleTriangle->setPosition(position + sf::Vector2f(12, -16 + animHeight));
		littleTriangle->draw(renderTex, nullptr);
	}

	// draw text
	if (isShowingText) {

	}
	else {

	}
}