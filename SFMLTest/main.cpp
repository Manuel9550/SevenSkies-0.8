#pragma once
#include <new>
#include "projectile.h"
#include "ExplosionSimple.h"
//#include <memory>
#include <algorithm>
#include "Collision.h"
#include "Explosion.h"
#define _USE_MATH_DEFINES
#pragma warning(disable:4996)

using namespace std;

void drawHUD(sf::RenderWindow * display, float time1, float time2, int HP);

int main()
{
	int dummy = 0;

	sf::Clock clock;
	sf::Time gameRun;
	sf::RenderWindow window(sf::VideoMode(1200, 1000), "SFML works!");
	sf::Texture Texture;
	Texture.loadFromFile("textures/wood1.jpg");

	vector<ExplosionSimple> currentExplosions; 
	vector<projectile> currentProjectiles;
	//vector<shared_ptr<ship>> currentShips;
	vector<ship> currentShips;
	ship player(50, 150, Texture, 0, 0, 1, 5);
	ship enemy(75, 300, Texture, -200, 0, 2, 5);
	currentShips.push_back(enemy);
	ship enemy2(50, 100, Texture, 800, 500, 3, 5);
	currentShips.push_back(enemy2);
	

	//sf::View view(sf::Vector2f(0.0f,0.0f), sf::Vector2f(1000.0f,1000.0f));
	sf::View view;
	view.setSize(1000, 1000);
	view.setViewport(sf::FloatRect(0,0,0.8,1));

	sf::View HUD;
	//HUD.setSize(400, 1000);
	HUD.setViewport(sf::FloatRect(0.8, 0, 1, 1));
	
	while (window.isOpen())
	{
		sf::Event evnt;

		

		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::Resized:
				cout << "Window Height: " << evnt.size.height << endl;
				cout << "Window Width: " << evnt.size.width <<endl;
				break;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			player.getHull()->rotate((float)-0.03);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			player.SpeedChange(1);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			player.SpeedChange(-1);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			player.getHull()->rotate((float) 0.03);
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K))
		{
			player.fireCannons('l', currentProjectiles);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L))
		{
			player.fireCannons('r', currentProjectiles);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O))
		{
			player.fireCannons('o', currentProjectiles);
		}
		
		/*
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K))
		{
			sf::Time cannonTimer = player.getCannonsL().getElapsedTime();
			if (cannonTimer.asSeconds() > 5)
			{
				player.CannonReset(0);

				// push the new cannonballs onto the list 
				for (int i = 0; i < 5; i++)
				{
					projectile currentCannonball(player.getCannonDirection('l', i) + player.getCurrentVelocity(), player.getCannonPoints(1, i), 1000, 0.01);
					currentProjectiles.push_back(currentCannonball);
				}
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L))
		{
			sf::Time cannonTimer = player.getCannonsR().getElapsedTime();
			if (cannonTimer.asSeconds() > 5)
			{
				// reset the timer
				player.CannonReset(1);

				
				// push the new cannonballs onto the list 
				for (int i = 0; i < 5; i++)
				{
					projectile currentCannonball(player.getCannonDirection('r', i) + player.getCurrentVelocity(), player.getCannonPoints(0, i), 1000, 0.01);
					currentProjectiles.push_back(currentCannonball);
				}
			}
		}
		*/
		/*
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			player.setPosition((float)mousePos.x, (float)mousePos.y);
		}
		*/
		
		window.clear(sf::Color::Cyan);
		view.setCenter(player.getHull()->getPosition());
		/*
		if (player.isInRange(&enemy))
		{
			if (player.isColliding(&enemy))
			{
				player.getHull()->setOutlineColor(sf::Color::Red);
			}
			else
			{
				player.getHull()->setOutlineColor(sf::Color::White);
			}
		}
		*/
		dummy++;
	
		if (dummy >= 1000)
		{
		
			dummy = 0;
		}
		
		for (vector<ship>::iterator c = currentShips.begin(); c != currentShips.end(); c++)
		{
			
			c->updateAI(0);
			if (player.isInRange(&*c))
			{
				
				if (player.shipCollision(&*c))
				{
					player.getHull()->setOutlineColor(sf::Color::Red);
					player.SpeedChange(-3);
					player.setHP(player.getHP() - 1);
				}
				else
				{
					player.getHull()->setOutlineColor(sf::Color::White);

				}
			}


		}
		
		/*
		for (vector<ship>::iterator c = currentShips.begin(); c != currentShips.end(); c++)
		{

			c->updateAI(0);
			if (player.isInRange(&*c))
			{

				if (collide(& player, &*c))
				{
					player.getHull()->setOutlineColor(sf::Color::Red);
					// we attempt to move the first ship away from the other ship
					//sf::Vector2f moveAway(player.getHull()->getPosition().x - c->getHull()->getPosition().x, player.getHull()->getPosition().y - c->getHull()->getPosition().y);
					//player.getHull->move(-minAxis.x, -minAxis.y);
					player.getHull()->setOutlineColor(sf::Color::Red);
				}
				else
				{
					system("CLS");
					player.getHull()->setOutlineColor(sf::Color::White);
				}
			}
			

		}
		*/
		//updating the ships

		player.upDate();
		//enemy.upDate(1);
		//enemy2.upDate(-3);
		
		// now rotate the ships
		for (vector<ship>::iterator c = currentShips.begin(); c != currentShips.end(); c++)
		{
			c->moveTowards(&player, currentProjectiles);
		}
	


		// updating the projectiles
		
		for (vector<projectile>::iterator c = currentProjectiles.begin(); c != currentProjectiles.end();)
		{
			c->update();
			
			//check to see if the cannonball has hit any ship
			for (vector<ship>::iterator s = currentShips.begin(); s != currentShips.end(); s++)
			{
				if (c->collisionShipTest(&*s) && (c->getID() != s->getID()))
				{
					cout << "hit!\n";
					s->setHP(s->getHP() - 5);
					cout << c->getCannonBall()->getPosition().x << " " << c->getCannonBall()->getPosition().y;
					c->setDone(true);
					currentExplosions.push_back(ExplosionSimple(100, 6, c->getCannonBall()->getPosition()));

				}
			}
			
			// check to see if it hit the player
			if (c->collisionShipTest(&player) && (c->getID() != player.getID()))
			{
				cout << "hit!\n";
				player.setHP(player.getHP() - 5);
				cout << c->getCannonBall()->getPosition().x << " " << c->getCannonBall()->getPosition().y;
				c->setDone(true);
				currentExplosions.push_back(ExplosionSimple(100, 6, c->getCannonBall()->getPosition()));

			}

			// also see if the cannonball has passed it's maximum range
			if (c->passedRange() == true || c->getDone() == true)
			{
				c = currentProjectiles.erase(c);
			}
			else
			{
				++c;
			}
		}
		
		

	
		gameRun = clock.getElapsedTime();

		sf::Time leftCannon = player.getCannonsL().getElapsedTime();
		sf::Time rightCannon = player.getCannonsR().getElapsedTime();
		

		window.setView(view);
		window.draw(* player.getHull());
		//window.draw(* enemy.getHull());
		//window.draw(* enemy2.getHull());

		

		for (vector<ship>::iterator c = currentShips.begin(); c != currentShips.end();)
		{
			window.draw(* c->getHull());

			if (c->getHP() <= 0)
			{
				currentExplosions.push_back(ExplosionSimple(500, 50, sf::Vector2f(c->getHull()->getPosition().x - 15, c->getHull()->getPosition().y + 15)));
				currentExplosions.push_back(ExplosionSimple(500, 15, sf::Vector2f(c->getHull()->getPosition().x, c->getHull()->getPosition().y)));
				currentExplosions.push_back(ExplosionSimple(500, 30, sf::Vector2f(c->getHull()->getPosition().x - 50, c->getHull()->getPosition().y + 50)));
				currentExplosions.push_back(ExplosionSimple(500, 40, sf::Vector2f(c->getHull()->getPosition().x + 40, c->getHull()->getPosition().y - 50)));
				currentExplosions.push_back(ExplosionSimple(500, 25, sf::Vector2f(c->getHull()->getPosition().x - 50, c->getHull()->getPosition().y - 50)));
				currentExplosions.push_back(ExplosionSimple(500, 25, sf::Vector2f(c->getHull()->getPosition().x + 10, c->getHull()->getPosition().y + 20)));
				c = currentShips.erase(c);

			}
			else
			{
				++c;
			}
		}

		// drawing the cannonballs
		for (vector<projectile>::iterator c = currentProjectiles.begin(); c != currentProjectiles.end(); c++)
		{
			
			window.draw(*c->getCannonBall());
		}

		// drawing the explosions
		for (vector<ExplosionSimple>::iterator c = currentExplosions.begin(); c != currentExplosions.end();)
		{

			window.draw(*c->getRed());
			window.draw(*c->getYellow());
			window.draw(*c->getOrange());


			// see if the explosion is done and should be removed from the vector

			if (c->getTimer() > c->getTimeLimit())
			{
				c = currentExplosions.erase(c);
			}
			else
			{
				++c;
			}
		}
		//now we draw the hud
		window.setView(HUD);
		drawHUD(&window, leftCannon.asMilliseconds(), rightCannon.asMilliseconds(), player.getHP());
		window.display();
	}

	return 0;
}

