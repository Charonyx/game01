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
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(1080, 720), "Fila Kung", sf::Style::Fullscreen);// , sf::Style::Fullscreen
	sf::RectangleShape frame(sf::Vector2f(1080.0f, 720.0f));
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(View_WIDTH, View_HEIGHT));

	window.setFramerateLimit(120);

	// BG01
	sf::RectangleShape bg01(sf::Vector2f(0.0f, 0.0f));
	sf::Texture bg1;
	bg1.loadFromFile("img/BG01.png");
	bg01.setTexture(&bg1);
	bg01.setSize(sf::Vector2f(12800.0f, 720.0f));	
	bg01.setOrigin(sf::Vector2f(0.0f, 0.0f));
	bg01.setPosition(sf::Vector2f(-540.0f, -360.0f));

	// BG02
	//sf::RectangleShape bg02(sf::Vector2f(0.0f, 0.0f));
	//sf::Texture bg2;
	//bg2.loadFromFile("img/BG02.png");
	//bg02.setTexture(&bg2);
	//bg02.setSize(sf::Vector2f(12800.0f, 720.0f));
	//bg02.setOrigin(sf::Vector2f(0.0f, 0.0f));
	//bg02.setPosition(sf::Vector2f(540.0f, -360.0f));

	// BG03
	//sf::RectangleShape bg03(sf::Vector2f(0.0f, 0.0f));
	//sf::Texture bg3;
	//bg2.loadFromFile("img/BG02.png");
	//bg03.setTexture(&bg3);
	//bg03.setSize(sf::Vector2f(12800.0f, 720.0f));
	//bg03.setOrigin(sf::Vector2f(0.0f, 0.0f));
	//bg03.setPosition(sf::Vector2f(540.0f, -360.0f));

	// floor
	sf::RectangleShape plat(sf::Vector2f(0, 0));
	sf::Texture floor;
	floor.loadFromFile("img/floor.png");
	plat.setTexture(&floor);

	//if (player.GetPosition().x <= 0)
	//{
	//	if (player.GetPosition().x >= x)
	//	{
	//		view.setCenter(sf::Vector2f(player.GetPosition().x, 0));
	//		x++;
	//	}
	//}

	sf::Texture player_texture;
	player_texture.loadFromFile("img/cat2_3.png");
	Player player(&player_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, 150.0f);

	sf::Texture enemy_texture;
	enemy_texture.loadFromFile("img/enemy.png");
	Enemy enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, 300 ,275);

	std::vector <Enemy> enemyVector;
	enemyVector.push_back(Enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 500 + 2400, 275));
	enemyVector.push_back(Enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 500 + 2800, 275));
	enemyVector.push_back(Enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 500 + 1200, 275));
	enemyVector.push_back(Enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 500 + 1600, 275));
	enemyVector.push_back(Enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 500 + 2000, 275));


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

	// ITEM 
	sf::RectangleShape item01(sf::Vector2f(300, 300));
	
	// Platform floor == texture size position
	std::vector<Platform> platforms;
	platforms.push_back(Platform(nullptr, sf::Vector2f(12800.0f, 100.0f), sf::Vector2f(-100.0f, 350.0f)));	//main
	platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 100.0f), sf::Vector2f(400.0f, 255.0f)));		//tutorial

	platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 40.0f), sf::Vector2f(1400.0f, 175.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 40.0f), sf::Vector2f(1500.0f, 135.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 40.0f), sf::Vector2f(1600.0f, 95.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(700.0f, 40.0f), sf::Vector2f(2000.0f, 55.0f)));		// item under	
	platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 40.0f), sf::Vector2f(2600.0f, 175.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 40.0f), sf::Vector2f(2500.0f, 135.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 40.0f), sf::Vector2f(2400.0f, 95.0f)));

	platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 40.0f), sf::Vector2f(3600.0f, 175.0f)));
	platforms.push_back(Platform(&floor, sf::Vector2f(200.0f, 40.0f), sf::Vector2f(3800.0f, 55.0f)));

	platforms.push_back(Platform(&floor, sf::Vector2f(300.0f, 40.0f), sf::Vector2f(4300.0f, 55.0f)));

	platforms.push_back(Platform(&floor, sf::Vector2f(200.0f, 40.0f), sf::Vector2f(4800.0f, 55.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 40.0f), sf::Vector2f(5000.0f, 175.0f)));



	float deltaTime = 0.0f;
	sf::Clock clock;
	sf::Time time;
	while (window.isOpen())
	{
		sf::Vector2f mousePosition = sf::Vector2f(0.0f, 0.0f);
		mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		printf("%f \t%f\n", mousePosition.x, mousePosition.y);

		//time = clock.restart();
		//float fps = time.asSeconds();
		//printf("%f\n", 1.0f / fps);
		
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

		HP.setPosition(sf::Vector2f(view.getCenter().x - 520 , -350));
		
		player.Update(deltaTime);
		view.setCenter(sf::Vector2f(player.GetPosition().x, 0));

		// check collider
		Collider enemyCollision = enemy.GetCollider();

		Collider playerCollision = player.GetCollider();
		sf::Vector2f direction;

		for (Platform& platform : platforms)
			if (platform.GetCollider().CheckCollision(playerCollision, direction, 1.0f))
				player.OnCollision(direction);

		// check point
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
			myHP = 78000;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			//enemy hit 0 hp
		

		window.clear();
//		window.clear(sf::Color(170, 237, 202));
//		for (int i = 0; i > 2; i++)
//		{
			//sf::Vector2f postion = bg01[i].getPosition();
			window.draw(bg01);
			//window.draw(bg_1_1);
//		}
		window.setView(view);
		window.draw(HP);
		player.Draw(window);

		enemy.GetCollider().CheckCollisionM(enemyCollision, 1.0f);

		for (Platform& platform : platforms)
		{
			platform.GetCollider().CheckCollisionM(enemyCollision, 1.0f);
			platform.Draw(window);
		}
			
		for (int i = 0; i < enemyVector.size(); i++)
		{
			enemyVector[i].GetCollider().CheckCollisionM(playerCollision, 1.0f);
			enemyVector[i].Draw(window);
		}
		
		//for (int i = 0; i < enemy2Vector.size(); i++)
		//{
		//	enemy2Vector[i].GetCollider().CheckCollisionM(playerCollision, 1.0f);
		//	enemy2Vector[i].Draw(window);
		//}
		
		window.display();
	}
	return 0;
}
