#pragma once
#include<SFML/Graphics.hpp>
#include "Animation.h"
#include "Collider.h"

class Player
{
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed,float jumpHeight);
	~Player();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void OnCollision(sf::Vector2f direction);
	void SetPosition(sf::Vector2f position) { body.setPosition(position); }
	sf::Vector2f GetPosition() {return	body.getPosition();}
	Collider GetCollider() { return Collider(body); }

	bool crawlRe() 
	{
		if (this->crawl == 1) { return 1; }
		else { return 0; }
	}
	float delayCrawlRe()
	{
		if (this->delayCrawl > 0.f) { return delayCrawl; }
		else { return 0.f; }
	}	

private:
	sf::RectangleShape body;
	Animation animation;
	unsigned int row;
	float speed;
	bool faceRight;
	bool crawl = 0;
	
	sf::Vector2f velocity;
	bool canJump;
	float jumpHeight;
	float delayCrawl = 0.0f;

};
