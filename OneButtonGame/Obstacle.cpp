#include "Obstacle.h"

Obstacle::Obstacle(Vector2u windowSize)
{
	this->HPMax = rand() % 3 + 1;
	this->HP = this->HPMax;

	this->shape.setSize(Vector2f(70.f, 40.f));
	this->shape.setFillColor(Color::Red);
	this->shape.setPosition((float)(rand() % (int)(this->shape.getGlobalBounds().width - windowSize.x)),this->shape.getGlobalBounds().height);
}

Obstacle::~Obstacle() {}

int Obstacle::getHP()
{
	return HP;
}

void Obstacle::setHP(int hp)
{
	HP = hp;
}

int Obstacle::getHPMax()
{
	return HPMax;
}

void Obstacle::setHPMax(int hpmax)
{
	HPMax = hpmax;
}