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
	velocity.x = 80;
	velocity.y = 0;

	if (abs(player.GetPosition().x - body.getPosition().x) <= 500.0f)
	{
		if (player.GetPosition().x > body.getPosition().x)
		{
			body.move(velocity * deltaTime);
			faceRight = 1;
			
		}
		else if (player.GetPosition().x < body.getPosition().x)
		{
			
			body.move(-velocity * deltaTime);
			faceRight = 0;
		}
	}

	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
}

void Enemy::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}