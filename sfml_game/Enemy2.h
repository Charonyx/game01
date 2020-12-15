#pragma once
#include<SFML/Graphics.hpp>
#include "Animation.h"
#include "Collider.h"
#include "Player.h"
class Enemy2
{
public:
	Enemy2(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float x, float y);
	~Enemy2();

	void Update2(float deltaTime, Player player);
	void Draw(sf::RenderWindow& window);
	void OnCollision(sf::Vector2f direction);
	sf::Vector2f GetPosition() { return	body.getPosition(); }
	Collider GetCollider() { return Collider(body); }

private:
	sf::RectangleShape body;
	Animation animation;
	unsigned int row;
	float speed;
	bool faceRight;

	sf::Vector2f velocity;

};