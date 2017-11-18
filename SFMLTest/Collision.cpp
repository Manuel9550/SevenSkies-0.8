/**
*  File: Collision.cpp
*  Manuel Poppe Richter
*  Description: This file contains the collision detection functions for the game,
*  as well as the supporting functions that they rely on
*
*/


#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "ship.h"
#define shipSides 7
#define cannonBallSides 4
#define turretSides 4

// to make using vectors less clunky
using namespace std;

//prototypes
bool collide(ship * ship1, ship * ship2);

bool collisionTest(sf::ConvexShape * shape1, sf::ConvexShape *shape2, sf::Vector2f axes1[], sf::Vector2f axes2[]);
void getAxes(sf::Vector2f axes[], int size, sf::ConvexShape * shape);
sf::Vector2f perpAxis(const sf::Vector2f & Axis);
pair<float, float> dotAxis(sf::ConvexShape * current_shape, const sf::Vector2f & axis);
sf::Vector2f normalizeAxis(const sf::Vector2f & Axis);
float getOverlap(std::pair<float, float> s1, std::pair<float, float> s2);
sf::Vector2f getNewAxis(sf::ConvexShape * shape, int i);


/**
*  Name: collisionTest
*  Description: This is the main collision test function. It accepts two shapes, as well as two arrays to hold their sides,
*  and determines if the two shapes are actually colliding
*  Inputs:
*  ConvexShape * shape1 : A pointer to the first shape
*  ConvexShape * shape2 : A pointer to the sexond shape
*  Vector2f Axes1[] : array to hold the first shapes sides
*  Vector2F Axes2[] : array to hold the second shapes sides
*
*  Outputs: bool : true if the shapes are colliding, false otherwise
*/


