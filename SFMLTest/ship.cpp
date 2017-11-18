/**
*  File: Ship.cpp
*  Manuel Poppe Richter
*  Description: This file contains all the methods for the ship class. 
*
*/


#pragma once
#include "ship.h"
#include <math.h>
#include "Collision.h"
using namespace std;

/**
*  Name: isInRange
*  Description: This method check if the current ship is "within Range" of another ship.
*  "Withing Range" does not mean the ships are colliding, but it is close enough to warrant a collision check
*  It is dependant on both the ships hull length added together, then divided by 2
*  Inputs: ship * enemy : A pointer to another ship we want to check if we are in range of
*  Outputs: boolean : true if the ship is "within range" of the other ship, fals otherwise
*/

bool ship::isInRange(ship * enemy)
{
	bool result = true;

	// check how close the two ships' centers are.
	// if the length of the hulls, added together and divided by 2 is shorter than the two ships centers, they are  "within range"
	if ( sqrt(pow((enemy->getHull()->getPosition().x - getHull()->getPosition().x), 2) + pow((enemy->getHull()->getPosition().y - getHull()->getPosition().y), 2)) 
		<= (getLength() / 2 + enemy->getLength() / 2))
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
*  Name: CannonReset
*  Description: resets the timer of the cannons for the chosen side
*  Input : int side : the side of the cannon to be reset. 0 is left side, 1 is right side
*  Output: Void
*/
void ship::CannonReset(int side)
{
	if (side == 0)
	{
		leftSideCannons.restart();
	}
	else 
	{
		rightSideCannons.restart();
	}
}

/**
*  Name: getCannonDirection
*  Description: Gets the direction (a vector) that the chosen cannon is pointing at
*  Inputs :  
*  char side : which side the cannon belongs to ('l' for left and 'r' for right)
*  int cannonNumber : which cannon on the selected side you want to get the direction for
*  Output: Vector2f : the diection that the chosen cannon is pointing
*/
sf::Vector2f ship::getCannonDirection(char side, int cannonNumber)
{
	// we return the vector that represents where the cannon is pointing

	if (side == 'l')
	{
		sf::Vector2f direction = getCannonPoints(0, cannonNumber) - getCannonPoints(1, cannonNumber);
		return direction;
		
	}
	else if (side == 'r')
	{
		sf::Vector2f direction = getCannonPoints(1, cannonNumber) - getCannonPoints(0, cannonNumber);
		return direction;
	}
	else if (side == 'o')
	{
		sf::Vector2f direction = getCannonPoints(1, cannonNumber) - getCannonPoints(0, cannonNumber);
		return direction;
	}
}

/**
*  Name: getCannonPoints
*  Description: Gets the location of the chosen cannons' position on the ship
*  Inputs:
*  int side : the side of the ship. 1 means we are choosing a cannon on the right side of the ship, else is left side
*  int cannonNumber : The number of the cannon we are choosing
*  Output: Vector2f : the location of the cannon on the ship;
*/
sf::Vector2f ship::getCannonPoints(int side, int cannonNumber)
{
	sf::Vector2f point;
	// to find the location of the cannon, we first get the length of the side of the ship
	// we do this by getting the distance between point 0 and 6 for the right side, or point 2 and 3 for the left side
	if (side == 1)
	{
		
		sf::Vector2f offset = (getHull()->getTransform().transformPoint(getHull()->getPoint(0)) - getHull()->getTransform().transformPoint(getHull()->getPoint(6)));
		// we then divide this distance by the number of cannons the ship posseses, since the cannons are evenly spaced
		
		offset.x = offset.x / getNumCannons();
		offset.y = offset.y / getNumCannons();


		// to get the final position of the chosen cannon, we multiply the offset by the chosen cannons Number. 
		point = getHull()->getTransform().transformPoint(getHull()->getPoint(2)) - sf::Vector2f(offset.x * cannonNumber, offset.y * cannonNumber);
		
	}
	else
	{
		
		sf::Vector2f offset = (getHull()->getTransform().transformPoint(getHull()->getPoint(2)) - getHull()->getTransform().transformPoint(getHull()->getPoint(3)));
		offset.x = offset.x / getNumCannons();
		offset.y = offset.y / getNumCannons();

		point = getHull()->getTransform().transformPoint(getHull()->getPoint(0)) - sf::Vector2f(offset.x * cannonNumber, offset.y * cannonNumber);
		
	}
	return point;
}

int ship::getNumCannons()
{
	return numCannons;
}

/**
*  Name: getCurrentVelocity
*  Description: Gets the current direction of the velocity of the ship
*  Inputs:None
*  Output: Vector2f : the current velocity of the ship (the direction it is travelling in)
*/
sf::Vector2f ship::getCurrentVelocity()
{
	return currentVelocity;
}

/**
*  Name: updateAI
*  Description: Helper function. Rotates the AI ship in the chosen direction, then calles the regular update function
*  Inputs: int rotation : the rotation that the AI ship will tunr this iteration
*  Output: Void
*/
void ship::updateAI(int rotation)
{
	rotate(rotation);
	timer++;
	ship::upDate();
	
}

/**
*  Name: Ship (copy constructor)
*  Description: copy constructor for the ship class. Will take in a ship object and copy the attributes to the current ship
*  Inputs: const ship & object : a ship, passed by refernece, that the attributes will be copied from
*  Output: none
*/
ship::ship(const ship & obj)
{
	// making the new hull for the ship to be copied
	hull = new sf::ConvexShape;
	*hull = *obj.hull;

	// now copying the points members (using std array)
	//std::array<sf::Vector2f, numSides> points[numSides] = obj. 

	// now copying the rest of the non-pointer members
	position = obj.position;
	speed = obj.speed;
	xDirection = obj.xDirection;
	yDirection = obj.yDirection;
	shipTexture = obj.shipTexture;
	length = obj.length;
	width = obj.width;
	timer = obj.timer;
	HP = obj.HP;
	id = obj.id;

	rightSideCannons = obj.rightSideCannons;
	leftSideCannons = obj.leftSideCannons;
	shipLength = obj.shipLength;
	currentVelocity = obj.currentVelocity;

	numCannons = obj.numCannons;
}

/**
*  Name: operator= (overloaoded rquals operator for the ship class)
*  Description: this is the = operator, overloaded to set ships classes equal to each other
*  input : const ship & rhs : the right hand side of the equals sign, the ship passed as a reference
*  Output: ship
*/
ship & ship::operator=(const ship & rhs)
{
	// creates a temporary copy of the right hand side, then swaps the data members with the temporary 
	ship tmp(rhs);

	// Now, swap the data members with the temporary:
	std::swap(hull, tmp.hull);
	std::swap(position, tmp.position);
	std::swap(speed, tmp.speed);
	std::swap(xDirection, tmp.xDirection);
	std::swap(yDirection, tmp.yDirection);
	std::swap(shipTexture, tmp.shipTexture);
	std::swap(length, tmp.length);
	std::swap(timer, tmp.timer);
	std::swap(leftSideCannons, tmp.leftSideCannons);
	std::swap(rightSideCannons, tmp.rightSideCannons);
	std::swap(shipLength, tmp.shipLength);
	std::swap(currentVelocity, tmp.currentVelocity);
	std::swap(HP, tmp.HP);
	std::swap(id, tmp.id);
	std::swap(numCannons, tmp.numCannons);
	return *this;

}




/**
*  Name: getHP
*  Description: returns the HP of the ship
*  Input : nove
*  Output: int : the HP of the current ship
*/
int ship::getHP()
{
	return HP;
}

/**
*  Name: setHP
*  Description: sets the HP of the ship to the entered amount
*  Output: Void
*/
void ship::setHP(int newHP)
{
	if (newHP <= 100)
	{
		HP = newHP;
	}
}

/**
*  Name: ship(constructor)
*  Description: constructor of the ship class
*  Inputs:
*  float width: the width of the ship
*  float height: the heigh of the ship
*  sf::Texture & shipTexture : the texture to be used for this ship
*  int x : The (starting) x position of the ship
*  int y : The (starting) y position of the ship
*  int newID : the ID of the ship (cannonballs do not hit ships with matching ID's)
*  
*/
ship::ship(float width, float length, sf::Texture & shipTexture, int x, int y, int newId, int cannonNumber) : width(width), length(length), shipTexture(shipTexture), numCannons(cannonNumber)
{
	timer = 0;
	xDirection = 0.01f;
	yDirection = 0.01f;
	speed = 1;
	HP = 100;
	id = newId;
	hull = new sf::ConvexShape();
	hull->setPointCount(7);
	hull->setPosition(x, y);
	hull->setOrigin(x, y);
	hull->setPoint(0, sf::Vector2f(x - ( width / 2), y - (length / 2) ) );
	hull->setPoint(1, sf::Vector2f(x, y -(length * 0.75)));
	hull->setPoint(2, sf::Vector2f(x + (width / 2), y  - (length / 2)));
	hull->setPoint(3, sf::Vector2f(x + (width / 2),y + (length / 2)));
	hull->setPoint(4, sf::Vector2f(x + (width * 0.25), y + (length * 0.60)));
	hull->setPoint(5, sf::Vector2f(x - (width * 0.25), y + (length  * 0.60)));
	hull->setPoint(6, sf::Vector2f(x - (width / 2), y + (length / 2)));

	shipLength = length * 1.35;
	/*
	hull->setOrigin(width / 2, length / 2);
	hull->setPoint(0, sf::Vector2f(0,0));
	hull->setPoint(1, sf::Vector2f(width / 2, - (width / 2)));
	hull->setPoint(2, sf::Vector2f(width, 0));
	hull->setPoint(3, sf::Vector2f(width, length));
	hull->setPoint(4, sf::Vector2f(width * 0.75, length + (width / 4)));
	hull->setPoint(5, sf::Vector2f(width * 0.25, length + (width / 4)));
	hull->setPoint(6, sf::Vector2f(0, length));
	*/

	
	
	hull->setOutlineThickness(1.f);
	hull->setOutlineColor(sf::Color::Yellow);
	
	hull->setTexture(&shipTexture);
}


/**
*  Name: ~ship ()destructor
*  Description: The Destructor for the ship
*/
ship::~ship()
{
	delete hull;
}

/**
*  Name:  getSpeed
*  Description: returns the speed of the ship
*  Inputs: none
*  outputs : float : the current speed of the ship
*
*/
float ship::getSpeed()
{
	return speed;
}

/**
*  Name:  speedChange
*  Description: changes the current speed of the ship
*  Inputs: int change : a positive int means the ship increases in speed, negative is a decrease
*  outputs void
*
*/

void ship::SpeedChange(int change)
{
	speed = speed + (0.1 * change);
	if (speed > maxSpeed)
	{
		speed = maxSpeed;
	}
	if (speed < minSpeed)
	{
		speed = minSpeed;
	}
}


/**
*  Name:  rotate
*  Description: rotates the ships' hull in the chosen direction
*  Inputs: int change : the direction we wish to rotate the hull (positive int will give a rotation to the right, negative left)
*  outputs : void
*
*/
void ship::rotate(int change)
{
	float rotationAngle = 0.03f * change;
	hull->rotate(rotationAngle);
	
}

/**
*  Name:  upDate
*  Description: updates the ship, moving it along the game map in the ships current direction and speed
*  Inputs: None
*  outputs : void
*
*/
void ship::upDate()
{
	// get the current direction that the ship
	xDirection = (float) 0.01f * cos((hull->getRotation() - 90) * PI / 180);
	yDirection = (float) 0.01f * sin((hull->getRotation() - 90) * PI / 180);
	// move the ship in the current direction it is facing, at the speed it is currently going
	currentVelocity = sf::Vector2f(xDirection * speed,yDirection* speed);
	
	hull->move(currentVelocity);

	
	
}

/**
*  Name:  getHull
*  Description: returns a pointer to the hull of the ship
*  Inputs: int change : the direction we wish to rotate the hull (positive int will give a rotation to the right, negative left)
*  outputs : void
*
*/
sf::ConvexShape * ship::getHull()
{
	return hull;
}


/**
*  Name:  getPosition
*  Description: gets the current position of the ship
*  Inputs: void
*  outputs : Vector2f : The current position of the ship on the map
*
*/
sf::Vector2f ship::getPosition()
{
	return position;
}

/**
*  Name:  getLength
*  Description: gets the shipLength
*  Inputs: void
*  outputs : float : The length of the ship
*
*/
float ship::getLength()
{
	return shipLength;
}

/**
*  Name:  isColliding
*  Description: Checks and sees if the current ship and inputted ship are colliding
*  Inputs: ship * enemy : a pointer to an enemy ship
*  outputs :bool : true if the ships are colliding, false otherwise
*
*/
bool ship::isColliding(ship * enemy)
{
	// creating the two axes arrays that will hold our shape sides
	sf::Vector2f axes1[numSides];
	sf::Vector2f axes2[numSides];

	// getting the shape sides
	getAxes(axes1);
	getAxes(axes2);

	

	// now that we have our axis, we have to project our shapes onto every axis
	// we will start with the first set of axis

	// these two pairs will keep our min and max for our two shapes

	pair <float, float> minMax1;
	pair <float, float> minMax2;

	// this axis will be used in order to push our shape out if they do collide
	sf::Vector2f minAxis;

	// this will be used to keep track of the minimum magnitude needed to push the ship away from the collision
	float minMagnitude = 1000;

	// now we must project  the shape onto the axes. We will start with the first axis array
	for (int i = 0; i < numSides; i++)
	{
		// getting the perpindicular of the current axis
		sf::Vector2f currentAxis = perpAxis( axes1[i]);	

		//minMax1 = dotAxis(this, currentAxis);
		//minMax2 = dotAxis(enemy, currentAxis);

		minMax1 = dotAxis(this, normalizeAxis(currentAxis));
		minMax2 = dotAxis(enemy, normalizeAxis(currentAxis));

		// now, we check the min and max values for this axis and see if they overlap
		if (minMax2.first > minMax1.second || minMax1.first > minMax2.second)
		{
			// these shapes do not overlap, return a 0, 0 vector
			return false;
			//hull->setOutlineColor(sf::Color::White);
		}
		else
		{
			//check the overlap, see if it is the new smallest overlap
			float newOverlap = getOverlap(minMax1, minMax2);
			if (newOverlap < minMagnitude)
			{
				minMagnitude = newOverlap;
				minAxis = normalizeAxis(currentAxis);
			}
		}
	}

	// we do the same thing for the second array of axis

	for (int i = 0; i < numSides; i++)
	{
		// getting the perpindicular of the current axis
		sf::Vector2f currentAxis = perpAxis(axes2[i]);


		minMax1 = dotAxis(this, normalizeAxis(currentAxis));
		minMax2 = dotAxis(enemy, normalizeAxis(currentAxis));

		// now, we check the min and max values for this axis and see if they overlap
		if  (minMax2.first > minMax1.second || minMax1.first > minMax2.second)
		{
			// these shapes do not overlap, return a 0, 0 vector
			return false;
			//hull->setOutlineColor(sf::Color::White);
			
		}
		else
		{
			//check the overlap, see if it is the new smallest overlap
			float newOverlap = getOverlap(minMax1, minMax2);
			if (newOverlap < minMagnitude)
			{
				minMagnitude = newOverlap;
				minAxis = normalizeAxis(currentAxis);
			}
		}
	}
	// if we made it this far, they are colliding, so move them and return true
	sf::Vector2f moveAway (getHull()->getOrigin().x - enemy->getHull()->getPosition().x, getHull()->getOrigin().y - enemy->getHull()->getPosition().y);
	getHull()->move(- minAxis.x ,  - minAxis.y );
	SpeedChange(-3);
	

	
	return true;
	

	

}


/**
*  Name:  normalizeAxis
*  Description: Normalizes the axis inputted and returns the result
*  Inputs: sf::Vector2f : the axis that is to be normalized
*  outputs : Vector2f : the normalized axis of the inputted axis
*
*/
sf::Vector2f ship::normalizeAxis(sf::Vector2f Axis)
{
	sf::Vector2f newAxis;
	// now we normalize the axis
	// first, find the correct "v" value

	float v = sqrt(pow(Axis.x, 2) + pow(Axis.y, 2));

	// divide both the x and y values by the v values

	newAxis.x = Axis.x / v;
	newAxis.y = Axis.y / v;

	// the axis is now normalized, we can return it to be used to check for the max/min
	return newAxis;
}

/**
*  Name:  dotAxis
*  Description: takes an axis, and applies the dot product to every one of the inputted ships points, as
*  to find the min and max projection of the ship on that axis
*  Inputs:
*  ship * current_ship : pointer to the ship we are going to find the projection of
*  Vector2f : The axis that we want to find the projection of the ship on
*  outputs : pair <float, float> : a pair, the min and max projection of th ship on that axis
*
*/
pair<float, float> ship::dotAxis(ship * current_ship, sf::Vector2f axis)
{
	pair<float, float> minMax;

	// setting up the first min max
	float min, max;
	sf::Vector2f current_point = current_ship->getHull()->getTransform().transformPoint(current_ship->getHull()->getPoint(0));
	min = current_point.x * axis.x + current_point.y * axis.y;
	
	max = min;

	// now that we have the first min max set up, we can dot product the rest of the vertices
	for (int i = 1; i < numSides; i++)
	{

		current_point = current_ship->getHull()->getTransform().transformPoint(current_ship->getHull()->getPoint(i));
		float newValue = current_point.x * axis.x + current_point.y * axis.y;

		// check to see if this should be the new min or max

		if (newValue < min)
		{
			min = newValue;
		}
		else if (newValue > max)
		{
			max = newValue;
		}
	}

	// now that we have the min and max values for the projection of the shape onto this axis, we return it
	minMax.first = min;
	minMax.second = max;
	return minMax;

	
}

sf::Vector2f ship::perpAxis(sf::Vector2f Axis)
{
	// to get the new axis we are using, we have to switch the x and y values around, and negate the new x value
	sf::Vector2f newAxis;
	newAxis.x = Axis.y * -1;
	newAxis.y = Axis.x;
	return newAxis;
	
}

float ship::getOverlap(pair<float, float> s1, pair<float, float> s2)
{
	float result;
	if (s1.second > s2.first)
	{
		result = s1.second - s2.first;
	}
	else
	{
		result = s2.second - s1.first;
	}

	return result;
}

sf::Clock ship::getCannonsR()
{
	return rightSideCannons;
}

sf::Clock ship::getCannonsL()
{
	return leftSideCannons;
}



void ship::getAxes(sf::Vector2f AxesArray[numSides])
{
	for (int i = 0; i < numSides; i++)
	{

		
		if (i == 0)
		{
			// to get the axis we are using to test, we subtract the ending vector from the starting vector
			AxesArray[i] = getHull()->getTransform().transformPoint(getHull()->getPoint(6)) - getHull()->getTransform().transformPoint(getHull()->getPoint(0));
		}
		else
		{
			// all other values of i can use the more general formula
			AxesArray[i] = getHull()->getTransform().transformPoint(getHull()->getPoint(i - 1)) - getHull()->getTransform().transformPoint(getHull()->getPoint(i));
		}
		
	}

	
}


/**
*  Name:  ShipCollision
*  Description: checks whether the curent ship and the inputted ship are colliding
*  (Does so by calling a helper function)
*  Inputs: ship * enemy : pointer to the enemy ships that we are checking
*  outputs : boolean : true if the ships are colliding, false otherwise
*
*/
bool ship::shipCollision(ship * enemy)
{
	sf::Vector2f axesArray1[numSides];
	sf::Vector2f axesArray2[numSides];

	return collisionTest(getHull(), enemy->getHull(), axesArray1, axesArray2);

}

/**
*  Name:  moveAway
*  Description: moves the ship from the direction it is currently headed
*  Inputs: none
*  outputs : none
*
*/
void ship::moveAway()
{
	
	currentVelocity = sf::Vector2f(-xDirection * (speed / 4), -yDirection * (speed / 4));
	speed = speed - 0.5;
	//hull->move(xDirection * speed, yDirection * speed);
	hull->move(currentVelocity);
}

/**
*  Name:  orientateFire
*  Description: orientates the ship to a better firing position against the inputted ship. Used for AI
*  Inputs: ship * enemy : the pointer to the enemy ship this ship wants to attack
*  vector<projectile>& currentCannonBall : the list of the current projectiles that are in the game. If the AI is ready to fire, these projectiles get added to this list
*  outputs : void
*
*/
void ship::orientateFire(ship * enemy, vector<projectile>& currentCannonBalls)
{
	// get the angle of the enemy position
	float FinalAngle = GetAngle(getHull(),enemy->getHull());


	compareAngle(FinalAngle, currentCannonBalls);

}

/**
*  Name:  compareAngle
*  Description: checks to see if the ship is angled correctly to fire against the enemy ship (Used by the AI)
*  Inputs:
*  float angle: the angle between the centre of the current ship and the enemy ship
*  vector<projectile> & currentCannonBalls : the vector of all cannonballs currently in the game
*  outputs : void
*
*/
void ship::compareAngle(float angle, vector<projectile>& currentCannonBalls)
{
	// we need to find out which is closer angle, the right side or the left side
	// we will take 90 degrees as being the right side and 270 degrees as being the left side of the ship
	// (orientation wise)

	float currentLeftSide = getHull()->getRotation() + 270;
	float currentRightSide = getHull()->getRotation() + 90;

	if (currentLeftSide > 360)
	{
		currentLeftSide = currentLeftSide - 360;
	}

	if (currentRightSide > 360)
	{
		currentRightSide = currentRightSide - 360;
	}
	// we check which side is closer to the angle of the nemy ship by finding the absolute difference
	// between each side and the angle 

	float leftAngleDistance = abs(currentLeftSide - angle);
	float rightAngleDistance = abs(currentRightSide - angle);
	float smallerAngleDistance;
	char firingDirection;

	if (leftAngleDistance <= rightAngleDistance)
	{
		if (currentLeftSide - angle < 0)
		{
			rotate(1);
		}
		else
		{
			rotate(-1);
		}
		smallerAngleDistance = leftAngleDistance;
		firingDirection = 'l';

	}
	else if (leftAngleDistance > rightAngleDistance)
	{
		if (currentRightSide - angle < 0)
		{
			rotate(1);
		}
		else
		{
			rotate(-1);
		}
		smallerAngleDistance = rightAngleDistance;
		firingDirection = 'r';
	}
	// if the ship is orientated in a position where fired cannonballs would likely hit the player, then fire the cannons
	if (smallerAngleDistance <= 20)
	{
		fireCannons(firingDirection, currentCannonBalls);
	}

}

/**
*  Name:  moveTowards
*  Description: If the current ship is too far away to the inputted ship, then it will attempt to move closer to the inputted ship (Used by AI)
*  Inputs: 
*  ship * enemy : pointer to the enemy ship
*  vector<projectile> & currentCannonballs : the vector of all the cannonballs currently in the game
*  outputs : void
*
*/
void ship::moveTowards(ship * enemy, vector<projectile>& currentCannonBalls)
{
	// if the ship is far away from the enemy, speed up and try to get towards it
	if (GetDistance(getHull(), enemy->getHull()) > 500)
	{
		// point towards the ship
		rotate(OrientTowards(getHull(), enemy->getHull()));

		// see if the ship should speed up or not
		int speed;
		float aimingAngle = GetAngle(getHull(), enemy->getHull());
		float currentAngle = getHull()->getRotation();
		float lowerLimit = aimingAngle - 25;
		float upperLimit = aimingAngle + 25;
		if (upperLimit > 360)
		{
			upperLimit = 360 - upperLimit;
			if (currentAngle >= lowerLimit || currentAngle <= upperLimit)
			{
				speed = 1;
			}
			else
			{
				speed = -1;
			}
		}
		else if (lowerLimit < 0)
		{
			lowerLimit = 360 - lowerLimit;
			if (currentAngle >= lowerLimit || currentAngle <= upperLimit)
			{
				speed = 1;
			}
			else
			{
				speed = -1;
			}
		}
		else
		{
			if (currentAngle >= lowerLimit && currentAngle <= upperLimit)
			{
				speed = 1;
			}
			else
			{
				speed = -1;
			}
		}
		SpeedChange(speed);
	}
	// if the ship is close to the enemy ship, slow down and prepare to fire at it
	else
	{
		if (getSpeed() >= 10)
		{
			SpeedChange(-1);
		}
		orientateFire(enemy, currentCannonBalls);
	}
}

/**
*  Name:  fireCannons
*  Description: fires the ships cannons one one side
*  Inputs: 
*  char side : the side we are firing the cannons from
*  vector<projectile>& currentCannonBalls : the list of currentCannonballs in the game
*  outputs : void
*
*/
void ship::fireCannons(char side, vector<projectile>& currentCannonBalls)
{
	// getting the current side and converting into an int, as well as getting the chosen cannons' timer
	sf::Time cannonTimer;
	int cannonSideInt;
	if (side == 'l')
	{
		cannonTimer = getCannonsL().getElapsedTime();
		cannonSideInt = 0;
	}
	else if (side == 'o')
	{
		cannonTimer = getCannonsL().getElapsedTime();
		cannonSideInt = 0;
	}

	else
	{
		cannonTimer = getCannonsR().getElapsedTime();
		cannonSideInt = 1;
	}

	// checks if the cannons are ready to fire
	if (cannonTimer.asSeconds() > 5)
	{
		// if they are ready, reset the timer and push new cannonballs onto the list
		CannonReset(cannonSideInt);

		// push the new cannonballs onto the list 

		if (side == 'o')
		{
			projectile currentCannonball(getHull()->getTransform().transformPoint(getHull()->getPoint(1)) - getHull()->getTransform().transformPoint(getPosition()), getHull()->getTransform().transformPoint(getHull()->getPoint(1)) , 1000, 0.01, getID());
			currentCannonBalls.push_back(currentCannonball);
		}
		else
		{
			for (int i = 0; i < getNumCannons(); i++)
			{
				projectile currentCannonball(getCannonDirection(side, i) + getCurrentVelocity(), getCannonPoints(cannonSideInt, i), 1000, 0.01, getID());
				currentCannonBalls.push_back(currentCannonball);
			}
		}
	}
}


/**
*  Name:  getID
*  Description: returns the ID of the ship
*  Inputs:none
*  Outputs : int : the ID of the ship
*
*/
int ship::getID()
{
	return id;
}




