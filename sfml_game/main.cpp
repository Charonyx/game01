#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "Player.h"
#include "Platform.h"
#include "Platform2.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "Item.h"
#include "Time.h"

// a lot of bugs in my game na ka!

static const float View_HEIGHT = 720.0f;
static const float View_WIDTH = 1080.0f;

// varible /////////////////////////////
int npc1 = 0, npc2 = 0, npc3 = 0;
int talk1 = 0, talk2 = 0, talk3 = 0; //0-strt 1-talkin' 2-give-item//already-NPC-disappeared
bool warp1 = 0, warp2 = 0;

int score = 0;

// player blink
int q = 0;
bool checkColi = false;
bool checkDraw = false;

// player 
int Loop = 0;

// menu
bool MENU = true;
bool playGAME = false;
bool how2play = false;
bool RANK = false;
bool setting = false;
bool endGAME = false;
bool enterName = false;
bool pause = false;
bool endOVER = false;

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize((View_HEIGHT)*aspectRatio, View_HEIGHT);
}

int main()
{
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(1080, 720), "Fila Kung");//, sf::Style::Fullscreen);// , sf::Style::Fullscreen
	sf::RectangleShape frame(sf::Vector2f(1080.0f, 720.0f));
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(View_WIDTH, View_HEIGHT));

	window.setFramerateLimit(120);


	// TEXT //////////////////////////   WARNING edit font color
	sf::Font MainFont;
	MainFont.loadFromFile("font/SHOWG.ttf");
	//sf::Text scoreText("score : ", MainFont, 16);
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
	sf::Text talk02_5("Oh! It's mine. ", MainFont, 25);
	sf::Text talk02_6(":D ", MainFont, 25);
	sf::Text talk02_7("Thank you, Mr. Meow. ", MainFont, 25);
	sf::Text talk02_8("No worries. ", MainFont, 25);

	sf::Text talk03_1("Bonjour, Mr. Magic!", MainFont, 25);
	sf::Text talk03_2("Bonjour, Fila-kung! \nCan I help you?", MainFont, 25);
	sf::Text talk03_3("Surely? \nCan you fix my bell collar? ", MainFont, 25);
	sf::Text talk03_4("Certainly, let you give \npieces of your collar to me! ", MainFont, 25);
	sf::Text talk03_5("Here you are.", MainFont, 25);
	sf::Text talk03_6("Great! Wait for a minute....\nFinished! ", MainFont, 25);
	sf::Text talk03_7("Wowwww! \nWhat would I do without you? ", MainFont, 25);
	sf::Text talk03_8("Ha ha ha! \nI'm happy to help. ", MainFont, 25);


	//------------------------------------------------------------- Music & Sound ------------------------------------------------------------//
	// sound crawl
	sf::SoundBuffer ssoundCrawl;
	ssoundCrawl.loadFromFile("sound/catCrawlEnemy.wav");
	sf::Sound soundCrawl;
	soundCrawl.setBuffer(ssoundCrawl);

	// sound jump
	sf::SoundBuffer ssoundJump;
	ssoundJump.loadFromFile("sound/jump.wav");
	sf::Sound soundJump;
	soundJump.setBuffer(ssoundJump);

	// sound click
	sf::SoundBuffer sclick;
	sclick.loadFromFile("sound/click.wav");
	sf::Sound click;
	click.setBuffer(sclick);

	// sound doorwarp
	sf::SoundBuffer sdoorwarp;
	sdoorwarp.loadFromFile("sound/doorwarp.wav");
	sf::Sound sounddoorwarp;
	sounddoorwarp.setBuffer(sdoorwarp);

	// sound player hurt
	sf::SoundBuffer shurt;
	shurt.loadFromFile("sound/hurt-enemy.wav");
	sf::Sound hurt;
	hurt.setBuffer(shurt);

	// sound fullhp
	sf::SoundBuffer sfullhp;
	sfullhp.loadFromFile("sound/fullhp.wav");
	sf::Sound fullhp;
	fullhp.setBuffer(sfullhp);

	// sound skull
	sf::SoundBuffer sskull;
	sskull.loadFromFile("sound/skull.wav");
	sf::Sound skull;
	skull.setBuffer(sskull);

	// sound hp
	sf::SoundBuffer shpup;
	shpup.loadFromFile("sound/hpUp.wav");
	sf::Sound hpup;
	hpup.setBuffer(shpup);
	
	// sound endgame
	sf::SoundBuffer send;
	send.loadFromFile("sound/win2.wav");
	sf::Sound end;
	end.setBuffer(send);

	// sound gameover
	sf::SoundBuffer sover;
	sover.loadFromFile("sound/endgameover.wav");
	sf::Sound soundover;
	soundover.setBuffer(sover);


	// sound 

	// MENU //////////////////////////
	// MENU unpressed
	sf::RectangleShape menu01(sf::Vector2f(0, 0));
	sf::Texture menu;
	menu.loadFromFile("img/menu01.png");
	menu01.setTexture(&menu);
	menu01.setSize(sf::Vector2f(1080.0f, 720.0f));
	menu01.setPosition(sf::Vector2f(0.0f, 0.0f));

	// MENU unpressed
	sf::RectangleShape menu01_0(sf::Vector2f(0, 0));
	sf::Texture menu1_0;
	menu1_0.loadFromFile("img/menu01-0.png");
	menu01_0.setTexture(&menu1_0);
	menu01_0.setSize(sf::Vector2f(1080.0f, 720.0f));
	menu01_0.setPosition(sf::Vector2f(0.0f, 0.0f));

	// MENU pressed play
	sf::RectangleShape menu01_1(sf::Vector2f(0, 0));
	sf::Texture menu1_1;
	menu1_1.loadFromFile("img/menu01-1.png");
	menu01_1.setTexture(&menu1_1);
	menu01_1.setSize(sf::Vector2f(1080.0f, 720.0f));
	menu01_1.setPosition(sf::Vector2f(0.0f, 0.0f));

	// MENU pressed score
	sf::RectangleShape menu01_2(sf::Vector2f(0, 0));
	sf::Texture menu1_2;
	menu1_2.loadFromFile("img/menu01-2.png");
	menu01_2.setTexture(&menu1_2);
	menu01_2.setSize(sf::Vector2f(1080.0f, 720.0f));
	menu01_2.setPosition(sf::Vector2f(0.0f, 0.0f));

	// MENU pressed how to play
	sf::RectangleShape menu01_3(sf::Vector2f(0, 0));
	sf::Texture menu1_3;
	menu1_3.loadFromFile("img/menu01-3.png");
	menu01_3.setTexture(&menu1_3);
	menu01_3.setSize(sf::Vector2f(1080.0f, 720.0f));
	menu01_3.setPosition(sf::Vector2f(0.0f, 0.0f));

	// MENU unpressed home exit
	sf::RectangleShape menux01(sf::Vector2f(0, 0));
	sf::Texture menux1;
	menux1.loadFromFile("img/menux01.png");
	menux01.setTexture(&menux1);
	menux01.setSize(sf::Vector2f(1080.0f, 720.0f));
	menux01.setPosition(sf::Vector2f(0.0f, 0.0f));
	//	menu01_4.setPosition(sf::Vector2f(540.0f, -360.0f));

	// MENU pressed home
	sf::RectangleShape menu01_4(sf::Vector2f(0, 0));
	sf::Texture menu1_4;
	menu1_4.loadFromFile("img/menu01-4.png");
	menu01_4.setTexture(&menu1_4);
	menu01_4.setSize(sf::Vector2f(1080.0f, 720.0f));
	menu01_4.setPosition(sf::Vector2f(0.0f, 0.0f));
	//	menu01_4.setPosition(sf::Vector2f(540.0f, -360.0f));

	// MENU pressed exit
	sf::RectangleShape menu01_5(sf::Vector2f(0, 0));
	sf::Texture menu1_5;
	menu1_5.loadFromFile("img/menu01-5.png");
	menu01_5.setTexture(&menu1_5);
	menu01_5.setSize(sf::Vector2f(1080.0f, 720.0f));
	menu01_5.setPosition(sf::Vector2f(0.0f, 0.0f));
	//	menu01_5.setPosition(sf::Vector2f(540.0f, -360.0f));

	// RANK
	sf::RectangleShape rank(sf::Vector2f(0, 0));
	sf::Texture showRank;
	showRank.loadFromFile("img/score.png");
	rank.setTexture(&showRank);
	rank.setSize(sf::Vector2f(1080.0f, 720.0f));
	rank.setPosition(sf::Vector2f(0.0f, 0.0f));

	// HOW TO  PLAY
	sf::RectangleShape h2play(sf::Vector2f(0, 0));
	sf::Texture show2play;
	show2play.loadFromFile("img/howToPlay.png");
	h2play.setTexture(&show2play);
	h2play.setSize(sf::Vector2f(1080.0f, 720.0f));
	h2play.setPosition(sf::Vector2f(0.0f, 0.0f));

	// GAME OVER
	sf::RectangleShape gameover(sf::Vector2f(0, 0));
	sf::Texture over;
	over.loadFromFile("img/gameOver.png");
	gameover.setTexture(&over);
	gameover.setSize(sf::Vector2f(1080.0f, 720.0f));
	gameover.setPosition(sf::Vector2f(0.0f, 0.0f));	

	// GAME END
	sf::RectangleShape gameend(sf::Vector2f(0, 0));
	sf::Texture win;
	win.loadFromFile("img/gameEnd.png");
	gameend.setTexture(&win);
	gameend.setSize(sf::Vector2f(1080.0f, 720.0f));
	gameend.setPosition(sf::Vector2f(0.0f, 0.0f));	

	// ENTER NAME
	sf::RectangleShape addName(sf::Vector2f(0, 0));
	sf::Texture name;
	name.loadFromFile("img/name.png");
	addName.setTexture(&name);
	addName.setSize(sf::Vector2f(1080.0f, 720.0f));
	addName.setPosition(sf::Vector2f(0.0f, 0.0f));

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
	warpPoint1.setPosition(sf::Vector2f(21025.0f, 25.0f));

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
	story01.setPosition(sf::Vector2f(4250.f, -18.0f));
	float npcc1 = 5450.0f;

	// story02 : NPC state2 MR. Meow
	sf::RectangleShape story02(sf::Vector2f(0.0f, 0.0f));
	sf::Texture storyState02;
	storyState02.loadFromFile("img/story02.png");
	story02.setTexture(&storyState02);
	story02.setSize(sf::Vector2f(60.0f, 60.0f));
	story02.setPosition(sf::Vector2f(9800.f, 243.0f));

	// story03 : NPC state3 MR. Magic
	sf::RectangleShape story03(sf::Vector2f(0.0f, 0.0f));
	sf::Texture storyState03;
	storyState03.loadFromFile("img/story03.png");
	story03.setTexture(&storyState03);
	story03.setSize(sf::Vector2f(60.0f, 60.0f));
	story03.setPosition(sf::Vector2f(20800.f, 243.0f));
	float npcc3 = 11000;
	float warpdis = 1385;
	float platdis = 3000;

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

	// quest 0
	sf::RectangleShape quest0(sf::Vector2f(0.0f, 0.0f));
	sf::Texture q0;
	q0.loadFromFile("img/quest.png");
	quest0.setTexture(&q0);
	quest0.setSize(sf::Vector2f(1080.0f, 720.0f));

	// quest 1
	sf::RectangleShape quest1(sf::Vector2f(0.0f, 0.0f));
	sf::Texture q1;
	q1.loadFromFile("img/quest1.png");
	quest1.setTexture(&q1);
	quest1.setSize(sf::Vector2f(1080.0f, 720.0f));

	// quest 2
	sf::RectangleShape quest2(sf::Vector2f(0.0f, 0.0f));
	sf::Texture q2;
	q2.loadFromFile("img/quest2.png");
	quest2.setTexture(&q2);
	quest2.setSize(sf::Vector2f(1080.0f, 720.0f));

	// quest 3
	sf::RectangleShape quest3(sf::Vector2f(0.0f, 0.0f));
	sf::Texture q3;
	q3.loadFromFile("img/quest3.png");
	quest3.setTexture(&q3);
	quest3.setSize(sf::Vector2f(1080.0f, 720.0f));

	// rare  item1
	sf::RectangleShape rareItem1(sf::Vector2f(0.0f, 0.0f));
	sf::Texture rare1;
	rare1.loadFromFile("img/rareItem1.png");
	rareItem1.setTexture(&rare1);
	rareItem1.setSize(sf::Vector2f(1080.0f, 720.0f));

	// rare  item2
	sf::RectangleShape rareItem2(sf::Vector2f(0.0f, 0.0f));
	sf::Texture rare2;
	rare2.loadFromFile("img/rareItem2.png");
	rareItem2.setTexture(&rare2);
	rareItem2.setSize(sf::Vector2f(1080.0f, 720.0f));

	// rare  item3
	sf::RectangleShape rareItem3(sf::Vector2f(0.0f, 0.0f));
	sf::Texture rare3;
	rare3.loadFromFile("img/rareItem3.png");
	rareItem3.setTexture(&rare3);
	rareItem3.setSize(sf::Vector2f(1080.0f, 720.0f));




	//if (player.GetPosition().x <= 0)
	//{
	//	if (player.GetPosition().x >= x)
	//	{
	//	view.setCenter(sf::Vector2f(player.GetPosition().x, 0));
	//		x++;
	//	}
	//}

	// ENTER NAME
	sf::String playerInput;
	std::ofstream fileWriter;
	std::ostringstream keyname;
	sf::Text Keyname;
	std::string userName;
	std::string namee; //////////////////////
	std::fstream adminFile;
	Keyname.setCharacterSize(40);
	Keyname.setString(" ");
	Keyname.setFont(MainFont);
	Keyname.setFillColor(sf::Color::Black);
	char last_char = ' ';
	sf::RectangleShape cursor;
	cursor.setSize(sf::Vector2f(5.0f, 30.0f));
	cursor.setOrigin(sf::Vector2f(2.5f, 15.0f));
	cursor.setFillColor(sf::Color::Black);
	sf::Text text("", MainFont);

	Keyname.setPosition(300, 500);
	text.setFillColor(sf::Color::Black);
	text.setPosition(545, 535);
	cursor.setPosition(545.0f + text.getGlobalBounds().width + 10, 555.0f);
	float totalTime_cursor = 0;
	sf::Clock clock_cursor;
	bool state_cursor = false;

	std::map<int, std::string> save_score;
	std::ifstream Opentext;
	std::string list;

	// SCORE
	sf::Font scoreFont;
	scoreFont.loadFromFile("font/SHOWG.ttf");
	std::ostringstream score_1;
	sf::Text scoreText;
	scoreText.setCharacterSize(26);
	scoreText.setString(score_1.str());
	scoreText.setFillColor(sf::Color::Black);
	scoreText.setFont(scoreFont);

	// NAME
	std::ostringstream name_1;
	sf::Text nameText;
	nameText.setCharacterSize(66);
	nameText.setString(name_1.str());
	nameText.setFillColor(sf::Color::Black);
	nameText.setFont(scoreFont);

	// PLAYER
	sf::Texture player_texture;
	player_texture.loadFromFile("img/cat2_5.png");
	Player player(&player_texture, sf::Vector2u(3, 3), 0.2f, 300.0f, 150.0f);

	// ENEMY01
	sf::Texture enemy_texture;
	enemy_texture.loadFromFile("img/enemy.png");
	Enemy enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, 300.0f, 275.0f);

	// ENEMY02
	sf::Texture enemy_texture2;
	enemy_texture2.loadFromFile("img/enemy2.png");
	Enemy enemy2(&enemy_texture2, sf::Vector2u(3, 2), 0.2f, 300.0f, 300.0f, 275.0f);

	std::vector <Enemy> enemyVector;
	std::vector <Enemy> enemy2Vector;

	// ITEM HP++
	sf::Texture item01;
	item01.loadFromFile("img/item4.png");
	Item item(&item01, sf::Vector2u(1, 1), 0.2f, 300.0f, 150.0f);

	std::vector <Item> itemVector;
	

	// ITEM HP--
	sf::Texture item02;
	item02.loadFromFile("img/skull.png");
	Item itemDown(&item02, sf::Vector2u(1, 1), 0.2f, 600.0f, 150.0f);

	std::vector <Item> item2Vector;
	
	// get check-point
	sf::Vector2f sprawn;
	sprawn.x = 0.0f;
	sprawn.y = 0.0f;

	// score
	//int score = 0;

	// HP player
	float myHP = 78000;
	sf::RectangleShape HP(sf::Vector2f(myHP / 150.0f, 50.0f));
	//HP.setPosition(sf::Vector2f(-170.0f, -350.0f));
	HP.setFillColor(sf::Color::Magenta);
	HP.setSize(sf::Vector2f(myHP / 320.f, 25.0f));


	// Platform floor == texture size position
	std::vector<Platform> platforms;
	std::vector<Platform2> platforms2;
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

	//...
	platforms2.push_back(Platform2(&floor, sf::Vector2f(200.0f, 40.0f), 3800.0f, 55.0f, 0.2f, 250.0f));		//
	platforms2.push_back(Platform2(&floor, sf::Vector2f(300.0f, 40.0f), 4300.0f, 55.0f, 0.2f, 0.0f));		//
	platforms2.push_back(Platform2(&floor, sf::Vector2f(200.0f, 40.0f), 4550.0f, 55.0f, 0.2f, 250.0f));		//
	//...
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
	platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 100.0f), sf::Vector2f(13400.0f, 255.0f)));	//tutorial

	platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 40.0f), sf::Vector2f(14400.0f + 2000, 175.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 40.0f), sf::Vector2f(14500.0f + 2000, 135.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 40.0f), sf::Vector2f(14600.0f + 2000, 95.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(700.0f, 40.0f), sf::Vector2f(15000.0f + 2000, 55.0f)));		// item under	
	platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 40.0f), sf::Vector2f(15600.0f + 2000, 175.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 40.0f), sf::Vector2f(15500.0f + 2000, 135.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 40.0f), sf::Vector2f(15400.0f + 2000, 95.0f)));



	platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 40.0f), sf::Vector2f(15000.0f + 3600 , 175.0f)));
	platforms2.push_back(Platform2(&floor, sf::Vector2f(200.0f, 40.0f), 3800.0f + 15000, 55.0f, 0.2f, 250.0f));	//
	platforms2.push_back(Platform2(&floor, sf::Vector2f(300.0f, 40.0f), 4300.0f + 15000, 55.0f, 0.2f, 0.0f));	//
	platforms2.push_back(Platform2(&floor, sf::Vector2f(200.0f, 40.0f), 4550.0f + 15000, 55.0f, 0.2f, 250.0f));	//
	platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 40.0f), sf::Vector2f(5000.0f + 15000, 175.0f)));

	// state 3
	platforms.push_back(Platform(nullptr, sf::Vector2f(12800.0f, 100.0f), sf::Vector2f(23060.0f, 350.0f)));	//main
