#pragma once
#include <SFML/Graphics.hpp>
#include "Ship.h"
#include "Collision.h"
#define sidesSquare 4
class ship;

class projectile
{
private:
	bool done; // a boolean to see if the cannonball should be deleted
	sf::Vector2f direction;
	sf::Vector2f start;
	float range;
	float speed;
	sf::CircleShape * cannonBall;
	sf::ConvexShape * cannonHitBox;
	int id;


public:
	projectile(sf::Vector2f direction, sf::Vector2f startPoint, float range, float speed, int id);
	~projectile();

	projectile & projectile::operator=(const projectile & rhs);
	projectile::projectile(const projectile & obj);

	void update();
	bool passedRange();
	sf::CircleShape * getCannonBall();
	sf::ConvexShape * getCannonHitBox();
	bool inRange(ship * test);
	bool collisionShipTest(ship * test);
	bool collision(ship * test);
	void setDone(bool newDone);

	bool getDone();

	int getID();
};