#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>

class explosion
{
	protected:
		int time; // the time (in milliseconds) the explosion will take place for
		int size; // the size of the explosion
		std::vector <sf::CircleShape> Explosions; // a vector to keep track of all the active circles in the explosions
		sf::Vector2f location;
		sf::Clock timer; // keeps track of how much time the explosion has taken place for
		sf::Clock NewCircle; // keeps track of when a new circle should be added to the explosion vector

	public:
		explosion(int time, int size, sf::Vector2f location);
		~explosion();
		void explosion::update();
		sf::Vector2f getLocation();
		float getTime();
		float getCircleTime();

		std::vector <sf::CircleShape> getExplosions();

		int getSize();
		int getTimeLimit();

};