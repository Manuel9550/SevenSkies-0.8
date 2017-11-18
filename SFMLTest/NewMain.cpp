#pragma once
#include <new>
#include "projectile.h"
#include "ExplosionSimple.h"
//#include <memory>
#include <algorithm>
#include "Collision.h"
#include "Explosion.h"
#include "Engine.h"
#define _USE_MATH_DEFINES


using namespace std;

void drawHUD(sf::RenderWindow * display, float time1, float time2, int HP);

int main()
{
	sf::RenderWindow window(sf::VideoMode(1200, 1000), "SFML works!");
	sf::Texture Texture;
	Texture.loadFromFile("textures/wood1.jpg");
	

	ship player(50, 150, Texture, 0, 0, 1, 5);
	ship enemy(75, 300, Texture, -200, 0, 2, 5);
	ship enemy2(50, 100, Texture, 800, 500, 3, 5);

	sf::View view;
	view.setSize(1000, 1000);
	view.setViewport(sf::FloatRect(0, 0, 0.8, 1));

	sf::View HUD;
	//HUD.setSize(400, 1000);
	HUD.setViewport(sf::FloatRect(0.8, 0, 1, 1));

	engine GameEngine(&player, &Texture, &view, &HUD);
	GameEngine.addShip(enemy);
	GameEngine.addShip(enemy2);

	cout << GameEngine.getCurrentShips()[0].getHull()->getPosition().x << " " << GameEngine.getCurrentShips()[0].getHull()->getPosition().y << "\n";
	cout << GameEngine.getCurrentShips()[1].getHull()->getPosition().x << " " << GameEngine.getCurrentShips()[1].getHull()->getPosition().y;
	//GameEngine.GameLoop();

	while (window.isOpen())
	{
		// first, get the players actions
		GameEngine.getEvent();
		// then update the game objects
		GameEngine.update();
		// then draw the screen
		GameEngine.draw();
	}




	return 0;
}