bool collisionTest(sf::ConvexShape * shape1, sf::ConvexShape *shape2, sf::Vector2f axes1[], sf::Vector2f axes2[])
{
	int size1 = shape1->getPointCount();
	int size2 = shape2->getPointCount();
	// getting the shapes sides
	getAxes(axes1, size1, shape1);
	getAxes(axes2, size2, shape2);
	
	
	

	// now that we have our axes we need to test, we have to project our shapes onto every axis
	// we will start with the first set of axis

	// these two pairs will keep our min and max for our two shapes
	pair <float, float> minMax1;
	pair <float, float> minMax2;

	// this axis will be used in order to push our shape out if they do collide
	sf::Vector2f minAxis;

	// this will be used to keep track of the minimum magnitude needed to push the ship away from the collision
	float minMagnitude = 1000;

	// now we must project  the shape onto the axes. We will start with the first axis array
	for (int i = 0; i < size1; i++)
	{
		// getting the perpindicular of the current axis
		sf::Vector2f inputAxis = axes1[i];
		sf::Vector2f currentAxis = perpAxis(inputAxis);

		//minMax1 = dotAxis(this, currentAxis);
		//minMax2 = dotAxis(enemy, currentAxis);

		minMax1 = dotAxis(shape1, normalizeAxis(currentAxis));
		minMax2 = dotAxis(shape2, normalizeAxis(currentAxis));

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

	for (int i = 0; i < size2; i++)
	{
		// getting the perpindicular of the current axis
		sf::Vector2f currentAxis = perpAxis(axes2[i]);

		//minMax1 = dotAxis(this, currentAxis);
		//minMax2 = dotAxis(enemy, currentAxis);

		minMax1 = dotAxis(shape1, normalizeAxis(currentAxis));
		minMax2 = dotAxis(shape2, normalizeAxis(currentAxis));

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
	// if we made it this far, then the two shapes are colliding. 

	sf::Vector2f moveAway(shape1->getOrigin().x - shape2->getPosition().x, shape1->getOrigin().y - shape2->getPosition().y);
	shape1->move(-minAxis.x, -minAxis.y);
	
	return true;
	// we attempt to move the first shape away from the other shape before returning true
	//sf::Vector2f moveAway(shape1->getPosition().x - shape2->getPosition().x, shape1->getPosition().y - shape2->getPosition().y);
	//shape1->move(-minAxis.x, -minAxis.y);

	
}

/**
*  Name: getAxes
*  Description: takes a shape, and fills the passed array with the shapes sides
*  Inputs:
*  Vector2f axes[] : array to hold the shapes sides
*  ConvexShape * shape : pointer to the shape we are getting the sides of
*
*  Outputs: void
*/

void getAxes(sf::Vector2f axes[], int size, sf::ConvexShape * shape)
{
	
	
	sf::Vector2f firstVector;
	sf::Vector2f secondVector;
	// to get the axis we are using to test, we subtract the ending vector from the starting vector
	for (int i = 0; i < size; i++)
	{
		// if this is the first vector, we will use the first and last point to get it to avoid overlap 
		if (i == 0)
		{
			//currentVector = shape->getPoint(sideCount - 1) - shape->getPoint(0);
			firstVector = shape->getTransform().transformPoint(shape->getPoint(size - 1));
			secondVector = shape->getTransform().transformPoint(shape->getPoint(0));
			axes[i] =  firstVector - secondVector;
			
			
		}
		else
		{
			// all other values of i can use the generic formula
			//currentVector = shape->getPoint(i - 1) - shape->getPoint(i);
			firstVector = shape->getTransform().transformPoint(shape->getPoint(i - 1));
			secondVector = shape->getTransform().transformPoint(shape->getPoint(i));
			axes[i] = firstVector - secondVector;
			
			
		}
		
	}
	
}

/**
*  Name: perpAxis
*  Description: returns a perpendicular axis to the one that was passed into it
*  Inputs:
*  const Vector2f & axis : the axis we are going to find the perpendicular of
*
*  Outputs: Vector2f : the axis that is perpendicular to the one that was entered
*/
sf::Vector2f perpAxis(const sf::Vector2f & Axis)
{
	// to get the perpendicular axis we are using, we have to switch the x and y values around, and negate the new x value
	sf::Vector2f newAxis;
	newAxis.x = Axis.y * -1;
	newAxis.y = Axis.x;
	return newAxis;
}

/**
*  Name:  dotAxis
*  Description: takes an axis, and applies the dot product to every one of the inputted shapes points, as
*  to find the min and max projection of the shape on that axis
*  Inputs:
*  ConvexShape * current_shape : pointer to the shape we are going to find the projection of
*  Vector2f : The axis that we want to find the projection of the ship on
*  outputs : pair <float, float> : a pair, the min and max projection of th ship on that axis
*
*/
pair<float, float> dotAxis(sf::ConvexShape * current_shape, const sf::Vector2f & axis)
{
	pair<float, float> minMax;

	// setting up the first min max
	float min, max;
	sf::Vector2f current_point = current_shape->getTransform().transformPoint(current_shape->getPoint(0));
	min = current_point.x * axis.x + current_point.y * axis.y;

	max = min;

	// now that we have the first min max set up, we can dot product the rest of the vertices
	for (int i = 1; i < current_shape->getPointCount(); i++)
	{
		// getting the new point to use dot product on
		current_point = current_shape->getTransform().transformPoint(current_shape->getPoint(i));
		// getting the value of the dot product 
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

/**
*  Name:  normalizeAxis
*  Description: Normalizes the axis inputted and returns the result
*  Inputs: sf::Vector2f : the axis that is to be normalized
*  outputs : Vector2f : the normalized axis of the inputted axis
*
*/
sf::Vector2f normalizeAxis(const sf::Vector2f & Axis)
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
*  Name:  getOverlap
*  Description: gets the the min and max pairs, and returns the total overlapt of the two
*  Inputs: 
*  pair<float, float> s1 : the first min and max pair
*  pair<float, float> s2 : the second min and max pair
*  outputs : float : the total overlap between the two min and max pairs
*
*/
float getOverlap(pair<float, float> s1, pair<float, float> s2)
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

/**
*  Name:  getNewAxis
*  Description: returns a new test axis for the collision, by finding the axis between two points of the shape
*  Inputs : ConvexShape * shape : pointer to the shape we will be getting a nex axis from
*  int i : the side of the shape we which to get the axis from
*  outputs : Vector2f : a new axis to project the shapes sides onto
*/
sf::Vector2f getNewAxis(sf::ConvexShape * shape, int i)
{
	
	sf::Vector2f currentVector;
	sf::Vector2f firstVector;
	sf::Vector2f secondVector;
	int sideCount = shape->getPointCount();
	// to get the axis we are using to test, we subtract the ending vector from the starting vector
	
	// if this is the first vector, we will use the first and last point to get it to avoid overlap 
	if (i == 0)
	{
		
		firstVector = shape->getTransform().transformPoint(shape->getPoint(sideCount - 1));
		secondVector = shape->getTransform().transformPoint(shape->getPoint(0));
		currentVector = firstVector - secondVector;
		
	}
	else
	{
		// all other values of i can use the generic formula
		//currentVector = shape->getPoint(i - 1) - shape->getPoint(i);
		firstVector = shape->getTransform().transformPoint(shape->getPoint(i - 1));
		secondVector = shape->getTransform().transformPoint(shape->getPoint(i));
		currentVector = firstVector - secondVector;
	}
	
	// now the vector of sf::vector2f passed in contains all the axes of the current shape passed in
	return currentVector;
}