#include <SFML/Graphics.hpp>
#include<iostream>
#include<vector>
#include"Player.h"
#include"Platform.h"

static const float View_HEIGHT = 720.0f;

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize((View_HEIGHT)* aspectRatio, View_HEIGHT );
}

int main()
{
	sf::RectangleShape bg_1(sf::Vector2f(0.0f, 0.0f));
	sf::Texture bg1;
	bg1.loadFromFile("img/bg1.png");
	bg_1.setTexture(&bg1);
	bg_1.setSize(sf::Vector2f(1280.0f, 720.0f));
	bg_1.setOrigin(sf::Vector2f(0.0f, 0.0f));
	bg_1.setPosition(sf::Vector2f(-540.0f, -360.0f));

	

	sf::Vector2f sprawn;
	sprawn.x = 0.0f;
	sprawn.y = 0.0f;



	sf::RenderWindow window(sf::VideoMode(1280, 720), "Fila Kung" , sf::Style::Fullscreen);
	sf::RectangleShape frame(sf::Vector2f(1280.0f, 720.0f));
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(View_HEIGHT, View_HEIGHT));


	////// Circle
	sf::CircleShape collision(50.f);
	collision.setPosition({ 200.f, 200.f });
	collision.setFillColor(sf::Color::Black);

	sf::RectangleShape bg_yard1(sf::Vector2f(0, 0));
	sf::Texture bg_yard;
	bg_yard.loadFromFile("img/bg_yard.jpg");
	bg_yard1.setTexture(&bg_yard);

	sf::RectangleShape b0(sf::Vector2f(0,0));
	sf::Texture floor;
	floor.loadFromFile("img/floor.png");
	b0.setTexture(&floor);
	
	sf::RectangleShape enemy(sf::Vector2f(0, 0));
	enemy.setPosition({ 200.f, 200.f});
	enemy.setFillColor(sf::Color::Blue);


	sf::Texture mon_texture;
	mon_texture.loadFromFile("img/cat2_3.png"); 
	Player monster(&mon_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, 300.0f);

	
	std::vector<Platform> platforms;

//	platforms.push_back(Platform(&floor, sf::Vector2f(100.0f, 50.0f), sf::Vector2f(600.0f, 250.0f)));
	platforms.push_back(Platform(&floor, sf::Vector2f(100.0f, 50.0f), sf::Vector2f(200.0f, 10.0f)));
	platforms.push_back(Platform(&floor, sf::Vector2f(100.0f, 50.0f), sf::Vector2f(300.0f, 50.0f)));
	//platforms.push_back(Platform(&floor, sf::Vector2f(100.0f, 50.0f), sf::Vector2f(700.0f, 300.0f)));
	platforms.push_back(Platform(&floor, sf::Vector2f(100.0f, 50.0f), sf::Vector2f(500.0f, 100.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 150.0f), sf::Vector2f(100.0f, 250.0f)));	
	//platforms.push_back(Platform(nullptr, sf::Vector2f(900.0f, 100.0f), sf::Vector2f(300.0f, 470.0f)));
	//platforms.push_back(Platform(nullptr, sf::Vector2f(900.0f, 50.0f), sf::Vector2f(1080.0f, 150.0f)));
	//platforms.push_back(Platform(nullptr, sf::Vector2f(900.0f, 100.0f), sf::Vector2f(2300.0f, 500.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(9000.0f, 100.0f), sf::Vector2f(-100.0f, 350.0f)));

	float deltaTime = 0.0f;
	sf::Clock clock;
	while (window.isOpen())
	{
//		printf("%d \t%d\n", view.getPosition().x, view.getPosition().y);
		
		window.draw(b0);
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
		
		monster.Update(deltaTime);
		view.setCenter(sf::Vector2f(monster.GetPosition().x, 0));

		Collider monsterCollision = monster.GetCollider(); // Dammit!!!!
		sf::Vector2f direction;


		for (Platform& platform : platforms)
			if (platform.GetCollider().CheckCollision(monsterCollision, direction, 1.0f))
				monster.OnCollision(direction);
		if (monster.GetPosition().y > 1000)
		{
			monster.SetPosition(sf::Vector2f(sprawn));
		}
		if (monster.GetPosition().x > 350)
		{
			sprawn.x = 350;
			sprawn.y = 0;
		}
	
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{	
			window.close();
		}
//		bg.Draw(window);
		window.clear();
//		window.clear(sf::Color(170, 237, 202));
		window.draw(bg_1);
		window.setView(view);
//		window.draw(collision);
//		window.draw(enemy);
		monster.Draw(window);
		for (Platform& platform : platforms)
		platform.Draw(window);
		window.display();
	}
	return 0;
}
