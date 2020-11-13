#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Player.h"
#include "Platform.h"
#include "Enemy.h"
#include "Time.h"

static const float View_HEIGHT = 720.0f;
static const float View_WIDTH = 1080.0f;


void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize((View_HEIGHT)* aspectRatio, View_HEIGHT );
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1080, 720), "Fila Kung");// , sf::Style::Fullscreen
	sf::RectangleShape frame(sf::Vector2f(1080.0f, 720.0f));
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(View_WIDTH, View_HEIGHT));

	window.setFramerateLimit(120);

	sf::Texture mon_texture;
	mon_texture.loadFromFile("img/cat2_3.png");
	Player player(&mon_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, 150.0f);

	sf::RectangleShape bg_1(sf::Vector2f(0.0f, 0.0f));
	sf::Texture bg1;
	bg1.loadFromFile("img/bg1.png");
	bg_1.setTexture(&bg1);
	bg_1.setSize(sf::Vector2f(1280.0f, 720.0f));
	bg_1.setOrigin(sf::Vector2f(0.0f, 0.0f));
	bg_1.setPosition(sf::Vector2f(-540.0f, -360.0f));

	//sf::RectangleShape bg_1_1(sf::Vector2f(0.0f, 0.0f));
	//sf::Texture bg1_1;
	//bg2.loadFromFile("img/bg1.png");
	//bg_1.setTexture(&bg1_1);
	//bg_1.setSize(sf::Vector2f(1280.0f, 720.0f));
	//bg_1.setOrigin(sf::Vector2f(0.0f, 0.0f));
	//bg_1.setPosition(sf::Vector2f(540.0f, -360.0f));

	//if (player.GetPosition().x <= 0)
	//{
	//	if (player.GetPosition().x >= x)
	//	{
	//		view.setCenter(sf::Vector2f(player.GetPosition().x, 0));
	//		x++;
	//	}
	//}

	

	sf::Texture enemy_texture;
	enemy_texture.loadFromFile("img/enemy.png");
	Enemy enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, 300 ,275);

	std::vector <Enemy> enemyVector;
	enemyVector.push_back(Enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 100 + 200, 275));

	enemyVector.push_back(Enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 100 + 300, 275));
	enemyVector.push_back(Enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 100 + 400, 275));
	enemyVector.push_back(Enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 100 + 500, 275));
	enemyVector.push_back(Enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 100 + 600, 275));


	// get check-point
	sf::Vector2f sprawn;
	sprawn.x = 0.0f;
	sprawn.y = 0.0f;

	// score
	int score = 0;


	// HP player
	float myHP = 78000;
	sf::RectangleShape HP(sf::Vector2f(myHP / 150.0f, 50));
	HP.setPosition(sf::Vector2f(-170, -350));
	HP.setFillColor(sf::Color::Magenta);
	HP.setSize(sf::Vector2f(myHP / 320.f, 25));

	sf::RectangleShape bg_yard1(sf::Vector2f(0, 0));
	sf::Texture bg_yard;
	bg_yard.loadFromFile("img/bg_yard.jpg");
	bg_yard1.setTexture(&bg_yard);

	sf::RectangleShape b0(sf::Vector2f(0,0));
	sf::Texture floor;
	floor.loadFromFile("img/floor.png");
	b0.setTexture(&floor);

	// ITEM 
	sf::RectangleShape item01(sf::Vector2f(300, 300));
	

	
	std::vector<Platform> platforms;
	//texture size position

//	platforms.push_back(Platform(&floor, sf::Vector2f(100.0f, 50.0f), sf::Vector2f(600.0f, 250.0f)));
//	platforms.push_back(Platform(&floor, sf::Vector2f(100.0f, 50.0f), sf::Vector2f(200.0f, 10.0f)));
	platforms.push_back(Platform(&floor, sf::Vector2f(100.0f, 50.0f), sf::Vector2f(300.0f, 50.0f)));
	//platforms.push_back(Platform(&floor, sf::Vector2f(100.0f, 50.0f), sf::Vector2f(700.0f, 300.0f)));
	platforms.push_back(Platform(&floor, sf::Vector2f(100.0f, 50.0f), sf::Vector2f(400.0f, 150.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 150.0f), sf::Vector2f(100.0f, 250.0f)));	
	//platforms.push_back(Platform(nullptr, sf::Vector2f(900.0f, 100.0f), sf::Vector2f(300.0f, 470.0f)));
	//platforms.push_back(Platform(nullptr, sf::Vector2f(900.0f, 50.0f), sf::Vector2f(1080.0f, 150.0f)));
	//platforms.push_back(Platform(nullptr, sf::Vector2f(900.0f, 100.0f), sf::Vector2f(2300.0f, 500.0f)));

	platforms.push_back(Platform(nullptr, sf::Vector2f(3000.0f, 100.0f), sf::Vector2f(-100.0f, 350.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(500.0f, 100.0f), sf::Vector2f(200.0f, 350.0f)));

	



	float deltaTime = 0.0f;
	sf::Clock clock;
	sf::Time time;
	while (window.isOpen())
	{
		sf::Vector2f mousePosition = sf::Vector2f(0.0f, 0.0f);
		mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
//		printf("%f \t%f\n", mousePosition.x, mousePosition.y);

		//time = clock.restart();
		//float fps = time.asSeconds();
		//printf("%f\n", 1.0f / fps);
		
//		window.draw(b0);
		deltaTime = clock.restart().asSeconds();
		if (deltaTime > 1.0f / 20.0f)
			deltaTime = 1.0f / 20.0f;
	
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				ResizeView(window, view);
				break;
			}
		}

		HP.setPosition(sf::Vector2f(view.getCenter().x - 520 , -340));
		
		player.Update(deltaTime);
		view.setCenter(sf::Vector2f(player.GetPosition().x, 0));

		Collider playerCollision = player.GetCollider();
		sf::Vector2f direction;

		for (Platform& platform : platforms)
			if (platform.GetCollider().CheckCollision(playerCollision, direction, 1.0f))
				player.OnCollision(direction);
		if (player.GetPosition().y > 1000)
		{
			player.SetPosition(sf::Vector2f(sprawn));
		}
		if (player.GetPosition().x > 350)
		{
			sprawn.x = 350;
			sprawn.y = 0;
		}
	
		//Player player = player;
		for (int i = 0; i < enemyVector.size(); i++)
			enemyVector[i].Update2(deltaTime, player);
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window.close();
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::RShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			//freeze hp
		
//		bg.Draw(window);
		window.clear();
//		window.clear(sf::Color(170, 237, 202));
//		for (int i = 0; i > 2; i++)
//		{
			//sf::Vector2f postion = bg_1[i].getPosition();
			window.draw(bg_1);
			//window.draw(bg_1_1);
//		}
		window.setView(view);
		window.draw(HP);
		player.Draw(window);

//		enemy.Draw(window);

		for (Platform& platform : platforms)
			platform.Draw(window);

		for (int i = 0; i < enemyVector.size(); i++)
		{
			enemyVector[i].GetCollider().CheckCollisions(playerCollision, 1.0f);
			enemyVector[i].Draw(window);
		}
		
		
		window.display();
	}
	return 0;
}
