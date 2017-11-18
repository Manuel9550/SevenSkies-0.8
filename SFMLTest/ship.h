/**
*  Name : ship.h
*  Description: the declaration for the ship class 
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h> 
#include "constants.h"
#include "projectile.h"
#include <utility>
#include <vector>
class projectile;

// definitions
#define maxSpeed 200.00
#define minSpeed 1.00
#define PI 3.14159265

#include "HelperFunctions.h"

class ship
{
protected:
	/**
	*  these are the data members of the ship that are passed through the constructor.
	*/
	
	float length; ///< length of the ship
	float width; ///< width of the ship
	sf::Texture shipTexture; ///< the texture of the ship
	int id; ///< the ID of the ship
	int numCannons; ///< the number of cannons this ship has on each side

	/**
	*  The rest of the ships data members are derived
	*/
	sf::Vector2f position;
	float speed; ///< the speed that the ship is currently going 
	float xDirection; ///< the x value of the direction the ship is currently going
	float yDirection; ///< the y value of the direction the ship is currently going
	int HP; ///< current HP of the ship
	sf::Clock rightSideCannons; ///< clock for the timer of the right side cannons
	sf::Clock leftSideCannons; ///< clock for the timer of the left side cannons
	float shipLength; ///< total length of the ship 
	sf::ConvexShape * hull; ///< shape for the hull of the ship
	int timer;
	sf::Vector2f currentVelocity; ///< the current direction that the ship is going
	
public:

	/**
	*  these are the setters for the data members
	*/

	void setHP(int newHP);
	/**
	*  these are the getters for the data members, and for objects that other methods will need
	*/
	float getSpeed();
	int getHP();
	sf::ConvexShape * getHull();
	sf::Vector2f getPosition();
	float getLength();
	sf::Vector2f getCurrentVelocity();
	sf::Clock getCannonsR();
	sf::Clock getCannonsL();
	sf::Vector2f getCannonDirection(char side, int cannonNumber);
	sf::Vector2f getCannonPoints(int side, int cannonNumber);
	

	ship(float width, float length, sf::Texture & shipTexture, int x, int y, int newId, int cannonNumber);
	~ship();
	
	bool isInRange(ship * enemy);
	void SpeedChange(int change);
	void rotate(int change);
	virtual void upDate();

	
	

	bool isColliding(ship * enemy);
	
	sf::Vector2f normalizeAxis(sf::Vector2f Axis);
	pair<float, float> dotAxis(ship * ship, sf::Vector2f axis);
	sf::Vector2f perpAxis(sf::Vector2f Axis);
	void getAxes(sf::Vector2f AxesArray[numSides]);
	float getOverlap(pair<float, float> s1, pair <float, float> s2);

	
	void CannonReset(int side);

	

	

	void updateAI(int rotation);
	ship(const ship &obj);
	ship& operator=(const ship& rhs);

	bool shipCollision(ship * enemy);
	void moveAway();

	void orientateFire(ship * enemy, vector<projectile>& currentCannonBalls);
	void compareAngle(float angle, vector<projectile>& currentCannonBalls);
	void moveTowards(ship * enemy, vector<projectile>& currentCannonBalls);

	void fireCannons(char side, vector<projectile> & currentCannonBalls);

	int getID();
};