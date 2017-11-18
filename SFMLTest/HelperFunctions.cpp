/**
*  File: HelperFunctions.cpp
*  Manuel Poppe Richter
*  Description: This file contains useful functions that may be called upon by a variety of other classes 
*
*/


#include "HelperFunctions.h"

/**
*  Name : getAngle
*  Description: gets the Angle between the centres of two shapes
*  Inputs: ConvexShape * currentShape : pointer to the first shape we are trying to find the angle between
*  ConvexShape * target : pointer to the second shape we want to fid the angle between
*  Outputs : float : the angle (in degrees) tbetween the first shapes center and the second shapes center
*/
float GetAngle(sf::ConvexShape * currentShape, sf::ConvexShape * target)
{
	// get the x and y coordinates of the enemy target position 
	float xCoord = target->getPosition().x - currentShape->getPosition().x;
	float yCoord = target->getPosition().y - currentShape->getPosition().y;

	// use inverse tan to get the angle to the enemy target in relation to this shape
	float angle = atan2(xCoord, -yCoord) * 180 / PI;
	// if the angle is less than 0, then that means we gotta add that to 360
	if (angle < 0)
	{
		angle = 360 + angle;
	}
	float FinalAngle = angle;

	return FinalAngle;

}

/**
*  Name : getDistance
*  Description: returns the distance between two shapes (measure from the shapes centers)
*  Inputs :
*  ConvexShape * currentShape : pointer to the first shape we are trying to find the distance between
*  ConvexShape * target : pointer to the second shape
*/
float GetDistance(sf::ConvexShape * currentShape, sf::ConvexShape * target)
{
	// get the x and y positions of the center of the shapes
	float xCoord = target->getPosition().x - currentShape->getPosition().x;
	float yCoord = target->getPosition().y - currentShape->getPosition().y;

	// use pythagorean theorem formula to find distance
	float distance = sqrt(pow(xCoord, 2) + pow(yCoord, 2));
	return distance;
}

/**
*  Name : OrientTowards
*  Description: returns 1 if the shape should rotate to the right to orient itself toward other shape
*  returns -1 if it should rotate to the left
*  (used for the AI ships to orient their cannons toward the player)
*  Inputs :
*  ConvexShape * currentShape : pointer to the first shape we are trying to orient
*  ConvexShape * target : pointer to the second shape, the one the first will be tragetting
*/
int OrientTowards(sf::ConvexShape * currentShape, sf::ConvexShape * target)
{
	int result;
	// get the current rotation of the first shape
	float angle = GetAngle(currentShape, target);
	float currentAngle = currentShape->getRotation();

	// now we check wheter it's faster to rotate the ship to the right or left

	if (currentAngle >= angle)
	{
		if (currentAngle - angle < 180)
		{
			result = -1;
		}
		else
		{
			result = 1;
		}
	}
	else
	{
		if (angle - currentAngle < 180)
		{
			result = 1;
		}
		else
		{
			result = -1;
		}
	}
	return result;
}
