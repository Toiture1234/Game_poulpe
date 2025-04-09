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

	// init objects
	objectAtlas.push_back(object(&textureAtlas.at(1), &textureAtlas.at(0)));
	objectAtlas.at(0).setPosition(sf::Vector2f(0, 50));
	objectAtlas.push_back(object(&textureAtlas.at(2), &textureAtlas.at(0)));

	// init text displayers
	text_dspAtlas.push_back(textDiplayer(&textureAtlas.at(3), &textureAtlas.at(3)));
	text_dspAtlas.at(0).position = sf::Vector2f(5 * TILE_SIZE, 4 * TILE_SIZE);
	text_dspAtlas.at(0).littleTriangle = new object(&textureAtlas.at(4), &textureAtlas.at(4));

	// init player better this way so the player is not dependent to an object
	player = playable(&textureAtlas.at(0), &textureAtlas.at(0));
	player.canMove = true;
	player.applyGravity = true;
	player.position = sf::Vector2f(48.f, 48.f);

	// init view ptr
	worldView.setCenter(player.position);

	// init tilemap
	worldTilemap.loadtilemap("assets/textures/tilemap/test_tilemap.png");
	std::cout << "Game initialisation done !!\n";
}
void game::gameClass::initTextures() {
	// load every texture and push back to vector
	sf::Texture tmp("assets/textures/null.png");
	textureAtlas.push_back(tmp); // 0
	textureAtlas.push_back(sf::Texture("assets/textures/nullw.png")); // 1
	textureAtlas.push_back(sf::Texture("assets/textures/background.png")); // 2
	textureAtlas.push_back(sf::Texture("assets/textures/objects/basic_sign.png")); // 3
	textureAtlas.push_back(sf::Texture("assets/textures/misc/triangle_txt.png")); // 4
}
void game::gameClass::initShaders() {

}
void game::gameClass::initRenderTexContext() {
	if (!gameRenderTexture.resize(sf::Vector2u(*windowW_ptr, *windowH_ptr))) {
		std::cout << "Failed to resize renderTex !!\n"; // a bit of debugging :)
	}
	// view is currently positionned using left-up, idk if I'll change this later
	//worldView = sf::View(sf::FloatRect(sf::Vector2f(view_posX, view_posY), sf::Vector2f(view_width, view_height)));
	gameRenderTexture.setView(worldView);
}

// this function will become really big I guess
void game::gameClass::onUpdate() {
	gameRenderTexture.clear();

	// keep track of user input
	
	// game logic
	if(!stopMovement) player.move(*deltaT_ptr, worldTilemap);

	text_dspAtlas.at(0).onUpdate(player, stopMovement);

	// update view
	worldView.setCenter(player.position + sf::Vector2f(16, 16));
	gameRenderTexture.setView(worldView);
	
	// drawing to render texture
	// this would use a loop soon so I have to take care I which order I put my objects
	// maybe I can make separated vectors for differents planes
	//objectAtlas.at(1).draw(&gameRenderTexture, nullptr);
	//objectAtlas.at(0).draw(&gameRenderTexture, nullptr);

	worldTilemap.drawTilemap(&gameRenderTexture);

	text_dspAtlas.at(0).draw(&gameRenderTexture, *runT_ptr);

	player.draw(&gameRenderTexture, nullptr);
}
void game::gameClass::drawToWindow(sf::RenderWindow* window) {
	gameRenderTexture.display();

	// copy to a sprite to render to window, todo : create the sprite once and reuse it
	sf::Sprite drawer(gameRenderTexture.getTexture());
	window->draw(drawer);
}