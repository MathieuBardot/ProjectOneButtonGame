#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;

class Player
{
public:
	Player(Vector2u windowSize);
	~Player();

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

