#include "object.hpp"

void game::object_t::setPtrs(sf::Texture* a_ptr, sf::Texture* n_ptr, sf::Texture* r_ptr) {
	albedo = a_ptr, normal = n_ptr, roughness = r_ptr;
	//objSprite.setTexture(*albedo);
	objSprite.setTexture(spriteNULLTexture);
}

void game::object_t::draw(sf::RenderTexture* renderTex, sf::Shader* shader) {
	// renderTex->draw(objSprite, shader);
	sf::Sprite oS(spriteNULLTexture);
	renderTex->draw(objSprite);
}