#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Collider.h"

class Platform2
{

public:
    Platform2(sf::Texture* texture, sf::Vector2f size, float x, float y, float switchTime, float moving);
    ~Platform2();
    void UpdateX(float deltaTime);
    void UpdateY(float deltaTime);
    void Draw(sf::RenderWindow& window);
    void MOVE();

    sf::Vector2f GetPosition() { return body.getPosition(); }
    Collider GetCollider() { return Collider(body); }

private:
    float posiX, posiY;

    int counthit;
    int count = 100;
    bool hit;
    float speed;
    float direction;
    float moving;
    sf::RectangleShape body;
    sf::Vector2f velocity;
};