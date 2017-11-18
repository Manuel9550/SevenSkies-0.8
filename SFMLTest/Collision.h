#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
//bool collide(ship * ship1, ship * ship2);

bool collisionTest(sf::ConvexShape * shape1, sf::ConvexShape * shape2, sf::Vector2f axes1[], sf::Vector2f axes2[]);
void getAxes(sf::Vector2f axes[], int size, sf::ConvexShape * shape);
sf::Vector2f perpAxis(const sf::Vector2f & Axis);
std::pair<float, float> dotAxis(sf::ConvexShape * current_shape, const sf::Vector2f & axis);
sf::Vector2f normalizeAxis(const sf::Vector2f & Axis);
float getOverlap(std::pair<float, float> s1, std::pair<float, float> s2);


