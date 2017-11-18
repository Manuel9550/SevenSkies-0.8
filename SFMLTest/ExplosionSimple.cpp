/**
*  File: Ship.cpp
*  Manuel Poppe Richter
*  Description: This file contains all the methods for the ExplosionSimple class.
*
*/


#include "ExplosionSimple.h"
#include <stdlib.h>
using namespace std;

/**
*  Name : ExplosionSimple (constructor)
*  Description: COnstructor for the Explosions SimpleClass
*  Inputs: 
*  int time : the amount of time (seconds) that the explosion is to be present on the screen for
*  int size : size of the explosion 
*  Vector2f location : the location of the explosion
*/

ExplosionSimple::ExplosionSimple(int time, int size, sf::Vector2f location) : time(time), size(size), location(location)
{
	sf::CircleShape * Explosion = new sf::CircleShape(size);
	Explosion->setOrigin(size / 2, size / 2);
	Explosion->setPosition(location.x - (size / 2), location.y - (size / 2));
	Explosion->setFillColor(sf::Color::Red);
	redExplosion = Explosion;

	yellowExplosion = new sf::CircleShape(size);
	yellowExplosion->setOrigin(size / 2, size / 2);
	yellowExplosion->setPosition(location.x + (size / 2), location.y + (size / 2));
	yellowExplosion->setFillColor(sf::Color::Yellow);

	orangeExplosion = new sf::CircleShape(size);
	orangeExplosion->setOrigin(size / 2, size / 2);
	orangeExplosion->setPosition(location.x + (size / 2), location.y - (size / 2));
	orangeExplosion->setFillColor(sf::Color(250,250,250));


}

/**
*  Name : ~ExplosionSimple
*  Description : Destructor for the explosion class
*/

ExplosionSimple::~ExplosionSimple()
{
	delete redExplosion;
	delete yellowExplosion;
	delete orangeExplosion;
}

/**
*  Name : getTimer
*  Description : returns the amount of milliseconds the explosion has elapsed for
*  input: none
*  Outputs : float : the millisecond amount the explosion has gone on for
*/
float ExplosionSimple::getTimer()
{
	return timer.getElapsedTime().asMilliseconds();
}

/**
*  Name : getRed()
*  Description : Returns the Red circle part of the explosion
*/
sf::CircleShape * ExplosionSimple::getRed()
{
	return redExplosion;
}

/**
*  Name : getOrange()
*  Description : Returns the Orange circle part of the explosion
*/
sf::CircleShape * ExplosionSimple::getOrange()
{
	return orangeExplosion;
}

/**
*  Name : getYellow()
*  Description : Returns the Yellow circle part of the explosion
*/
sf::CircleShape * ExplosionSimple::getYellow()
{
	return yellowExplosion;
}

/**
*  Name : getRed()
*  Description : Returns the Timelimit of the explosion, or how long it is supposed to last for
*/
int ExplosionSimple::getTimeLimit()
{
	return time;
}

ExplosionSimple & ExplosionSimple::operator=(const ExplosionSimple & rhs)
{
	// creates a temporary copy of the right hand side, then swaps the data members with the temporary 
	ExplosionSimple tmp(rhs);

	// now swapping data members with temporary copy
	std::swap(redExplosion, tmp.redExplosion);
	std::swap(yellowExplosion, tmp.yellowExplosion);
	std::swap(orangeExplosion, tmp.orangeExplosion);

	std::swap(time, tmp.time);
	std::swap(size, tmp.size);
	std::swap(timer,tmp.timer);
	std::swap(location, tmp.location);
	return *this;
}

ExplosionSimple::ExplosionSimple(const ExplosionSimple & obj)
{
	// making the new circle shapes so they can be copied
	orangeExplosion = new sf::CircleShape;
	*orangeExplosion = *obj.orangeExplosion;

	yellowExplosion = new sf::CircleShape;
	*yellowExplosion = *obj.yellowExplosion;

	redExplosion = new sf::CircleShape;
	*redExplosion = *obj.redExplosion;

	// now copying the rest of the ExplosionSimple data members

	time = obj.time;
	size = obj.size;
	timer = obj.timer;
	location = obj.location;



}