void drawHUD(sf::RenderWindow * display, float time1, float time2, int HP)
{
	sf::Font font;

	if (!font.loadFromFile("LiberationSerif-Regular.ttf"))
	{
		cout << "File isn't there\n";
	}
	if (time1 > 5000)
	{
		time1 = 5000;
	}

	if (time2 > 5000)
	{
		time2 = 5000;
	}

	sf::Text textL;
	sf::Text textR;
	textL.setFont(font);
	textR.setFont(font);
	textL.setString("Left");
	textR.setString("Right");
	textL.setCharacterSize(20);
	textR.setCharacterSize(20);
	textL.setStyle(sf::Text::Bold);
	textR.setStyle(sf::Text::Bold);
	textL.setPosition(25, 470);
	textR.setPosition(125, 470);
	textL.setColor(sf::Color::White);
	textR.setColor(sf::Color::White);
	sf::RectangleShape backGround;
	backGround.setSize(sf::Vector2f(200, 1000));
	backGround.setFillColor(sf::Color::Color(6,6,6));

	sf::RectangleShape leftCannonTimer;
	leftCannonTimer.setSize(sf::Vector2f(50, -time1 / 10));
	leftCannonTimer.setPosition(25, 1000);

	sf::RectangleShape rightCannonTimer;
	rightCannonTimer.setSize(sf::Vector2f(50, -time2 / 10));
	rightCannonTimer.setPosition(125, 1000);

	sf::RectangleShape HPbar;
	HPbar.setPosition(0, 200);
	HPbar.setSize(sf::Vector2f(HP * 2, 30));
	
	HPbar.setFillColor(sf::Color::Green);

	display->draw(backGround);
	display->draw(rightCannonTimer);
	display->draw(leftCannonTimer);
	display->draw(HPbar);
	display->draw(textL);
	display->draw(textR);

	

}