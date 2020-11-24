#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Player.h"
#include "Platform.h"
#include "Enemy.h"
#include "Item.h"
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


	// TEXT //////////////////////////   WARNING edit font color
	sf::Font MainFont;
	MainFont.loadFromFile("font/SHOWG.ttf");
	sf::Text talk01_1("Ah! onii-chan!? ", MainFont, 25);
	sf::Text talk01_2("Hi, fila-kung. \nI haven't seen you for ages. ", MainFont, 25);
	sf::Text talk01_3("Ha ha ha! \nAre you kidding me? \nWe just met each other yesterday.", MainFont, 23);
	sf::Text talk01_4("Opps! Really? \nI think yesterday is very \nlong times for me. ", MainFont, 25);
	sf::Text talk01_5("Sorry to interrupt you, \nbut I've lost my bell collar. \nHave you seen something \nlike my collar ? ", MainFont, 25);
	sf::Text talk01_6("Hmm.......... \nI'm not sure, but I have found \npieces of something. Let me \ngive it to you.", MainFont, 25);
	sf::Text talk01_7("Oh! This is pieces of my collar. \nThanx, onii-chan!", MainFont, 25);
	sf::Text talk01_8("You got it. \nfinger crossed! ", MainFont, 25);

	sf::Text talk02_1("Bonjour, Mr. Meow! ", MainFont, 25);
	sf::Text talk02_2("Bonjour, Fila-kung! \nWhy are you in a rush? ", MainFont, 25);
	sf::Text talk02_3("I lost my bell collar and \nI want to found it ASAP.", MainFont, 25);
	sf::Text talk02_4("What a coincidence! \nI just found something like that. \nLet me give it to you. ", MainFont, 25);
	sf::Text talk02_5("Thank you, Mr. Meow. ", MainFont, 25);
	sf::Text talk02_6("No worries. ", MainFont, 25);

	sf::Text talk03_1("Bonjour, Mr. Magic!", MainFont, 25);
	sf::Text talk03_2("Bonjour, Fila-kung! \nCan I help you?", MainFont, 25);
	sf::Text talk03_3("Surely, Can you fix my bell collar? ", MainFont, 25);
	sf::Text talk03_4("Certainly, let you give \npieces of your collar to me! ", MainFont, 25);
	sf::Text talk03_5("Here you are.", MainFont, 25);
	sf::Text talk03_6("Great! Wait for a minute....\nFinished! ", MainFont, 25);
	sf::Text talk03_7("Wowwww! What would I do without you? ", MainFont, 25);
	sf::Text talk03_8("Ha ha ha! \nI'm happy to help. ", MainFont, 25);
	
	// MENU //////////////////////////
	// MENU unpressed
	sf::RectangleShape menu01(sf::Vector2f(0, 0));
	sf::Texture menu;
	menu.loadFromFile("img/menu01.png");
	menu01.setTexture(&menu);
	menu01.setSize(sf::Vector2f(1080.0f, 720.0f));
	menu01.setOrigin(sf::Vector2f(0.0f, 0.0f));
	menu01.setPosition(sf::Vector2f(540.0f, -360.0f));
	
	// MENU pressed play
	sf::RectangleShape menu01_1(sf::Vector2f(0, 0));
	sf::Texture menu1_1;
	menu1_1.loadFromFile("img/menu01-1.png");
	menu01_1.setTexture(&menu1_1);
	menu01_1.setSize(sf::Vector2f(1080.0f, 720.0f));
	menu01_1.setOrigin(sf::Vector2f(0.0f, 0.0f));
	menu01_1.setPosition(sf::Vector2f(540.0f, -360.0f));	

	// MENU pressed score
	sf::RectangleShape menu01_2(sf::Vector2f(0, 0));
	sf::Texture menu1_2;
	menu1_2.loadFromFile("img/menu01-2.png");
	menu01_2.setTexture(&menu1_2);
	menu01_2.setSize(sf::Vector2f(1080.0f, 720.0f));
	menu01_2.setOrigin(sf::Vector2f(0.0f, 0.0f));
	menu01_2.setPosition(sf::Vector2f(540.0f, -360.0f));

	// MENU pressed how to play
	sf::RectangleShape menu01_3(sf::Vector2f(0, 0));
	sf::Texture menu1_3;
	menu1_3.loadFromFile("img/menu01-3.png");
	menu01_3.setTexture(&menu1_3);
	menu01_3.setSize(sf::Vector2f(1080.0f, 720.0f));
	menu01_3.setOrigin(sf::Vector2f(0.0f, 0.0f));
	menu01_3.setPosition(sf::Vector2f(540.0f, -360.0f));	

	// MENU pressed setting
	sf::RectangleShape menu01_4(sf::Vector2f(0, 0));
	sf::Texture menu1_4;
	menu1_4.loadFromFile("img/menu01-3.png");
	menu01_4.setTexture(&menu1_4);
	menu01_4.setSize(sf::Vector2f(1080.0f, 720.0f));
	menu01_4.setOrigin(sf::Vector2f(0.0f, 0.0f));
	menu01_4.setPosition(sf::Vector2f(540.0f, -360.0f));

	// MENU pressed exit
	sf::RectangleShape menu01_5(sf::Vector2f(0, 0));
	sf::Texture menu1_5;
	menu1_5.loadFromFile("img/menu01-3.png");
	menu01_5.setTexture(&menu1_4);
	menu01_5.setSize(sf::Vector2f(1080.0f, 720.0f));
	menu01_5.setOrigin(sf::Vector2f(0.0f, 0.0f));
	menu01_5.setPosition(sf::Vector2f(540.0f, -360.0f));
	
	// Background //////////////////////////////////
	// BG01
	sf::RectangleShape bg01(sf::Vector2f(0.0f, 0.0f));
	sf::Texture bg1;
	bg1.loadFromFile("img/BG01.png");
	bg01.setTexture(&bg1);
	bg01.setSize(sf::Vector2f(12800.0f, 720.0f));	
	bg01.setOrigin(sf::Vector2f(0.0f, 0.0f));
	bg01.setPosition(sf::Vector2f(-540.0f, -360.0f));

	// BG02
	sf::RectangleShape bg02(sf::Vector2f(0.0f, 0.0f));
	sf::Texture bg2;
	bg2.loadFromFile("img/BG02.png");
	bg02.setTexture(&bg2);
	bg02.setSize(sf::Vector2f(12800.0f, 720.0f));
	bg02.setOrigin(sf::Vector2f(0.0f, 0.0f));
	bg02.setPosition(sf::Vector2f(12260.0f, -360.0f));

	// BG03
	sf::RectangleShape bg03(sf::Vector2f(0.0f, 0.0f));
	sf::Texture bg3;
	bg3.loadFromFile("img/BG03.png");
	bg03.setTexture(&bg3);
	bg03.setSize(sf::Vector2f(12800.0f, 720.0f));
	bg03.setOrigin(sf::Vector2f(0.0f, 0.0f));
	bg03.setPosition(sf::Vector2f(25060.0f, -360.0f));


	// floor
	sf::RectangleShape plat(sf::Vector2f(0, 0));
	sf::Texture floor;
	floor.loadFromFile("img/floor.png");
	plat.setTexture(&floor);

	// door wrap
	sf::RectangleShape warpPoint(sf::Vector2f(0.0f, 0.0f));
	sf::Texture doorwarp;
	doorwarp.loadFromFile("img/warp.png");
	warpPoint.setTexture(&doorwarp);
	warpPoint.setSize(sf::Vector2f(200.0f, 300.0f));
	warpPoint.setPosition(sf::Vector2f(10125.0f, 25.0f));

	// door wrap 1
	sf::RectangleShape warpPoint1(sf::Vector2f(0.0f, 0.0f));
	sf::Texture doorwarp1;
	doorwarp1.loadFromFile("img/warp.png");
	warpPoint1.setTexture(&doorwarp1);
	warpPoint1.setSize(sf::Vector2f(200.0f, 300.0f));
	warpPoint1.setPosition(sf::Vector2f(22385.0f, 25.0f));

	// to talk
	sf::Texture msgTalk;
	msgTalk.loadFromFile("img/messageTalk.png");
	sf::RectangleShape msgToTalk(sf::Vector2f(0.0f, 0.0f));
	msgToTalk.setTexture(&msgTalk);
	msgToTalk.setSize(sf::Vector2f(250.0f, 60.0f));

	// to warp
	sf::Texture msgWarp;
	msgWarp.loadFromFile("img/messageWarp.png");
	sf::RectangleShape msgToWarp(sf::Vector2f(0.0f, 0.0f));
	msgToWarp.setTexture(&msgWarp);
	msgToWarp.setSize(sf::Vector2f(250.0f, 60.0f));

	// ZONE : Story /////////////////////////////////////////////
	// story01 : NPC state1 onii-chan
	sf::RectangleShape story01(sf::Vector2f(0.0f, 0.0f));
	sf::Texture storyState01;
	storyState01.loadFromFile("img/story01.png");
	story01.setTexture(&storyState01);
	story01.setSize(sf::Vector2f(60.0f, 60.0f));
	story01.setPosition(sf::Vector2f(9800.f, 243.0f));	
	
	// story02 : NPC state2 MR. Meow
	sf::RectangleShape story02(sf::Vector2f(0.0f, 0.0f));
	sf::Texture storyState02;
	storyState02.loadFromFile("img/story02.png");
	story02.setTexture(&storyState02);
	story02.setSize(sf::Vector2f(60.0f, 60.0f));
	story02.setPosition(sf::Vector2f(800.f, 243.0f));	
	
	// story03 : NPC state3 MR. Magic
	sf::RectangleShape story03(sf::Vector2f(0.0f, 0.0f));
	sf::Texture storyState03;
	storyState03.loadFromFile("img/story03.png");
	story03.setTexture(&storyState03);
	story03.setSize(sf::Vector2f(60.0f, 60.0f));
	story03.setPosition(sf::Vector2f(900.f, 243.0f));

	// messengeBox player
	sf::RectangleShape msgBoxPlayer(sf::Vector2f(0.0f, 0.0f));
	sf::Texture msgBoxP;
	msgBoxP.loadFromFile("img/messageTalkPlayer.png");
	msgBoxPlayer.setTexture(&msgBoxP);
	msgBoxPlayer.setSize(sf::Vector2f(600.0f, 230.0f));

	// messengeBox NPC1
	sf::RectangleShape msgBoxNPC1(sf::Vector2f(0.0f, 0.0f));
	sf::Texture msgBoxN1;
	msgBoxN1.loadFromFile("img/messageTalkNPC1.png");
	msgBoxNPC1.setTexture(&msgBoxN1);
	msgBoxNPC1.setSize(sf::Vector2f(600.0f, 230.0f));

	// messengeBox NPC2
	sf::RectangleShape msgBoxNPC2(sf::Vector2f(0.0f, 0.0f));
	sf::Texture msgBoxN2;
	msgBoxN2.loadFromFile("img/messageTalkNPC2.png");
	msgBoxNPC2.setTexture(&msgBoxN2);
	msgBoxNPC2.setSize(sf::Vector2f(600.0f, 230.0f));

	// messengeBox NPC3
	sf::RectangleShape msgBoxNPC3(sf::Vector2f(0.0f, 0.0f));
	sf::Texture msgBoxN3;
	msgBoxN3.loadFromFile("img/messageTalkNPC3.png");
	msgBoxNPC3.setTexture(&msgBoxN3);
	msgBoxNPC3.setSize(sf::Vector2f(600.0f, 230.0f));

	// rare  item1
	sf::RectangleShape rareItem1(sf::Vector2f(0.0f, 0.0f));
	sf::Texture rare1;
	rare1.loadFromFile("img/rareItem1.png");
	rareItem1.setTexture(&rare1);
	rareItem1.setSize(sf::Vector2f(600.0f, 230.0f));
	
	// rare  item2
	sf::RectangleShape rareItem2(sf::Vector2f(0.0f, 0.0f));
	sf::Texture rare2;
	rare2.loadFromFile("img/rareItem2.png");
	rareItem2.setTexture(&rare2);
	rareItem2.setSize(sf::Vector2f(600.0f, 230.0f));

	// rare  item3
	sf::RectangleShape rareItem3(sf::Vector2f(0.0f, 0.0f));
	sf::Texture rare3;
	rare3.loadFromFile("img/rareItem3.png");
	rareItem3.setTexture(&rare3);
	rareItem3.setSize(sf::Vector2f(600.0f, 230.0f));
	



	//if (player.GetPosition().x <= 0)
	//{
	//	if (player.GetPosition().x >= x)
	//	{
	//		view.setCenter(sf::Vector2f(player.GetPosition().x, 0));
	//		x++;
	//	}
	//}


	// varible /////////////////////////////
	int npc1 = 0, npc2 = 0, npc3 = 0;
	int talk1 = 0, talk2 = 0, talk3 = 0; //0-strt 1-talkin' 2-already-NPC-disappeared
	bool warp1 = 0, warp2 = 0;

	bool START = false;
	bool MENU = true;
	bool Rank = false;
	bool SCORE = true;
	bool endGame = false;
	bool MemScore = false;
	bool sound_over = false;
	bool checkpause = false;
	bool cheakhighscore = false;

	// PLAYER
	sf::Texture player_texture;
	player_texture.loadFromFile("img/cat2_5.png");
	Player player(&player_texture, sf::Vector2u(3, 3), 0.2f, 300.0f, 150.0f);

	// ENEMY01
	sf::Texture enemy_texture;
	enemy_texture.loadFromFile("img/enemy.png");
	Enemy enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, 300.0f ,275.0f);

	std::vector <Enemy> enemyVector;
	enemyVector.push_back(Enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 500 + 2400, 275));
	enemyVector.push_back(Enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 500 + 2800, 275));
	enemyVector.push_back(Enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 500 + 1200, 275));
	enemyVector.push_back(Enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 500 + 1600, 275));
	enemyVector.push_back(Enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 500 + 2000, 275));

	// ITEM HP++
	sf::Texture item01;
	item01.loadFromFile("img/item4.png");
	Item item(&item01, sf::Vector2u(1, 1), 0.2f, 300.0f, 150.0f);

	std::vector <Item> itemVector;
	itemVector.push_back(Item(&item01, sf::Vector2u(1, 1), 0.2f, rand() % 500 + 2400, 275));
	itemVector.push_back(Item(&item01, sf::Vector2u(1, 1), 0.2f, rand() % 500 + 2800, 275));

	// ITEM HP--
	sf::Texture item02;
	item02.loadFromFile("img/item2.png");
	Item itemDown(&item02, sf::Vector2u(1, 1), 0.2f, 600.0f, 150.0f);


	// get check-point
	sf::Vector2f sprawn;
	sprawn.x = 0.0f;
	sprawn.y = 0.0f;

	// score
	int score = 0;

	// HP player
	float myHP = 78000;
	sf::RectangleShape HP(sf::Vector2f(myHP / 150.0f, 50.0f));
	HP.setPosition(sf::Vector2f(-170.0f, -350.0f));
	HP.setFillColor(sf::Color::Magenta);
	HP.setSize(sf::Vector2f(myHP / 320.f, 25.0f));

	
	// Platform floor == texture size position
	std::vector<Platform> platforms;

	// state 1
	platforms.push_back(Platform(nullptr, sf::Vector2f(22900.0f, 100.0f), sf::Vector2f(-100.0f, 350.0f)));	//main
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
	
	platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 40.0f), sf::Vector2f(6400.0f, 175.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 40.0f), sf::Vector2f(6500.0f, 135.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 40.0f), sf::Vector2f(6600.0f, 95.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(700.0f, 40.0f), sf::Vector2f(7000.0f, 55.0f)));		// item under	
	platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 40.0f), sf::Vector2f(7600.0f, 175.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 40.0f), sf::Vector2f(7500.0f, 135.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 40.0f), sf::Vector2f(7400.0f, 95.0f)));
	

	
	// state 2
	platforms.push_back(Platform(nullptr, sf::Vector2f(22800.0f, 100.0f), sf::Vector2f(12800.0f, 350.0f)));	//main
	platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 100.0f), sf::Vector2f(13400.0f, 255.0f)));		//tutorial

	platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 40.0f), sf::Vector2f(14400.0f, 175.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 40.0f), sf::Vector2f(14500.0f, 135.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 40.0f), sf::Vector2f(14600.0f, 95.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(700.0f, 40.0f), sf::Vector2f(15000.0f, 55.0f)));		// item under	
	platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 40.0f), sf::Vector2f(15600.0f, 175.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 40.0f), sf::Vector2f(15500.0f, 135.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 40.0f), sf::Vector2f(15400.0f, 95.0f)));

	platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 40.0f), sf::Vector2f(16600.0f, 175.0f)));
	platforms.push_back(Platform(&floor, sf::Vector2f(200.0f, 40.0f), sf::Vector2f(16800.0f, 55.0f)));

	platforms.push_back(Platform(&floor, sf::Vector2f(300.0f, 40.0f), sf::Vector2f(17300.0f, 55.0f)));

	platforms.push_back(Platform(&floor, sf::Vector2f(200.0f, 40.0f), sf::Vector2f(17800.0f, 55.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 40.0f), sf::Vector2f(18000.0f, 175.0f)));
		
	// state 3
