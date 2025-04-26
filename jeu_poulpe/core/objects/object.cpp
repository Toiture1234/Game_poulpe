#include "object.hpp"

bool game::renderingObject::resize(sf::Vector2u size) {
	if (!albedoTexture.resize(size))return false;
	if (!normalTexture.resize(size))return false;
	if (!depthTexture.resize(size))return false;
};
void game::renderingObject::setView(sf::View& view) {
	albedoTexture.setView(view);
	normalTexture.setView(view);
	depthTexture.setView(view);
};
void game::renderingObject::clear(sf::Color clearColor0, sf::Color clearColor1, sf::Color clearColor2) {
	albedoTexture.clear(clearColor0);
	normalTexture.clear(clearColor1);
	depthTexture.clear(clearColor2);
}

void game::object::draw(renderingObject* renderTex, sf::Shader* shaderUsed) {
	renderTex->albedoTexture.draw(albedoSP);
}
void game::object::setTextures(sf::Texture* albedo_ptr, sf::Texture* normal_ptr) {
	albedoSP.setTexture(*albedo_ptr);
	normalSP.setTexture(*normal_ptr);
}
void game::object::setPosition(sf::Vector2f position) {
	albedoSP.setPosition(position);
	normalSP.setPosition(position);
}

