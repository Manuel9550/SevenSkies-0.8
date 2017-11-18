/**
*  Name : projectile.cpp
*  Manuel Poppe Richter
*  Description: Contains all the methods for the projectile class
*/

#include "projectile.h"
#include <stdlib.h>
#include <math.h>


/**
*  Name : projectile (constructor)
*  Description: constructor for the projectile class
*  Inputs :
*  Vector2f direction : the direction that the projectil will be moving in
*  Vector2f startPoint : the starting location of the projectile
*  float range : the range of the projectile (how long it can travel before it expires and deletes)
*  float speed : the speed of the projectile
*  int id : The id of the projectile (ships sharing the same ID won't get hit by the projectile)
*
*/
projectile::projectile(sf::Vector2f direction, sf::Vector2f startPoint, float range, float speed, int id) : direction(direction), start(startPoint), range(range), speed(speed), id(id)
{
	/*
	cannonBall = new sf::CircleShape(5);
	cannonHitBox = new sf::ConvexShape();
	cannonHitBox->setPointCount(4);
	cannonHitBox->setPosition(startPoint);
	cannonHitBox->setOrigin(startPoint);
	cannonHitBox->setPoint(0, sf::Vector2f(startPoint.x - 2, startPoint.y - 2));
	cannonHitBox->setPoint(1, sf::Vector2f(startPoint.x + 2, startPoint.y - 2));
	cannonHitBox->setPoint(2, sf::Vector2f(startPoint.x + 2, startPoint.y + 2));
	cannonHitBox->setPoint(3, sf::Vector2f(startPoint.x - 2, startPoint.y + 2));
	cannonBall->setOrigin(cannonBall->getRadius(), cannonBall->getRadius());
	cannonBall->setPosition(startPoint);
	cannonBall->setFillColor(sf::Color::Black);
	*/

	sf::CircleShape * newCannonBall = new sf::CircleShape(5);
	newCannonBall->setOrigin(2.5, 2.5);
	newCannonBall->setPosition(startPoint);
	newCannonBall->setFillColor(sf::Color::Black);
	cannonBall = newCannonBall;

	sf::ConvexShape * newCannonHitBox = new sf::ConvexShape();
	newCannonHitBox->setPointCount(4);
	newCannonHitBox->setPosition(startPoint);
	newCannonHitBox->setOrigin(startPoint.x - 2, startPoint.y - 2);
	newCannonHitBox->setPoint(0, sf::Vector2f(startPoint.x - 4, startPoint.y - 4));
	newCannonHitBox->setPoint(1, sf::Vector2f(startPoint.x + 4, startPoint.y - 4));
	newCannonHitBox->setPoint(2, sf::Vector2f(startPoint.x + 4, startPoint.y + 4));
	newCannonHitBox->setPoint(3, sf::Vector2f(startPoint.x - 4, startPoint.y + 4));

	cannonHitBox = newCannonHitBox;
	done = false;
}

/**
*  Name : ~projectile
*  Description: destructor for the projectile
*/
projectile::~projectile()
{
	delete cannonBall;
	delete cannonHitBox;
}

/**
*  Name : update
*  Description: updates the projectile, moving it in the direction it's headed towards in the game world
*  Inputs : none
*  output : void
*/
void projectile::update()
{
	cannonBall->move(direction * speed);
	cannonHitBox->move(direction * speed);
	
}

/**
*  Name : passedRange
*  Description: checks whether the porjectile has passed it's current range, and must be deleted
*  Inputs : none
*  outputs: bool : true if the projctile has passed its range and should be deleted, false otherwise
*/
bool projectile::passedRange()
{
	bool result = true;
	// get the line between the cannonballs current position and the cannonbals starting position
	float xValue = abs(cannonBall->getPosition().x - start.x);
	float yValue = abs(cannonBall->getPosition().y - start.y);

	float currentDistance = sqrt(pow(xValue,2) + pow(yValue,2));

	// check if the ditance has surpassed it's range
	if (currentDistance >= range)
	{
		result = true;
	}
	else
	{
		result = false;
	}

	return result;
}

sf::CircleShape * projectile::getCannonBall()
{
	return cannonBall;
}

sf::ConvexShape * projectile::getCannonHitBox()
{
	return cannonHitBox;
}


