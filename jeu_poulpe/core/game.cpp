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
	objectAtlas.push_back(object(&textureAtlas.at(NULLTEX_WHITE), &textureAtlas.at(NULLTEX_WHITE)));
	objectAtlas.at(0).setPosition(sf::Vector2f(0, 50));
	objectAtlas.push_back(object(&textureAtlas.at(STARS_BKG), &textureAtlas.at(STARS_BKG)));

	// init text displayers
	text_dspAtlas.push_back(textDiplayer(&textureAtlas.at(SIGN), &textureAtlas.at(SIGN)));
	text_dspAtlas.at(0).position = sf::Vector2f(5 * TILE_SIZE, 4 * TILE_SIZE);
	text_dspAtlas.at(0).littleTriangle = new object(&textureAtlas.at(SIGN_TRIANGLE), &textureAtlas.at(SIGN_TRIANGLE));
	text_dspAtlas.at(0).drawingText = new sf::Text(fontAtlas.at(0));
	text_dspAtlas.at(0).setText("Hello, welcome in my game !! Press Escape \nto exit :)");
	

	// init player better this way so the player is not dependent to an object
	player = playable(&textureAtlas.at(NULLTEX), &textureAtlas.at(NULLTEX));
	player.canMove = true;
	player.applyGravity = true;
	player.position = sf::Vector2f(48.f, 48.f);

	// init view ptr
	worldView.setCenter(player.position);

	// init tilemap
	worldTilemap.loadtilemap("assets/textures/tilemap/test_tilemap.png");
	worldTilemap.usedTileSet = tileSet(&textureAtlas.at(5), &textureAtlas.at(5));
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
	textureAtlas.push_back(sf::Texture("assets/textures/tilemap/tiles_v0.png")); // 5

	// load fonts
	fontAtlas.push_back(sf::Font("assets/font/minecraft-regular.ttf"));
}
void game::gameClass::initShaders() {
	if (!sf::Shader::isAvailable()) {
		std::cout << "ERROR -- SHADERS AREN'T AVAILABLE\n";
		return;
	}

	dark.loadFromFile("assets/shaders/VertexShader.glsl", "assets/shaders/FragmentShader.glsl");
	dark.setUniform("texture", sf::Shader::CurrentTexture);
	dark.setUniform("playerPosition", player.position);
}
void game::gameClass::initRenderTexContext() {
	if (!gameRenderTexture.resize(sf::Vector2u(*windowW_ptr, *windowH_ptr))) {
		std::cout << "Failed to resize renderTex !!\n"; // a bit of debugging :)
	}
	gameRenderTexture.setView(worldView);
}

// this function will become really big I guess
void game::gameClass::onUpdate() {
	gameRenderTexture.clear(sf::Color::Blue);

	sf::Vector2f centerPos = player.position + sf::Vector2f(16, -16);
	centerPos.x = fminf(fmaxf(centerPos.x, 7 * 32), (WORLD_SIZE - 7) * 32);
	centerPos.y = fminf(fmaxf(centerPos.y, 4 * 32), (WORLD_SIZE - 4) * 32);
	
	// game logic
	if(!stopMovement) player.move(*deltaT_ptr, worldTilemap);
	dark.setUniform("playerPosition", player.position - centerPos);

	text_dspAtlas.at(0).onUpdate(player, stopMovement);

	// update view
	
	worldView.setCenter(centerPos);
	gameRenderTexture.setView(worldView);

	worldTilemap.drawTilemap(&gameRenderTexture, centerPos);
	text_dspAtlas.at(0).draw(&gameRenderTexture, *runT_ptr, centerPos);
	player.draw(&gameRenderTexture, nullptr);
}
void game::gameClass::drawToWindow(sf::RenderWindow* window) {
	gameRenderTexture.display();

	// copy to a sprite to render to window, todo : create the sprite once and reuse it
	sf::Sprite drawer(gameRenderTexture.getTexture());
	window->draw(drawer, &dark);
}