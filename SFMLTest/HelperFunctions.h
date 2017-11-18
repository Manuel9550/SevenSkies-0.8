#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
#define PI 3.14159265


float GetAngle(sf::ConvexShape * currentShape, sf::ConvexShape * target);
float GetDistance(sf::ConvexShape * currentShape, sf::ConvexShape * target);
int OrientTowards(sf::ConvexShape * currentShape, sf::ConvexShape * target);