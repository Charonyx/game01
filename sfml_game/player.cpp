#include "Player.h"


Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	this->jumpHeight = jumpHeight;
	row = 0;
	faceRight = true;
	crawl = 0;
	
	body.setSize(sf::Vector2f(65.0f, 50.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(9600.f, -360.0f);
	body.setTexture(texture);
}
Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	velocity.x *= 0.0f;
	this->delayCrawl += deltaTime;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		velocity.x -= speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		velocity.x += speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && canJump)
	{
		canJump = false;
		velocity.y = -sqrt(2.0f * 981.0f * jumpHeight);	
	}
//	printf("%f\n", this->delayCrawl);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J) && crawl == 0)
	{
		//velocity.x += speed;
		crawl = 1;
		this->delayCrawl = 0;
	}
	if (delayCrawl > 0.2 * 3) // switchTime * column (Player)
	{
		crawl = 0;
	}
	velocity.y += 981.0f * deltaTime;

	if (velocity.x == 0.0f)
	{
		row = 0;
	}
	else {
		row = 0;
		if (velocity.x > 0.0f)
		{
			faceRight = true;
		}		
		else
		{
			faceRight = false;
		}

	}
	if (crawl == 1)
	{
		row = 2;
	}

	animation.Update(row, deltaTime,faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Player::OnCollision(sf::Vector2f direction)
{
	if (direction.x< 0.0f)
	{
		//Collision on the left.
		velocity.x = 0.0f;
	}
	else if(direction.x >0.0f)
	{
		//Collision on the right.
		velocity.x = 0.0f;
	}
	if (direction.y < 0.0f)
	{
		//Collision on the bottom.
		velocity.y = 0.0f;
		canJump = true;
	}
	else if (direction.y > 0.0f)
	{
		//Collision on the top.
		velocity.y = 0.0f;
	}
}
