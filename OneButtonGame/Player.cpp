#include "Player.h"

Player::Player(Vector2u windowSize)
{
	this->HPMax = 10;
	this->HP = this->HPMax;

	this->shape.setSize(Vector2f(30.f, 30.f));
	this->shape.setFillColor(Color::Blue);
	this->shape.setPosition(windowSize.x / 2, windowSize.y - shape.getGlobalBounds().width);
}

Player::~Player() {}

int Player::getHP()
{
	return HP;
}

void Player::setHP(int hp)
{
	HP = hp;
}

int Player::getHPMax()
{
	return HPMax;
}

void Player::setHPMax(int hpmax)
{
	HPMax = hpmax;
}
