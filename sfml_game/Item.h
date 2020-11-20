#pragma once
#include<SFML/Graphics.hpp>
#include "Animation.h"
#include "Collider.h"
#include "Player.h"
class Item
{
public:
	Item(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float x, float y);
	~Item();

	void Update(float deltaTime, Player player);
	void Draw(sf::RenderWindow& window);
	sf::Vector2f GetPosition() { return	body.getPosition(); }
	int iscollide()
	{
		if (item == 1) {
			item--;
			return 1;
		}
	}
	Collider GetCollider() { return Collider(body); }

private:
	sf::RectangleShape body;
	Animation animation;
	unsigned int row;
	int item;
	int collide;
	bool faceRight;
};