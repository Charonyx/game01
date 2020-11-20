#include "Item.h"

Item::Item(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float x, float y) :
	animation(texture, imageCount, switchTime)
{
	row = 0;
	item = 0;
	collide = 0;
	body.setSize(sf::Vector2f(65.0f, 50.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(x, y);
	body.setTexture(texture);
}
Item::~Item()
{
}

void Item::Update(float deltaTime, Player player)
{
	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
}

void Item::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}