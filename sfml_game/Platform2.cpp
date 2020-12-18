#include "Platform2.h"
#include<iostream>

Platform2::Platform2(sf::Texture* texture, sf::Vector2f size, float x, float y, float switchTime, float moving)
{
    this->posiX = x;
    this->posiY = y;
    this->speed = speed;
    this->direction = 1;
    this->moving = moving;


    counthit = 0;
    body.setSize(size);
    body.setOrigin(body.getSize() / 2.0f);
    body.setPosition(this->posiX, this->posiY);
    body.setTexture(texture);
}
Platform2::~Platform2()
{
}
void Platform2::UpdateX(float deltaTime)
{
    float POSX = body.getPosition().x;
    velocity.y = 0;
    velocity.x = 80;
    if (POSX < this->posiX) {

        this->direction = 1;
    }
    else if (POSX > this->posiX + moving) {

        this->direction = -1;
    }
    body.move(this->direction * velocity * deltaTime);

}

void Platform2::UpdateY(float deltaTime)
{
    float POSY = body.getPosition().y;
    velocity.y = 80;
    velocity.x = 0;
    if (POSY < this->posiY) {

        this->direction = 1;
    }
    else if (POSY > this->posiY + moving) {

        this->direction = -1;
    }
    body.move(0, this->direction * velocity.y * deltaTime);

}

void Platform2::MOVE() {

    body.setPosition(-1000.0f, 350.0f);
}
void Platform2::Draw(sf::RenderWindow& window)
{
    window.draw(body);
}