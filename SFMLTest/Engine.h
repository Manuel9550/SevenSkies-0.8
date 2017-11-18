
#pragma once
#include "ship.h"
#include "ExplosionSimple.h"

class engine
{
	protected:
		vector<ship> currentShips;
		vector<ExplosionSimple> currentExplosions;
		vector<projectile> currentProjectiles;

		sf::RenderWindow GameWindow;
		sf::Texture * shipTexture;

		ship * player;

		sf::View * view;
		sf::View * HUD;

	public:
		engine(ship * player, sf::Texture * shipTexture, sf::View * view, sf::View * HUD);

		void addShip(ship & newShip);
		void addExplosion(ExplosionSimple & newExplosion);
		void addProjectile(projectile & newProjectile);

		vector<ship> getCurrentShips();
		vector<ExplosionSimple> getCurrentExplosions();
		vector<projectile> getCurrentProjectiles();

		
		sf::View * getView();
		sf::View * getHUD();
		ship * getPlayer();

		void GameLoop();
		void getEvent();
		void update();
		void draw();
		void drawHUD(sf::RenderWindow * display, float time1, float time2, int HP);

		void setProjectile(projectile & newProjectile, int placement);



};