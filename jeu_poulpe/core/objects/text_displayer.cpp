#include "text_displayer.hpp"

void game::textDiplayer::setText(std::string txt) {
	text.clear();
	text = txt;
	drawingText->setString(text);
	drawingText->scale({ 0.7, 0.7 });
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

// note that playerPos is the position of the center of the screen
void game::textDiplayer::draw(sf::RenderTexture* renderTex, float runTime, sf::Vector2f playerPos, int stage) {
	if (stage == 0) {
		objRef->draw(renderTex, nullptr);

		if (possibleInteraction) {
			int animHeight = int(sinf(runTime * 5.f) * 3);
			littleTriangle->setPosition(position + sf::Vector2f(12, -16 + animHeight));
			littleTriangle->draw(renderTex, nullptr);
		}
	}
	else {
		// draw text
		if (isShowingText) {
			/*sf::RectangleShape box({160, 80});
			box.setPosition(playerPos + sf::Vector2f(-64 * 5., -112));
			box.setFillColor(sf::Color::White);
			renderTex->draw(box);

			box.setSize({ 156, 76 });
			box.setPosition(playerPos + sf::Vector2f(-62, -110));
			box.setFillColor(sf::Color::Black);
			renderTex->draw(box);

			drawingText->setPosition(playerPos + sf::Vector2f(-64 + 4, -112 + 4));
			renderTex->draw(*drawingText);
			*/
			float y = 200;
			sf::RectangleShape box({ 640, 240 });
			box.setPosition({ 320, 240 - y});
			box.setFillColor(sf::Color::White);
			renderTex->draw(box);

			box.setSize({ 630, 230 });
			box.setPosition({ 325, 245 - y});
			box.setFillColor(sf::Color::Black);
			renderTex->draw(box);

			drawingText->setPosition({ 330, 250 - y });
			renderTex->draw(*drawingText);
		}
	}
}