/**
*  Name : inRange
*  Description: checks if the cannonball is "in range" of the passed ship
*  "in range" means that the cannonball is close enough to the ship to warrant a collision test
*  Inputs:
*  ship * test : pointer to the ship that we are testing for in range
*  output: bool : true if the ship is "in range" of th cannonball, false otherwise
*/
bool projectile::inRange(ship * test)
{
	bool result = false;
	// get the distance between the cannonball and the ship
	// if its within range of the ships length /2, plus the cannonballs radius, it is "within range"
	if (sqrt(pow((test->getHull()->getPosition().x + cannonBall->getPosition().x), 2) + pow((test->getHull()->getPosition().y + cannonBall->getPosition().y), 2)) <= (test->getLength() / 2 + cannonBall->getRadius()))
	{
		result = true;
	}
	else
	{
		result = false;
	}
	return result;
}

/**
*  Name :collisionShipTest
*  Description: checks if the projectile has collided with the inputted ship
*  Inputs : ship * test : pointer to the ship to be tested for collision
*  Outputs: bool : true if the projectile and ship have collided, false otherwise
*/
bool projectile::collisionShipTest(ship * test)
{
	sf::Vector2f axesArray1[sidesSquare];
	sf::Vector2f axesArray2[numSides];

	return collisionTest(getCannonHitBox(), test->getHull(), axesArray1, axesArray2);
}

// outdated, use above method
bool projectile::collision(ship * test)
{
	bool result = false;

	/*
	// finding the closest point
	// we start off with an arbitrarily large distance
	float distance = 100000;
	int point = 0;
	for (int i = 0; i < numSides; i++)
	{
		float newDistance = sqrt(pow((test->getHull()->getTransform().transformPoint(test->getHull()->getPoint(i)).x + cannonBall->getPosition().x), 2) + pow((test->getHull()->getTransform().transformPoint(test->getHull()->getPoint(i)).y + cannonBall->getPosition().y), 2)) <= (test->getLength() / 2 + cannonBall->getRadius());
		if (newDistance < distance)
		{
			distance = newDistance;
			point = i;
		}
	}
	*/

	for (int i = 0; i < numSides; i++)
	{

		//now we have the point that is closest, so lets use that for the axis 
		sf::Vector2f axis = (test->getHull()->getTransform().transformPoint(test->getHull()->getPoint(i)) - cannonBall->getPosition());
		

		// normalizing the axis

		float v = sqrt(pow(axis.x, 2) + pow(axis.y, 2));

		// divide both the x and y values by the v values

		axis.x = axis.x / v;
		axis.y = axis.y / v;

		// get the location of the cannonballs' projection onto the axis
		float cannonballProjection = (cannonBall->getPosition().x * axis.x) + (cannonBall->getPosition().y * axis.y);

		// this will store the min max values of the ships projection onto the axis
		pair<float, float> minMax = test->dotAxis(test, axis);

		// now we test and see if the balls projection hit the ships projection
		if (cannonballProjection - 5 > minMax.second || cannonballProjection + 5 > minMax.first)
		{
			// the ball has hit the ship
			result = true;
		}
	}
	// return the result if the ball hasn't hit the ship
	return result;
	
}

void projectile::setDone(bool newDone)
{
	done = newDone;
}

bool projectile::getDone()
{
	return done;
}

int projectile::getID()
{
	return id;
}


projectile & projectile::operator=(const projectile & rhs)
{
	// creates a temporary copy of the right hand side, then swaps the data members with the temporary 
	projectile tmp(rhs);

	// Now, swap the data members with the temporary:
	std::swap(cannonBall, tmp.cannonBall);
	std::swap(cannonHitBox, tmp.cannonHitBox);
	std::swap(speed, tmp.speed);
	std::swap(start, tmp.start);
	std::swap(done, tmp.done);
	std::swap(direction, tmp.direction);
	std::swap(range, tmp.range);
	std::swap(id, tmp.id);
	
	return *this;

}

projectile::projectile(const projectile & obj)
{
	// making the new cannonball and cannonballhitbox for the projectile to be copied
	cannonBall = new sf::CircleShape;
	*cannonBall = *obj.cannonBall;
	cannonHitBox = new sf::ConvexShape;
	*cannonHitBox = *obj.cannonHitBox;

	// now copying the rest of the non-pointer members
	done = obj.done;
	direction = obj.direction;
	start = obj.start;
	range = obj.range;
	speed = obj.speed;
	id = obj.id;


}
