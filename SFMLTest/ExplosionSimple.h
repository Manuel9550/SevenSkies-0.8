#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>



class ExplosionSimple
{
	private:
		sf::CircleShape * redExplosion;
		sf::CircleShape * yellowExplosion;
		sf::CircleShape * orangeExplosion;
		sf::Vector2f location;
		int time;
		int size;
		sf::Clock timer;

	public:
		ExplosionSimple::ExplosionSimple(int time, int size, sf::Vector2f location);
		~ExplosionSimple();

		float getTimer();
		sf::CircleShape * getRed();
		sf::CircleShape * getOrange();
		sf::CircleShape * getYellow();
		int getTimeLimit();

		ExplosionSimple & ExplosionSimple::operator=(const ExplosionSimple & rhs);
		ExplosionSimple::ExplosionSimple(const ExplosionSimple & obj);






};