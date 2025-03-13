#include "game.hpp"

void game::gameClass::init(float* dtPtr, float* rtPtr, unsigned int* wW, unsigned int* wH) {
	// init pointers 
	this->deltaT_ptr = dtPtr;
	this->runT_ptr = rtPtr;
	this->windowW_ptr = wW;
	this->windowH_ptr = wH;

	initTextures();
	initShaders();
	initRenderTexContext();

	std::cout << "Game initialisation done !!\n";
}
void game::gameClass::initTextures() {
	// load every texture and push back to vector
}
void game::gameClass::initShaders() {

}
void game::gameClass::initRenderTexContext() {
	if (!gameRenderTexture.resize(sf::Vector2u(*windowW_ptr, *windowH_ptr))) {
		std::cout << "Failed to resize renderTex !!\n"; // a bit of debugging :)
	}
	// view is currently positionned using left-up, idk if I'll change this later
	worldView = sf::View(sf::FloatRect(sf::Vector2f(view_posX, view_posY), sf::Vector2f(view_width, view_height)));
	gameRenderTexture.setView(worldView);
}

// this function will become really big I guess
void game::gameClass::onUpdate() {
	gameRenderTexture.clear();

	// keep track of user input
	
	// game logic
	
	// drawing to render texture
	gameRenderTexture.draw(test);
	std::cout << "Game updated !!\n";
}
void game::gameClass::drawToWindow(sf::RenderWindow* window) {
	gameRenderTexture.display();

	// copy to a sprite to render to window, todo : create the sprite once and reuse it
	sf::Sprite drawer(gameRenderTexture.getTexture());
	window->draw(drawer);
}