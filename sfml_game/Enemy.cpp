#include "Enemy.h"

Enemy::Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float x, float y) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 0;
	faceRight = true;


	body.setSize(sf::Vector2f(65.0f, 50.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(x, y);
	body.setTexture(texture);
}
Enemy::~Enemy()
{
}

void Enemy::Update2(float deltaTime , Player player)
{
	velocity.x *= 80.0f;
	velocity.y *= 0.0f;


	if (abs(player.GetPosition().x - body.getPosition().x) <= 300)
	{
		if (player.GetPosition().x > body.getPosition().x)
		{
			body.move(velocity * deltaTime);
		}
		else if (player.GetPosition().x < body.getPosition().x)
		{
			body.move(-velocity * deltaTime);
		}
	}

	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
}

void Enemy::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}