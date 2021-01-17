#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Obstacle
{
public:
	Obstacle(Vector2u windowSize);
	~Obstacle();

	RectangleShape shape;

	// Getter et Setter
	int getHP();
	void setHP(int hp);
	int getHPMax();
	void setHPMax(int hpmax);

protected:

private:
	int HP;
	int HPMax;
};

