
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1080, 720), "FILA-KUNG");

	//const float gravity = 1;
	//int groundHeight = 440;
	//sf::Vector2f velocity(sf::Vector2f(0, 0));
	//float jumpspeed = 10.0f;

	////// Circle
	sf::CircleShape collision(100.f);
	collision.setPosition({ 400.f, 400.f });
	collision.setFillColor(sf::Color::Blue);

	////// Texture
	sf::Texture playerTexture;
	if (!playerTexture.loadFromFile("img/cat2_3.PNG"))
	{
		std::cout << "Load failed" << std::endl;
	}

	////// Sprite
	sf::Sprite shapeSprite;
	shapeSprite.setTexture(playerTexture);

	int spriteSizeX = playerTexture.getSize().x / 3;
	int spriteSizeY = playerTexture.getSize().y / 2;

	shapeSprite.setTextureRect(sf::IntRect(0, 0, spriteSizeX, spriteSizeY));

	sf::Vector2f spawnPoint = { 0.f, 0.f };
	shapeSprite.setPosition(spawnPoint);

	int animationFrame = 0;

	while (window.isOpen())
	{
		window.draw(shapeSprite);
		window.draw(collision);
		window.display();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			shapeSprite.move(.1f, 0.f);
			shapeSprite.setTextureRect(sf::IntRect(spriteSizeX * animationFrame, spriteSizeY * 1, spriteSizeX, spriteSizeY));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			shapeSprite.move(-.1f, 0.f);
			shapeSprite.setTextureRect(sf::IntRect(spriteSizeX * animationFrame, spriteSizeY * 0, spriteSizeX, spriteSizeY));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			shapeSprite.move(0.f, -.1f);
//			velocity.y = -jumpspeed;
			shapeSprite.setTextureRect(sf::IntRect(spriteSizeX * animationFrame, 0, spriteSizeX, spriteSizeY));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			shapeSprite.move(0.f, .1f);
			shapeSprite.setTextureRect(sf::IntRect(spriteSizeX * animationFrame, spriteSizeY * 1, spriteSizeX, 32));
		}
		//if (shapeSprite.getPosition().y + spriteSizeY < groundHeight || velocity.y < 0)
		//{
		//	velocity.y += gravity;
		//}
		//else
		//{
		//	shapeSprite.setPosition(shapeSprite.getPosition().x, groundHeight - spriteSizeY);
		//}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}
		animationFrame++;

		if (animationFrame >= 2) {
			animationFrame = 0;
		}

		if (collision.getGlobalBounds().intersects(shapeSprite.getGlobalBounds())) {
			shapeSprite.setPosition(spawnPoint);
		}
		window.clear(sf::Color(0, 255, 127));
	}
	return 0;
}
