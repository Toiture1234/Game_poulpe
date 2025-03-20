#include "follow_view.hpp"

void game::followView::onUpdate(sf::RenderTexture* renderTex) {
	view.setCenter(*pos_ptr);
	renderTex->setView(view); // have to update the view on the render texture
}
void game::followView::setPtr(sf::Vector2f* ptr) {
	pos_ptr = ptr;
}