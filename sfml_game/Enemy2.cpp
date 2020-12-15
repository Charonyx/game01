#include "Enemy2.h"

Enemy2::Enemy2(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float x, float y) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 0;
	faceRight = true;

	body.setSize(sf::Vector2f(65.0f, 50.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(x, y);
	body.setTexture(texture);

	//this->enemyHP.setSize(sf::Vector2f(60, 5));
	//this->enemyHP.setFillColor(sf::Color::Red);

	//this->enemyHPBack = this->enemyHP;
	//this->enemyHPBack.setFillColor(sf::Color::Black);
}
Enemy2::~Enemy2()
{
}

void Enemy2::Update2(float deltaTime, Player player)
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

void Enemy2::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
void Enemy2::OnCollision(sf::Vector2f direction)
{
	if (direction.x < 0.0f)
	{
		//Collision on the left.
		velocity.x = 0.0f;
	}
	else if (direction.x > 0.0f)
	{
		//Collision on the right.
		velocity.x = 0.0f;
	}
	if (direction.y < 0.0f)
	{
		//Collision on the bottom.
		velocity.y = 0.0f;

	}
	else if (direction.y > 0.0f)
	{
		//Collision on the top.
		velocity.y = 0.0f;
	}
}
