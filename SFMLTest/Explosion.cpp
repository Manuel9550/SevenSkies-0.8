/**
*  File: Explosion.cpp
*  Manuel Poppe Richter
*  Description: This file contains all the methods for the ExplosionCLass
*
*/



#include "Explosion.h"

explosion::explosion(int time, int size, sf::Vector2f location) : time(time), size(size), location(location)
{
	//timer.restart(); // set the timer to 0
	//NewCircle.restart(); // sets the circle timer to 0
	sf::CircleShape first(size);
	first.setFillColor(sf::Color::Red);
	Explosions.push_back(first);
}

explosion::~explosion()
{

}

void explosion::update()
{
	float newCircle = getCircleTime();
	if (newCircle > 20)
	{
		sf::CircleShape newExplosion(getSize());

		int color = rand() % 3;

		if (color == 0)
		{
			newExplosion.setFillColor(sf::Color::Yellow);
		}
		else if (color == 1)
		{
			newExplosion.setFillColor(sf::Color::Red);
		}

		int xOffset = rand() % 5 - 2;
		int yOffset = rand() % 5 - 2;

		newExplosion.setOrigin(getLocation().x + xOffset, getLocation().y + yOffset);
		Explosions.push_back(newExplosion);
		NewCircle.restart();
	}

}

sf::Vector2f explosion::getLocation()
{
	return location;
}

float explosion::getTime()
{
	return timer.getElapsedTime().asMilliseconds();
}

float explosion::getCircleTime()
{
	return NewCircle.getElapsedTime().asMilliseconds();
}

std::vector<sf::CircleShape> explosion::getExplosions()
{
	return Explosions;
}

int explosion::getSize()
{
	return size;
}

int explosion::getTimeLimit()
{
	return time;
}