/*	platforms.push_back(Platform(nullptr, sf::Vector2f(12800.0f, 100.0f), sf::Vector2f(-100.0f, 350.0f)));	//main
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

	*/

	float deltaTime = 0.0f;
	int k = 0;
	sf::Clock clock;
	sf::Time time; //frame rate
	sf::Clock cl; // hit enemy
	sf::Clock clTalk;
	float timeTalk = 0;

	float delayTime = 0.f;
	float dTime = 0.4;
	//delayTime += deltaTime;

	while (window.isOpen())
	{
		float PositionPlayerX = float((player.GetCollider().GetPosition().x));
		float PositionPlayerY = float((player.GetCollider().GetPosition().y));

		float msgPX = PositionPlayerX - 520.f, msgPY = -270.f;
		float msgNX = PositionPlayerX - 80.f, msgNY = 40.f;

		timeTalk = clTalk.getElapsedTime().asSeconds();
//		while (MENU == true)
//		{
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
			// mouse position
			sf::Vector2f mousePosition = sf::Vector2f(0.0f, 0.0f);
			mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
			//printf("%f \t%f\n", mousePosition.x, mousePosition.y);

			//printf("%f \t%f\n", player.GetPosition().x, player.GetPosition().y);

			// frameRate 
			//time = clock.restart();
			//float fps = time.asSeconds();
			//printf("%f\n", 1.0f / fps);

			deltaTime = clock.restart().asSeconds();
			if (deltaTime > 1.0f / 20.0f)
				deltaTime = 1.0f / 20.0f;
			
/*			if (cheakhighscore == false) {
				window.draw(menu01);
				window.display();
			}
			if (sf::Mouse::getPosition(window).x >= 427 && sf::Mouse::getPosition(window).y >= 275 &&
				sf::Mouse::getPosition(window).x <= 660 && sf::Mouse::getPosition(window).y <= 348)
			{
				window.draw(menu01);
				window.display();
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					MENU = false;
					START = false;
					MemScore = true;
				}
			}
			/*
			else if (sf::Mouse::getPosition(window).x >= 427 && sf::Mouse::getPosition(window).y >= 395 &&
				sf::Mouse::getPosition(window).x <= 660 && sf::Mouse::getPosition(window).y <= 466)
			{
				window.draw(bg);
				window.draw(bg3);
				window.display();
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && (timerpausemenu.getElapsedTime().asSeconds() >= 0.3))
				{
					MENU = false;
					START = false;
					Rank = true;
				}
			}
			else if (sf::Mouse::getPosition(window).x >= 427 &&	sf::Mouse::getPosition(window).y >= 515 &&
				sf::Mouse::getPosition(window).x <= 660 && sf::Mouse::getPosition(window).y <= 584)
			{
				window.draw(bg);
				window.draw(bg4);
				window.display();
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					window.close();
					break;
				}
			}*/
			
//		}

		HP.setPosition(sf::Vector2f(view.getCenter().x - 520.0f , -350.0f));
		
		player.Update(deltaTime);
		view.setCenter(sf::Vector2f(player.GetPosition().x, 0));

		// check collider
		//Collider itemCollision = item.GetCollider();
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
		
		for (int i = 0; i < itemVector.size(); i++) {
			itemVector[i].Update(deltaTime, player);
		}
		
		// storyTalk /////////////////////////
		//timeTalk = clTalk.restart().asSeconds() * 100;
		// storyTalk NPC1
		if (PositionPlayerX >= 9650 && PositionPlayerX <= 9900)
		{
			if (talk1 == 0) 
			{
				//printf("unpressed\n");
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) /*&& timeTalk > 3.0f*/)
				{
					//printf("pressed talk");
					//printf("%f %d\n----\n", timeTalk, npc1);
				
					talk1 = 1;
					//timeTalk = 0;
					clTalk.restart();
				}
			}
			if (talk1 == 1)
			{
				printf("1234567 %f %d\n", timeTalk, npc1);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && timeTalk > 5.0f)
				{
					printf("yahoo %f %d\n", timeTalk, npc1);
					npc1 = 0;
					//timeTalk = 0;
					clTalk.restart();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && timeTalk > 5.0f)
				{
					printf("yahoo1 %f %d\n", timeTalk, npc1);
					npc1 = 1;
					clTalk.restart();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && timeTalk > 5.0f)
				{
					npc1 = 2;
					clTalk.restart();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && timeTalk > 2.0f)
				{
					npc1 = 3;
					clTalk.restart();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && timeTalk > 2.0f)
				{
					npc1 = 4;
					talk1 = 2;
					clTalk.restart();
				}
			}
		}
		else { talk1 = 0; }

		// warp
		if (PositionPlayerX >= 10100 && PositionPlayerX <= 10400)
		{
			if (warp1 == 0)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) { warp1 = 1; }
			}
			if (warp1 == 1)
			{
				player.SetPosition(sf::Vector2f(13000.f, 275.f));
			}
		}
		if (PositionPlayerX >= 22360 && PositionPlayerX <= 22660)
		{
			if (warp2 == 0)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) { warp2 = 1; }
			}
			if (warp2 == 1)
			{
				player.SetPosition(sf::Vector2f(25500.f, 275.f));
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
			myHP = 78000;
			HP.setSize(sf::Vector2f(myHP / 320.f, 25));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			//enemy hit 0 hp

		window.clear();
//		window.clear(sf::Color(170, 237, 202));
		window.draw(bg01);
		window.draw(bg02);
		window.draw(bg03);
		window.setView(view);
		window.draw(warpPoint);
		window.draw(warpPoint1);
		window.draw(story01);
		window.draw(story02);
		window.draw(story03);

		window.draw(HP);
		player.Draw(window);
		for (int i = 0; i < enemyVector.size(); i++) {
			for (Platform& platform : platforms) {
				if (platform.GetCollider().CheckCollision(enemyVector[i].GetCollider(), direction, 1.0f));
				enemyVector[i].OnCollision(direction);
			}
		}
		
		for (Platform& platform : platforms)
		{
			//platform.GetCollider().CheckCollisionM(enemyCollision, 1.0f);
			platform.Draw(window);
		}
		for (int i = 0; i < itemVector.size(); i++) {
			itemVector[i].Draw(window);
		}
		for (int i = 0; i < enemyVector.size(); i++) {	
			enemyVector[i].Draw(window);
		}

		for (int i = 0; i < enemyVector.size(); i++)
		{
			if (enemyVector[i].GetCollider().CheckCollisionM(playerCollision, 1.0f) )
			{
				myHP -= 200;
				HP.setSize(sf::Vector2f(myHP / 320.f, 25));
				k = 1;
			}
			/*if (k == 1 && player.crawlRe() == 1)
			{
				printf("%d %f \n", player.crawlRe(), player.delayCrawlRe());
				enemyVector.erase(enemyVector.begin() + i);
				k = 0;
			}*/
		}
		
		
		for (int i = 0; i < enemyVector.size(); i++) {
			delayTime += cl.restart().asSeconds();
			//printf("%f %f \n", delayTime, cl.restart().asSeconds());
			//printf("%f \n", deltaTime);
			//clock.restart();
			if (k == 1 && player.crawlRe() == 1 && delayTime > 1)
			{
				k = 0;
				//printf("%d %f \n", player.crawlRe(), player.delayCrawlRe());
				//printf("%f %f \n", delayTime, cl.restart().asSeconds());
				enemyVector.erase(enemyVector.begin() + i);
				delayTime = 0.f;
				cl.restart();
				
			}
		}


		for (int i = 0; i < itemVector.size(); i++)
		{
			if (itemVector[i].GetCollider().CheckCollisions(playerCollision))
			{
				myHP += 500;
				HP.setFillColor(sf::Color::Magenta);
				HP.setSize(sf::Vector2f(myHP / 320.f, 25.f));
				itemVector.erase(itemVector.begin() + i); // after collided a item, it will disappear ?
			}	
		}

		if (PositionPlayerX >= 9650 && PositionPlayerX <= 9900)
		{
			if (talk1 == 0)
			{
				msgToTalk.setPosition(sf::Vector2f(9650.f, 0.0f));
				window.draw(msgToTalk);
			}
			if (talk1 == 1)
			{
				//printf("%d\n", npc1);
				msgBoxPlayer.setPosition(sf::Vector2f(msgPX, msgPY));
				msgBoxNPC1.setPosition(sf::Vector2f(msgNX, msgNY));
				talk01_1.setPosition(sf::Vector2f(msgPX + 125.f, msgPY + 45.f));
				talk01_2.setPosition(sf::Vector2f(msgNX + 45.f, msgNY + 45.f));
				talk01_3.setPosition(sf::Vector2f(msgPX + 125.f, msgPY + 45.f));
				talk01_4.setPosition(sf::Vector2f(msgNX + 45.f, msgNY + 45.f));
				talk01_5.setPosition(sf::Vector2f(msgPX + 125.f, msgPY + 45.f));
				talk01_6.setPosition(sf::Vector2f(msgNX + 45.f, msgNY + 45.f));
				talk01_7.setPosition(sf::Vector2f(msgPX + 125.f, msgPY + 45.f));
				talk01_8.setPosition(sf::Vector2f(msgNX + 45.f, msgNY + 45.f));
				if (npc1 == 0)
				{
					window.draw(msgBoxPlayer);
					window.draw(msgBoxNPC1);
					window.draw(talk01_1);
					window.draw(talk01_2);
				}
				if (npc1 == 1)
				{
					window.draw(msgBoxPlayer);
					window.draw(msgBoxNPC1);
					window.draw(talk01_3);
					window.draw(talk01_4);
				}
				if (npc1 == 2)
				{
					window.draw(msgBoxPlayer);
					window.draw(msgBoxNPC1);
					window.draw(talk01_5);
					window.draw(talk01_6);
				}				
				if (npc1 == 3)
				{
					window.draw(msgBoxPlayer);
					window.draw(msgBoxNPC1);
					window.draw(talk01_7);
					window.draw(talk01_8);
				}
				if (npc1 == 4)
				{
					window.draw(msgBoxPlayer);
					window.draw(msgBoxNPC1);

				}
			}
			if (talk1 == 2)
			{
				rareItem1.setPosition(sf::Vector2f(msgNX - 100.0f, msgNY - 275.0f)); // edit positon
				window.draw(rareItem1);
			}
		}
		if (PositionPlayerX >= 10100 && PositionPlayerX <= 10400)
		{
			if (warp1 == 0)
			{
				msgToWarp.setPosition(sf::Vector2f(10100.f, -20.0f));
				window.draw(msgToWarp);
			}
		}	
		if (PositionPlayerX >= 22360 && PositionPlayerX <= 22660)
		{
			if (warp2 == 0)
			{
				msgToWarp.setPosition(sf::Vector2f(22360.f, -20.0f));
				window.draw(msgToWarp);
			}
		}
		


		if (myHP < 0.0f)
		{
			myHP = 0;
			endGame = 1;
		}
		if (myHP > 78000.0f)
		{
			myHP = 78000.0f;
			HP.setFillColor(sf::Color::Magenta);
			HP.setSize(sf::Vector2f(myHP / 320.f, 25.f));
		}
		window.display();
	}
	return 0;
}
