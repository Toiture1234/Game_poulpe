#include "object.hpp"

void game::object::draw(sf::RenderTexture* renderTex, sf::Shader* shaderUsed) {
	renderTex->draw(albedoSP);
}
void game::object::setTextures(sf::Texture* albedo_ptr, sf::Texture* normal_ptr) {
	albedoSP.setTexture(*albedo_ptr);
	normalSP.setTexture(*normal_ptr);
}
void game::object::setPosition(sf::Vector2f position) {
	albedoSP.setPosition(position);
	normalSP.setPosition(position);
}