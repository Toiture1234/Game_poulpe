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
	// we don't have any objects now so...

	// init text displayers
	text_dspAtlas.push_back(textDiplayer(&textureAtlas.at(SIGN), &textureAtlas.at(SIGN)));
	text_dspAtlas.at(0).position = sf::Vector2f(5 * TILE_SIZE, 4 * TILE_SIZE);
	text_dspAtlas.at(0).littleTriangle = new object(&textureAtlas.at(SIGN_TRIANGLE), &textureAtlas.at(SIGN_TRIANGLE));
	text_dspAtlas.at(0).drawingText = new sf::Text(fontAtlas.at(0));
	text_dspAtlas.at(0).setText("Hello, welcome in my game !! Press Escape to exit \n:)");

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

	if (!dark.loadFromFile("assets/shaders/VertexShader.glsl", "assets/shaders/FragmentShader.glsl")) std::cout << "FAILED TO LOAD SHADER\n";
	dark.setUniform("texture", sf::Shader::CurrentTexture);
	dark.setUniform("offset", sf::Vector2f(0.f, 0.f));
	dark.setUniform("w_resolution", sf::Vector2f(*windowW_ptr, *windowH_ptr));
}
void game::gameClass::initRenderTexContext() {
	if (!gameRenderingObject.resize(sf::Vector2u(*windowW_ptr, *windowH_ptr))) {
		std::cout << "Failed to resize renderTex !!\n"; // a bit of debugging :)
	}
	gameRenderingObject.setView(worldView);

	if (!GUI_renderTexture.resize(sf::Vector2u(*windowW_ptr, *windowH_ptr))) {
		std::cout << "Failed to resize renderTex !!\n"; // a bit of debugging :)
	}
}

// this function will become really big I guess
void game::gameClass::onUpdate() {
	gameRenderingObject.clear(sf::Color::Blue, sf::Color::Black, sf::Color::Black);
	GUI_renderTexture.clear(sf::Color::Black, sf::Color::Black, sf::Color::Black);

	sf::Vector2f centerPos = player.position + sf::Vector2f(16, -16);
	centerPos.x = fminf(fmaxf(centerPos.x, 7 * 32), (WORLD_SIZE - 7) * 32);
	centerPos.y = fminf(fmaxf(centerPos.y, 4 * 32), (WORLD_SIZE - 4) * 32);

	// have to calculate the offset between player position and camera position
	sf::Vector2f difference = centerPos - player.position;
	difference.x /= view_width;
	difference.y /= view_height;
	std::cout << difference.x << " " << difference.y << "\n";
	
	// game logic
	if(!stopMovement) player.move(*deltaT_ptr, worldTilemap);
	dark.setUniform("offset", difference);

	text_dspAtlas.at(0).onUpdate(player, stopMovement);

	// update view
	worldView.setCenter(centerPos);
	gameRenderingObject.setView(worldView);

	// drawing, phase 1
	worldTilemap.drawTilemap(&gameRenderingObject, centerPos);
	text_dspAtlas.at(0).draw(&gameRenderingObject, *runT_ptr, centerPos, 0);
	player.draw(&gameRenderingObject, nullptr);

	// draw to GUI renderTexture
	gameRenderingObject.albedoTexture.display();
	sf::Sprite drawer(gameRenderingObject.albedoTexture.getTexture());
	GUI_renderTexture.albedoTexture.draw(drawer, &dark);

	// draw GUI, drawing phase 2
	text_dspAtlas.at(0).draw(&GUI_renderTexture, *runT_ptr, sf::Vector2f(*windowW_ptr * 0.5f, *windowH_ptr * 0.5f), 1);
}
void game::gameClass::drawToWindow(sf::RenderWindow* window) {
	GUI_renderTexture.albedoTexture.display();

	// copy to a sprite to render to window, todo : create the sprite once and reuse it
	sf::Sprite drawer(GUI_renderTexture.albedoTexture.getTexture());
	// apply global shader
	window->draw(drawer);
}