/*	platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 100.0f), sf::Vector2f(400.0f, 255.0f)));		//tutorial

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
	sf::Time time;			//frame rate
	sf::Clock cl;			// hit enemy
	sf::Clock timercoli;	// check player blink
	sf::Clock clTalk;		// NPC talk
	float counTime;			// enter name
	float timeTalk = 0;

	float delayTime = 0.f;
	float dTime = 0.4;
	//delayTime += deltaTime;

	while (window.isOpen())
	{		
		deltaTime = clock.restart().asSeconds();
		//if (deltaTime > 1.0f / 20.0f)
		//	deltaTime = 1.0f / 20.0f;
		
		//view.setCenter(sf::Vector2f(540, 0));

		while (MENU == true)
		{
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
			//view.setCenter(sf::Vector2f(540, 0));

			window.draw(menu01);
			window.draw(menu01_0);
			window.draw(menux01);

			// mouse position
			sf::Vector2f mousePosition = sf::Vector2f(0.0f, 0.0f);
			mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
			//printf("%f \t%f\n", mousePosition.x, mousePosition.y);

			//printf("%f \t%f\n", player.GetPosition().x, player.GetPosition().y);

			// frameRate 
			//time = clock.restart();
			//float fps = time.asSeconds();
			//printf("%f\n", 1.0f / fps);

			if (sf::Mouse::getPosition(window).x >= 380 && sf::Mouse::getPosition(window).y >= 265 &&
				sf::Mouse::getPosition(window).x <= 665 && sf::Mouse::getPosition(window).y <= 330) {
				window.draw(menux01);
				window.draw(menu01_1);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					click.play();
					MENU = false;
					playGAME = false;
					enterName = true;
					
				}
			}
			else if (sf::Mouse::getPosition(window).x >= 380 && sf::Mouse::getPosition(window).y >= 380 &&
				sf::Mouse::getPosition(window).x <= 665 && sf::Mouse::getPosition(window).y <= 445) {
				window.draw(menux01);
				window.draw(menu01_2);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					click.play();
					MENU = false;
					RANK = true;
				}
			}
			else if (sf::Mouse::getPosition(window).x >= 380 && sf::Mouse::getPosition(window).y >= 485 &&
				sf::Mouse::getPosition(window).x <= 665 && sf::Mouse::getPosition(window).y <= 555) {
				window.draw(menux01);
				window.draw(menu01_3);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					click.play();
					MENU = false;
					how2play = true;
				}
			}
			else if (sf::Mouse::getPosition(window).x >= 23 && sf::Mouse::getPosition(window).y >= 647 &&
				sf::Mouse::getPosition(window).x <= 75 && sf::Mouse::getPosition(window).y <= 689) {
				window.draw(menu01_0);
				window.draw(menu01_4);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					click.play();
					MENU = false;
					setting = true;
				}
			}
			else if (sf::Mouse::getPosition(window).x >= 997 && sf::Mouse::getPosition(window).y >= 637 &&
				sf::Mouse::getPosition(window).x <= 1046 && sf::Mouse::getPosition(window).y <= 689) {
				window.draw(menux01);
				window.draw(menu01_5);
				
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					click.play();
					window.close();
					break;
				}
			}
			window.display();
		}
		/**/
		while (enterName == true) {
			//counTime += deltaTime;
			sf::Event event;
			while (window.pollEvent(event)) {
				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();
					break;
				}
			}

			if (event.type == sf::Event::TextEntered && last_char != event.text.unicode)
			{
				if (event.text.unicode == 13) { // ESC
					userName = playerInput;
					playerInput.clear();
					MENU = true; //edit?

				}
				else if (event.text.unicode == 8 && playerInput.getSize() > 0) { // backspace delete
					playerInput = playerInput.substring(0, playerInput.getSize() - 1);
				}
				else {
					if (playerInput.getSize() < 10) {
						//if (counTime > 0.2) {
							playerInput += event.text.unicode;
							//counTime = 0;
						//}
					}
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
					MENU = false;
					enterName = false;
					playGAME = true;
				}

				last_char = event.text.unicode;
				text.setString(playerInput);
				cursor.setPosition(545.0f + text.getGlobalBounds().width + 10, 555.0f);
			}
			else if (event.type == sf::Event::EventType::KeyReleased && last_char != ' ') {
				last_char = ' ';
			}
			window.clear();
			//window.draw(key);
			window.draw(addName);
			window.draw(Keyname);

			totalTime_cursor += clock_cursor.restart().asSeconds();
			if (totalTime_cursor >= 0.5) {
				totalTime_cursor = 0;
				state_cursor = !state_cursor;
			}
			if (state_cursor == true) {

				window.draw(cursor);
			}
			window.draw(text);

			window.display();

		}
		/**/
		while (RANK == true) {
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
			//view.setCenter(sf::Vector2f(view.getCenter().x - 540, -360));
			printf("loop : %d..\n", Loop);
			if (Loop == 0) {

				view.setCenter(sf::Vector2f(540, 360));
			}

			
			// mouse position
			sf::Vector2f mousePosition = sf::Vector2f(0.0f, 0.0f);
			mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
			printf("%f \t%f\n", mousePosition.x, mousePosition.y);

			window.clear();
			window.draw(rank);

			sf::Text text1("", MainFont);
			text1.setCharacterSize(30);
			text1.setFillColor(sf::Color::Black);

			Opentext.open("text/highScore.txt");
			do {
				Opentext >> list;
				std::string first_token = list.substr(0, list.find(','));
				int second_token = std::stoi(list.substr(list.find(',') + 1, list.length()));
				save_score[second_token] = first_token;
			} while (Opentext.good());
			Opentext.close();
			std::map<int, std::string>::iterator end = save_score.end();
			std::map<int, std::string>::iterator beg = save_score.begin();
			end--;
			beg--;
			int currentDisplay = 0;
			for (std::map<int, std::string>::iterator it = end; it != beg; it--) {
				

				text1.setString(it->second);
				//text1.setPosition(view.getCenter().x - 170, 210 + 80 * currentDisplay);

				text1.setPosition(view.getCenter().x - 170, -110 + 80 * currentDisplay);  //250
				window.draw(text1);
				text1.setString(std::to_string(it->first));
				text1.setPosition(view.getCenter().x + 85, -110 + 80 * currentDisplay); //250
				window.draw(text1);
				currentDisplay++;

				if (currentDisplay == 5)
				{
					break;
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Home))
			{
				//Soundch.play();
				RANK = false;
				MENU = true;
				//scoreSound.stop();
			}
			window.display();
		}
		
				

		while (how2play == true) {
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
			printf("%f \t%f\n", mousePosition.x, mousePosition.y);

			//view.setCenter(sf::Vector2f(540,-360));
			window.draw(h2play);


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Home))
			{
				//Soundch.play();
				how2play = false;
				MENU = true;
				//scoreSound.stop();
			}
			window.display();
		}

		deltaTime = 0;
		clock.restart();
		score = 0;
		myHP = 78000;
		talk1 = 0, talk2 = 0, talk3 = 0;
		npc1 = 0, npc2 = 0, npc3 = 0;
		//HP.setFillColor(sf::Color::Magenta);
		HP.setSize(sf::Vector2f(myHP / 320.f, 25.0f));

		enemyVector.push_back(Enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 500 + 2400, 275));
	enemyVector.push_back(Enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 500 + 2800, 275));
	enemyVector.push_back(Enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 500 + 1200, 275));
	enemyVector.push_back(Enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 500 + 1600, 275));
	enemyVector.push_back(Enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 500 + 2000, 275));

	enemyVector.push_back(Enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 500 + 5000, 275));
	enemyVector.push_back(Enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 500 + 6000, 275));
	enemyVector.push_back(Enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 500 + 5500, 275));
	enemyVector.push_back(Enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 500 + 8000, 275));
	enemyVector.push_back(Enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 500 + 7000, 275));
	enemyVector.push_back(Enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 500 + 7500, 275));
	enemyVector.push_back(Enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 500 + 8500, 275));
	enemyVector.push_back(Enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 500 + 9000, 275));
	enemyVector.push_back(Enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 500 + 9000, 275));

	enemyVector.push_back(Enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 500 + 7000, 275));
	enemyVector.push_back(Enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 500 + 8500, 275));
	

	enemyVector.push_back(Enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 1500 + 17000, 275));
	enemyVector.push_back(Enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 1500 + 16000, 275));
	enemyVector.push_back(Enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 1500 + 15500, 275));
	enemyVector.push_back(Enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 1500 + 18000, 275));
	enemyVector.push_back(Enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 1500 + 17000, 275));
	enemyVector.push_back(Enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 1500 + 17500, 275));
	enemyVector.push_back(Enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 1500 + 18500, 275));
	enemyVector.push_back(Enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 1500 + 19000, 275));

	enemyVector.push_back(Enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 500 + 17000, 275));
	enemyVector.push_back(Enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 500 + 16000, 275));
	enemyVector.push_back(Enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 500 + 15500, 275));
	enemyVector.push_back(Enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 500 + 18000, 275));
	enemyVector.push_back(Enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 1000 + 17000, 275));
	enemyVector.push_back(Enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 500 + 17500, 275));
	enemyVector.push_back(Enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 500 + 18500, 275));
	enemyVector.push_back(Enemy(&enemy_texture, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 500 + 19000, 275));

	// ENEMY2
	enemy2Vector.push_back(Enemy(&enemy_texture2, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 2500 + 5800, 275));
	enemy2Vector.push_back(Enemy(&enemy_texture2, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 2500 + 6200, 275));
	enemy2Vector.push_back(Enemy(&enemy_texture2, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 2500 + 7600, 275));
	enemy2Vector.push_back(Enemy(&enemy_texture2, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 2500 + 8000, 275));

	enemy2Vector.push_back(Enemy(&enemy_texture2, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 2500 + 15800, 275));
	enemy2Vector.push_back(Enemy(&enemy_texture2, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 2500 + 16200, 275));
	enemy2Vector.push_back(Enemy(&enemy_texture2, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 2500 + 17600, 275));
	enemy2Vector.push_back(Enemy(&enemy_texture2, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 2500 + 18000, 275));
	
	enemy2Vector.push_back(Enemy(&enemy_texture2, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 500 + 15000, 275));
	enemy2Vector.push_back(Enemy(&enemy_texture2, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 500 + 16000, 275));
	enemy2Vector.push_back(Enemy(&enemy_texture2, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 500 + 15500, 275));
	enemy2Vector.push_back(Enemy(&enemy_texture2, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 500 + 18000, 275));
	enemy2Vector.push_back(Enemy(&enemy_texture2, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 500 + 17000, 275));
	
	enemy2Vector.push_back(Enemy(&enemy_texture2, sf::Vector2u(3, 2), 0.2f, 300.0f, rand() % 500 + 17000, 275));

	item2Vector.push_back(Item(&item02, sf::Vector2u(1, 1), 0.2f, rand() % 1500 + 2000, 275));
	item2Vector.push_back(Item(&item02, sf::Vector2u(1, 1), 0.2f, rand() % 1500 + 3000, 275));
	item2Vector.push_back(Item(&item02, sf::Vector2u(1, 1), 0.2f, rand() % 1500 + 4000, 275));
	item2Vector.push_back(Item(&item02, sf::Vector2u(1, 1), 0.2f, rand() % 1500 + 8000, 275));
	item2Vector.push_back(Item(&item02, sf::Vector2u(1, 1), 0.2f, rand() % 1500 + 9000, 275));
	item2Vector.push_back(Item(&item02, sf::Vector2u(1, 1), 0.2f, rand() % 1500 + 11000, 275));
	item2Vector.push_back(Item(&item02, sf::Vector2u(1, 1), 0.2f, rand() % 1500 + 8000, 275));

	itemVector.push_back(Item(&item01, sf::Vector2u(1, 1), 0.2f, rand() % 1500 + 2400, 275));
	itemVector.push_back(Item(&item01, sf::Vector2u(1, 1), 0.2f, rand() % 1500 + 3000, 275));
	itemVector.push_back(Item(&item01, sf::Vector2u(1, 1), 0.2f, rand() % 500 + 6000, 275));
	itemVector.push_back(Item(&item01, sf::Vector2u(1, 1), 0.2f, rand() % 500 + 7800, 275));
	itemVector.push_back(Item(&item01, sf::Vector2u(1, 1), 0.2f, rand() % 1500 + 7800, 275));

	item2Vector.push_back(Item(&item02, sf::Vector2u(1, 1), 0.2f, rand() % 1500 + 16000, 275));
	item2Vector.push_back(Item(&item02, sf::Vector2u(1, 1), 0.2f, rand() % 1500 + 17000, 275));
	item2Vector.push_back(Item(&item02, sf::Vector2u(1, 1), 0.2f, rand() % 1500 + 14000, 275));
	item2Vector.push_back(Item(&item02, sf::Vector2u(1, 1), 0.2f, rand() % 1500 + 15000, 275));
	item2Vector.push_back(Item(&item02, sf::Vector2u(1, 1), 0.2f, rand() % 1500 + 16500, 275));
	item2Vector.push_back(Item(&item02, sf::Vector2u(1, 1), 0.2f, rand() % 1500 + 17000, 275));

	itemVector.push_back(Item(&item01, sf::Vector2u(1, 1), 0.2f, rand() % 1500 + 18400, 275));
	itemVector.push_back(Item(&item01, sf::Vector2u(1, 1), 0.2f, rand() % 1500 + 17000, 275));
	itemVector.push_back(Item(&item01, sf::Vector2u(1, 1), 0.2f, rand() % 500 + 16000, 275));
	itemVector.push_back(Item(&item01, sf::Vector2u(1, 1), 0.2f, rand() % 500 + 20000, 275));
	itemVector.push_back(Item(&item01, sf::Vector2u(1, 1), 0.2f, rand() % 1500 + 16000, 275));

		while (playGAME == true) {

			float PositionPlayerX = float((player.GetCollider().GetPosition().x));//float(player.GetPosition().x); //float((player.GetCollider().GetPosition().x));
			float PositionPlayerY = float((player.GetCollider().GetPosition().y));//float(player.GetPosition().y); //float((player.GetCollider().GetPosition().y));

			float msgPX = PositionPlayerX - 520.f, msgPY = -270.f;
			float msgNX = PositionPlayerX - 80.f, msgNY = 40.f;

			timeTalk = clTalk.getElapsedTime().asSeconds();
			printf("%f %f\n", PositionPlayerX, PositionPlayerY);
			
			//printf("%f \t%f\n", view.getCenter().x, view.getCenter().y);

			deltaTime = clock.restart().asSeconds();
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

			//	printf("%f %f\n", a, b);
			// mouse position
			sf::Vector2f mousePosition = sf::Vector2f(0.0f, 0.0f);
			mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
			//printf("%f \t%f\n", mousePosition.x, mousePosition.y);


			view.setCenter(player.GetPosition().x, 0.0f);

			if (view.getCenter().x - 540.0f <= 0.0f)
			{
				view.setCenter(540.0f, 0.0f);
			}
			if (player.GetPosition().x >= 10500) {
				if (view.getCenter().x - 540.0f <= 10500.0f) {
					view.setCenter(11040.0f, 0.0f);
				}
			}			
			//if (player.GetPosition().x >= 13500) {
			//	if (view.getCenter().x - 540.0f <= 13500.0f) {
			//		view.setCenter(1.0f, 0.0f);
			//	}
			//}
			if (view.getCenter().x + 540.0f >= 22000.0f) {
				view.setCenter(22540.0f, 0.0f);
			}

			// SET POSITION HP
			HP.setPosition(sf::Vector2f(view.getCenter().x - 520.0f, -350.0f));

			// SHOW SCORE 
			score_1.str(" ");
			score_1 << "SCORE : " << score;
			scoreText.setString(score_1.str());
			scoreText.setPosition(sf::Vector2f(view.getCenter().x + 300.0f, -350.0f));

			// QUEST POSITION
			quest0.setPosition(sf::Vector2f(view.getCenter().x - 540.0f, -360.0f));
			quest1.setPosition(sf::Vector2f(view.getCenter().x - 540.0f, -360.0f));
			quest2.setPosition(sf::Vector2f(view.getCenter().x - 540.0f, -360.0f));
			quest3.setPosition(sf::Vector2f(view.getCenter().x - 540.0f, -360.0f));


			// check collider
			//Collider itemCollision = item.GetCollider();
			Collider enemyCollision = enemy.GetCollider();
			Collider playerCollision = player.GetCollider();
			sf::Vector2f direction;

			for (Platform& platform : platforms)
				if (platform.GetCollider().CheckCollision(playerCollision, direction, 1.0f))
					player.OnCollision(direction);

			// check point
			if (player.GetPosition().y > 1000) {
				player.SetPosition(sf::Vector2f(sprawn));
			}
			if (player.GetPosition().x > 350) {
				sprawn.x = 350;
				sprawn.y = 0;
			}

			if (endGAME == false && endOVER == false) {

				player.Update(deltaTime);
				//Player player = player;
				for (int i = 0; i < enemyVector.size(); i++) {
					enemyVector[i].Update2(deltaTime, player);
				}
				for (int i = 0; i < enemy2Vector.size(); i++) {
					enemy2Vector[i].Update2(deltaTime, player);
				}
				for (int i = 0; i < itemVector.size(); i++) {
					itemVector[i].Update(deltaTime, player);
				}
				for (int i = 0; i < item2Vector.size(); i++) {
					item2Vector[i].Update(deltaTime, player);
				}
				// item 3 yarn ball
				for (int i = 0; i < item2Vector.size(); i++) {
					item2Vector[i].Update(deltaTime, player);
				}
				for (int i = 0; i < platforms2.size(); i++) {
					platforms2[i].UpdateX(deltaTime);
				}
			}

			// storyTalk /////////////////////////////////////////////////////////////////////////////////////////
			//timeTalk = clTalk.restart().asSeconds() * 100;
			// storyTalk NPC1
			if (PositionPlayerX >= 9650 - npcc1 && PositionPlayerX <= 9900 - npcc1)
			{
				//printf("111 %d\n", talk1);
				if (talk1 == 0) {
					//printf("123 %d\n", talk1);
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
						talk1 = 1;
						clTalk.restart();
					}
				}
				if (talk1 == 1) {
					//printf("1234567 %f %d\n", timeTalk, npc1);
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && timeTalk > 1.0f) {
						//printf("yahoo %f %d\n", timeTalk, npc1);
						npc1 = 0;
						clTalk.restart();
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && timeTalk > 1.0f) {
						//printf("yahoo1 %f %d\n", timeTalk, npc1);
						npc1 = 1;
						clTalk.restart();
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && timeTalk > 1.0f) {
						npc1 = 2;
						clTalk.restart();
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::T) && timeTalk > 1.0f) {
						npc1 = 3;
						clTalk.restart();
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y) && timeTalk > 1.0f) {
						npc1 = 4;
						clTalk.restart();
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::U) && timeTalk > 1.0f) {
						npc1 = 5;
						clTalk.restart();
					}
				}
			}
			else { talk1 = 0; }
			
			// storyTalk NPC2
			if (PositionPlayerX >= 9650 && PositionPlayerX <= 9900)
			{
				//printf("111 %d\n", talk2);
				if (talk2 == 0) {
					//printf("123 %d\n", talk2);
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
						talk2 = 1;
						clTalk.restart();
					}
				}
				if (talk2 == 1) {
					//printf("1234567 %f %d\n", timeTalk, npc2);
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && timeTalk > 1.0f) {
						//printf("yahoo %f %d\n", timeTalk, npc2);
						npc2 = 0;
						clTalk.restart();
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && timeTalk > 1.0f) {
						//printf("yahoo1 %f %d\n", timeTalk, npc2);
						npc2 = 1;
						clTalk.restart();
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && timeTalk > 1.0f) {
						npc2 = 2;
						clTalk.restart();
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::T) && timeTalk > 1.0f) {
						npc2 = 3;
						clTalk.restart();
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y) && timeTalk > 1.0f) {
						npc2 = 4;
						clTalk.restart();
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::U) && timeTalk > 1.0f) {
						npc2 = 5;
						clTalk.restart();
					}
				}
			}
			else { talk2 = 0; }

			// storyTalk NPC3
			if (PositionPlayerX >= 9650 + npcc3 && PositionPlayerX <= 9900 + npcc3)
			{
				//printf("111 %d\n", talk3);
				if (talk3 == 0) {
					//printf("123 %d\n", talk3);
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
						talk3 = 1;
						clTalk.restart();
					}
				}
				if (talk3 == 1) {
					//printf("1234567 %f %d\n", timeTalk, npc3);
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && timeTalk > 1.0f) {
						//printf("yahoo %f %d\n", timeTalk, npc3);
						npc3 = 0;
						clTalk.restart();
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && timeTalk > 1.0f) {
						//printf("yahoo1 %f %d\n", timeTalk, npc2);
						npc3 = 1;
						clTalk.restart();
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && timeTalk > 1.0f) {
						npc3 = 2;
						clTalk.restart();
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::T) && timeTalk > 1.0f) {
						npc3 = 3;
						clTalk.restart();
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y) && timeTalk > 1.0f) {
						npc3 = 4;
						clTalk.restart();
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::U) && timeTalk > 1.0f) {
						npc3 = 5;
						clTalk.restart();
					}
				}
			}
			else { talk3 = 0; }

			// warp
			if (PositionPlayerX >= 10100 && PositionPlayerX <= 10400) {
				if (warp1 == 0) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) { warp1 = 1; sounddoorwarp.play(); }
				}
				if (warp1 == 1) {
					player.SetPosition(sf::Vector2f(14000.f, 275.f));
				}
			}
			if (PositionPlayerX >= 22360 - warpdis && PositionPlayerX <= 22660 - warpdis) {
				if (warp2 == 0) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) { warp2 = 1; end.play(); }
				}
			}
			if (warp2 == 1) {
				//player.SetPosition(sf::Vector2f(25500.f, 275.f));
				playGAME = false;
				RANK = false;
				how2play = false;
				MENU = false;
				endOVER = false;
				endGAME = true;
			}

			// pause //////////////////////////////////////
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) /* && sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) */) {
				window.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Home) /* && sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) */) {
				pause = true;
			}
			if (pause == true) {
				MENU = true;
				playGAME = false;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
				myHP = 78000;
				HP.setSize(sf::Vector2f(myHP / 320.f, 25));
				fullhp.play();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
				//enemy hit 0 hp
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				soundJump.play();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
				soundCrawl.play();
			}
				window.clear();
			//		window.clear(sf::Color(170, 237, 202));

			window.draw(bg01);
			window.draw(bg02);
			window.draw(bg03);
			window.setView(view);
			window.draw(warpPoint);
			window.draw(warpPoint1);
			if (talk1 != 3) {
				window.draw(story01);
			}
			if (talk2 != 3) {
				window.draw(story02);
			}
			if (talk3 != 3) {
				window.draw(story03);
			}
			window.draw(quest0);
			window.draw(HP);
			window.draw(scoreText);

			// draw player
			if (checkColi == true) {
				if (q < 10) {
					if (q % 2 == 0 && timercoli.getElapsedTime().asSeconds() >= 0.05) {
						checkDraw = true;
						q++;
						timercoli.restart();
					}
					else if (q % 2 != 0 && timercoli.getElapsedTime().asSeconds() >= 0.05) {
						checkDraw = false;
						q++;
						timercoli.restart();
					}
					if (q == 10) {
						checkColi = false;
					}
				}
			}
			if (checkDraw == false) {
				player.Draw(window);
			}

			for (int i = 0; i < enemyVector.size(); i++) {
				for (Platform& platform : platforms) {
					if (platform.GetCollider().CheckCollision(enemyVector[i].GetCollider(), direction, 1.0f));
					enemyVector[i].OnCollision(direction);
				}
			}
			if (score > 5000) {
				for (int i = 0; i < enemy2Vector.size(); i++) {
					for (Platform& platform : platforms) {
						if (platform.GetCollider().CheckCollision(enemy2Vector[i].GetCollider(), direction, 1.0f));
						enemy2Vector[i].OnCollision(direction);
					}
				}
			}

			// DRAW //////////////////////////////////////////////////
			for (Platform& platform : platforms) {
				//platform.GetCollider().CheckCollisionM(enemyCollision, 1.0f);
				platform.Draw(window);
			}

			for (int i = 0; i < platforms2.size(); i++) {
				platforms2[i].Draw(window);
			}
			for (int i = 0; i < itemVector.size(); i++) {
				itemVector[i].Draw(window);
			}
			for (int i = 0; i < item2Vector.size(); i++) {
				item2Vector[i].Draw(window);
			}
			for (int i = 0; i < enemyVector.size(); i++) {
				enemyVector[i].Draw(window);
			}
			if (score >= 5000) {
				for (int i = 0; i < enemy2Vector.size(); i++) {
					enemy2Vector[i].Draw(window);
				}
			}
			for (int i = 0; i < enemyVector.size(); i++) {
				if (enemyVector[i].GetCollider().CheckCollisionM(playerCollision, 1.0f)) {
					myHP -= 200;
					HP.setSize(sf::Vector2f(myHP / 320.f, 25));
					//hurt.play();
					k = 1;
					delayTime += cl.restart().asSeconds();

					//printf("%f %f \n", delayTime, cl.restart().asSeconds());
					//printf("%f \n", deltaTime);
					//clock.restart();

					if (player.crawlRe() == 1) {

						if (delayTime > 1) {

							//printf("%d %f \n", player.crawlRe(), player.delayCrawlRe());
							//printf("%f %f \n", delayTime, cl.restart().asSeconds());				
							enemyVector.erase(enemyVector.begin() + i);
							
							score += 1500;
							delayTime = 0.f;
							cl.restart();
						}
					}
				}
				/*if (k == 1 && player.crawlRe() == 1) {
					printf("%d %f \n", player.crawlRe(), player.delayCrawlRe());
					enemyVector.erase(enemyVector.begin() + i);
					k = 0;
				}*/
			}
			
			if (score > 5000) {
				for (int i = 0; i < enemy2Vector.size(); i++) {
					if (enemy2Vector[i].GetCollider().CheckCollisionM(playerCollision, 1.0f)) {
						myHP -= 500;
						HP.setSize(sf::Vector2f(myHP / 320.f, 25));
						//hurt.play();
						k = 1;
						delayTime += cl.restart().asSeconds();
						//printf("%f %f \n", delayTime, cl.restart().asSeconds());
						//printf("%f \n", deltaTime);
						//clock.restart();

						if (player.crawlRe() == 1) {

							if (delayTime > 1) {

								//printf("%d %f \n", player.crawlRe(), player.delayCrawlRe());
								//printf("%f %f \n", delayTime, cl.restart().asSeconds());				
								enemy2Vector.erase(enemy2Vector.begin() + i);

								score += 2500;
								delayTime = 0.f;
								cl.restart();
							}
						}
					}
				}
			}

			/*	for (int i = 0; i < enemyVector.size(); i++) {


				}*/

			for (int i = 0; i < itemVector.size(); i++) {
				if (itemVector[i].GetCollider().CheckCollisions(playerCollision)) {
					hpup.play();
					myHP += 20000;
					HP.setFillColor(sf::Color::Magenta);
					HP.setSize(sf::Vector2f(myHP / 320.f, 25.f));
					itemVector.erase(itemVector.begin() + i); // after collided a item, it will disappear ?
					score += 1300;
				}
			}
			
			/*for (int i = 0; i < platforms2.size(); i++) {
				if (platforms2[i].GetCollider().CheckCollisions(playerCollision)) {
					player.OnCollision(direction); // after collided a item, it will disappear ?
				}
			}*/



			for (Platform2& platVector : platforms2)
				if (platVector.GetCollider().CheckCollision(playerCollision, direction, 1.0f))
					player.OnCollision(direction);

			for (int i = 0; i < item2Vector.size(); i++) {
				if (item2Vector[i].GetCollider().CheckCollisions(playerCollision)) {
					skull.play();
					myHP -= 15000;
					HP.setFillColor(sf::Color::Magenta);
					HP.setSize(sf::Vector2f(myHP / 320.f, 25.f));
					item2Vector.erase(item2Vector.begin() + i); // after collided a item, it will disappear ?
				}
			}

			// NPC STORY DRAW
			if (PositionPlayerX >= 9650 - npcc1 && PositionPlayerX <= 9900 - npcc1) {
				if (talk1 == 0) {
					msgToTalk.setPosition(sf::Vector2f(9650.f - npcc1, 100.0f));
					window.draw(msgToTalk);
				}
				if (talk1 == 1) {
					printf("%d\n", npc1);
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
					rareItem1.setPosition(sf::Vector2f(view.getCenter().x - 540.f, -360.f));
					if (npc1 == 0) {
						window.draw(msgBoxPlayer);
						window.draw(msgBoxNPC1);
						window.draw(talk01_1);
						window.draw(talk01_2);
					}
					if (npc1 == 1) {
						window.draw(msgBoxPlayer);
						window.draw(msgBoxNPC1);
						window.draw(talk01_3);
						window.draw(talk01_4);
					}
					if (npc1 == 2) {
						window.draw(msgBoxPlayer);
						window.draw(msgBoxNPC1);
						window.draw(talk01_5);
						window.draw(talk01_6);
					}
					if (npc1 == 3) {
						window.draw(msgBoxPlayer);
						window.draw(msgBoxNPC1);
						window.draw(talk01_7);
						window.draw(talk01_8);
					}
					if (npc1 == 4) {
						window.draw(rareItem1);
					}
				}
			}
			if (npc1 == 5) {
				window.draw(quest1);
			}


			// NPC2 STORY
			if (PositionPlayerX >= 9650 && PositionPlayerX <= 9900) {
				if (talk2 == 0) {
					msgToTalk.setPosition(sf::Vector2f(9650.f, 0.0f));
					window.draw(msgToTalk);
				}
				if (talk2 == 1) {
					printf("%d\n", npc2);
					msgBoxPlayer.setPosition(sf::Vector2f(msgPX, msgPY));
					msgBoxNPC2.setPosition(sf::Vector2f(msgNX, msgNY));
					talk02_1.setPosition(sf::Vector2f(msgPX + 125.f, msgPY + 45.f));
					talk02_2.setPosition(sf::Vector2f(msgNX + 45.f, msgNY + 45.f));
					talk02_3.setPosition(sf::Vector2f(msgPX + 125.f, msgPY + 45.f));
					talk02_4.setPosition(sf::Vector2f(msgNX + 45.f, msgNY + 45.f));
					talk02_5.setPosition(sf::Vector2f(msgPX + 125.f, msgPY + 45.f));
					talk02_6.setPosition(sf::Vector2f(msgNX + 45.f, msgNY + 45.f));
					talk02_7.setPosition(sf::Vector2f(msgPX + 125.f, msgPY + 45.f));
					talk02_8.setPosition(sf::Vector2f(msgNX + 45.f, msgNY + 45.f));
					rareItem2.setPosition(sf::Vector2f(view.getCenter().x - 540.f, -360.f));
					if (npc2 == 0) {
						window.draw(msgBoxPlayer);
						window.draw(msgBoxNPC2);
						window.draw(talk02_1);
						window.draw(talk02_2);
					}
					if (npc2 == 1) {
						window.draw(msgBoxPlayer);
						window.draw(msgBoxNPC2);
						window.draw(talk02_3);
						window.draw(talk02_4);
					}
					if (npc2 == 2) {
						window.draw(msgBoxPlayer);
						window.draw(msgBoxNPC2);
						window.draw(talk02_5);
						window.draw(talk02_6);
					}
					if (npc2 == 3) {
						window.draw(msgBoxPlayer);
						window.draw(msgBoxNPC2);
						window.draw(talk02_7);
						window.draw(talk02_8);
					}
					if (npc2 == 4) {
						window.draw(rareItem2);
					}
				}
			}
			if (npc2 == 5) {
				window.draw(quest2);
			}
			

			// NPC3 STORY
			if (PositionPlayerX >= 9650 + npcc3 && PositionPlayerX <= 9900 + npcc3) {
				if (talk3 == 0) {
					msgToTalk.setPosition(sf::Vector2f(9650.f + npcc3, 0.0f));
					window.draw(msgToTalk);
				}
				if (talk3 == 1) {
					//printf("%d\n", npc3);
					msgBoxPlayer.setPosition(sf::Vector2f(msgPX, msgPY));
					msgBoxNPC3.setPosition(sf::Vector2f(msgNX, msgNY));
					talk03_1.setPosition(sf::Vector2f(msgPX + 125.f, msgPY + 45.f));
					talk03_2.setPosition(sf::Vector2f(msgNX + 45.f, msgNY + 45.f));
					talk03_3.setPosition(sf::Vector2f(msgPX + 125.f, msgPY + 45.f));
					talk03_4.setPosition(sf::Vector2f(msgNX + 45.f, msgNY + 45.f));
					talk03_5.setPosition(sf::Vector2f(msgPX + 125.f, msgPY + 45.f));
					talk03_6.setPosition(sf::Vector2f(msgNX + 45.f, msgNY + 45.f));
					talk03_7.setPosition(sf::Vector2f(msgPX + 125.f, msgPY + 45.f));
					talk03_8.setPosition(sf::Vector2f(msgNX + 45.f, msgNY + 45.f));
					rareItem3.setPosition(sf::Vector2f(view.getCenter().x - 540.f, -360.f));
					if (npc3 == 0) {
						window.draw(msgBoxPlayer);
						window.draw(msgBoxNPC3);
						window.draw(talk03_1);
						window.draw(talk03_2);
					}
					if (npc3 == 1) {
						window.draw(msgBoxPlayer);
						window.draw(msgBoxNPC3);
						window.draw(talk03_3);
						window.draw(talk03_4);
					}
					if (npc3 == 2) {
						window.draw(msgBoxPlayer);
						window.draw(msgBoxNPC3);
						window.draw(talk03_5);
						window.draw(talk03_6);
					}
					if (npc3 == 3) {
						window.draw(msgBoxPlayer);
						window.draw(msgBoxNPC3);
						window.draw(talk03_7);
						window.draw(talk03_8);
					}
					if (npc3 == 4) {
						window.draw(rareItem3);
					}
				}
			}
			if (npc3 == 5) {
				window.draw(quest3);
			}

			// msg to wrap
			if (PositionPlayerX >= 10100 && PositionPlayerX <= 10400)
			{
				if (warp1 == 0)
				{
					msgToWarp.setPosition(sf::Vector2f(10100.f, -20.0f));
					window.draw(msgToWarp);
				}
			}
			if (PositionPlayerX >= 21000 && PositionPlayerX <= 21300) 
			{
				if (warp2 == 0)
				{
					msgToWarp.setPosition(sf::Vector2f(21000.f, -20.0f));
					window.draw(msgToWarp); 
				}
			}


			if (myHP < 0.0f) {
				myHP = 0;
				endOVER = true;
				
			}
			if (myHP > 78000.0f) {
				myHP = 78000.0f;
				HP.setFillColor(sf::Color::Magenta);
				HP.setSize(sf::Vector2f(myHP / 320.f, 25.f));
			}
			if (endOVER == true) {
				
				gameover.setPosition(sf::Vector2f(view.getCenter().x - 540 , -360)); //////////////////////////////////////////////////edit center
				window.draw(gameover);
				//soundover.play();

				// SHOW SCORE 
				scoreText.setCharacterSize(30);
				score_1.str(" ");
				score_1 << "SCORE \n " << score;
				namee = userName;
				//name_1 <<" :" << namee;
				
				scoreText.setString(score_1.str());
				scoreText.setPosition(sf::Vector2f(view.getCenter().x - 20.0f, -0.0f)); ///////// edit here
				window.draw(scoreText);
				
				nameText.setString(name_1.str());
				nameText.setPosition(sf::Vector2f(view.getCenter().x -540.0f, -120.0f)); ///////// edit here
				window.draw(nameText);

				if (/*sf::Mouse::getPosition(window).x >= 525 &&
					sf::Mouse::getPosition(window).y >= 475 &&
					sf::Mouse::getPosition(window).x <= 845 &&
					sf::Mouse::getPosition(window).y <= 565)*/ 1 == 1)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Home)/*sf::Mouse::isButtonPressed(sf::Mouse::Left)*/) {
						click.play();
						std::vector<std::pair<int, std::string> > scoreText;
						std::string temp, tempString;
						int tempInt = 0, X = 1;
						while (window.pollEvent(event))
						{
							if (event.type == sf::Event::Closed)
								window.close();
							fileWriter.open("text/highScore.txt", std::ios::out | std::ios::app);
							fileWriter << "\n" << userName << "," << score;
							fileWriter.close();
							playerInput.clear();
						}
						adminFile.close();
						playGAME = false;
						//part1Sound.stop();
						RANK = false;
						endOVER = false;
						endGAME = false;
						MENU = true; //
					}
				}
			}
			if (endGAME == true /*|| warp2 == 1*/) {
				gameend.setPosition(sf::Vector2f(view.getCenter().x - 540, -400));
				//gameend.setPosition(sf::Vector2f(PositionPlayerX - 540, 0));
				window.draw(gameend);
				end.play();

				// SHOW SCORE 
				scoreText.setCharacterSize(30);
				score_1.str(" ");
				score_1 << "SCORE  \n" << score;
				namee = userName;
				//name_1 <<" :" << namee;

				scoreText.setString(score_1.str());
				scoreText.setPosition(sf::Vector2f(view.getCenter().x - 20.0f, -0.0f)); ///////// edit here
				window.draw(scoreText);

				nameText.setString(name_1.str());
				nameText.setPosition(sf::Vector2f(view.getCenter().x - 540.0f, -120.0f)); ///////// edit here
				window.draw(nameText);

				if (/*sf::Mouse::getPosition(window).x >= 525 &&
					sf::Mouse::getPosition(window).y >= 475 &&
					sf::Mouse::getPosition(window).x <= 845 &&
					sf::Mouse::getPosition(window).y <= 565*/ 1 == 1)
				{
					if (/*sf::Mouse::isButtonPressed(sf::Mouse::Left)*/ sf::Keyboard::isKeyPressed(sf::Keyboard::Home)) {
						click.play();

						std::vector<std::pair<int, std::string> > scoreText;
						std::string temp, tempString;
						int tempInt = 0, X = 1;
						while (window.pollEvent(event))
						{
							if (event.type == sf::Event::Closed)
								window.close();
							fileWriter.open("text/highScore.txt", std::ios::out | std::ios::app);
							fileWriter << "\n" << userName << "," << score;
							fileWriter.close();
							playerInput.clear();
						}
						adminFile.close();
						playGAME = false;
						//part1Sound.stop();
						RANK = false;
						endOVER = false;
						endGAME = false;
						MENU = true; //
					}
				}
			}

			// edit here
			menu01.setPosition(view.getCenter().x - 540, -360);
			menux01.setPosition(view.getCenter().x - 540, -360);
			menu01_0.setPosition(view.getCenter().x - 540, -360);
			menu01_1.setPosition(view.getCenter().x - 540, -360);
			menu01_2.setPosition(view.getCenter().x - 540, -360);
			menu01_3.setPosition(view.getCenter().x - 540, -360);
			menu01_4.setPosition(view.getCenter().x - 540, -360);
			menu01_5.setPosition(view.getCenter().x - 540, -360);
			h2play.setPosition(view.getCenter().x - 540, -360);
			addName.setPosition(view.getCenter().x - 540, -360);
			gameover.setPosition(view.getCenter().x - 540, -360);
			gameend.setPosition(view.getCenter().x - 540, -360);
			rank.setPosition(view.getCenter().x - 540, -360);
			quest0.setPosition(view.getCenter().x - 540, -360);
			//enterName.setPosition(view.getCenter().x - 540, 0);
			cursor.setPosition(view.getCenter().x + 0 + text.getGlobalBounds().width - 15, 70.0f);
			last_char = event.text.unicode;
			text.setString(playerInput);
			Keyname.setPosition(view.getCenter().x - 100 , 170);//240, 500);
			text.setPosition(view.getCenter().x - 15, 150);// - 15, 535.0f);
			window.display();
		}
		pause = false;
		Loop++;
		player.SetPosition(sf::Vector2f(200, -275));

		for (int i = 0; i < enemyVector.size(); i++) {
			enemyVector.erase(enemyVector.begin() + i);
		} 
		enemyVector.clear();
		if (score > 5000) {
			for (int i = 0; i < enemy2Vector.size(); i++) {
				enemy2Vector.erase(enemy2Vector.begin() + i);
			}
		}
		enemy2Vector.clear();
		for (int i = 0; i < itemVector.size(); i++) {
			itemVector.erase(itemVector.begin() + i);
		}
		itemVector.clear();		
		
		for (int i = 0; i < item2Vector.size(); i++) {
			item2Vector.erase(item2Vector.begin() + i);
		}
		item2Vector.clear();
	}
	return 0;
}
