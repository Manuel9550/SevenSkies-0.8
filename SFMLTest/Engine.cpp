#include "Engine.h"
#pragma warning(disable:4996)

engine::engine(ship * player, sf::Texture * shipTexture, sf::View * view, sf::View * HUD)  : player(player), GameWindow(sf::VideoMode(1200, 1000), "Seven Skies"), shipTexture(shipTexture), view(view), HUD(HUD)
{
	view->setSize(1000, 1000);
	view->setViewport(sf::FloatRect(0, 0, 0.8, 1));

	HUD->setViewport(sf::FloatRect(0.8, 0, 1, 1));
	
}

void engine::addShip(ship & newShip)
{
	currentShips.push_back(newShip);
}

void engine::addExplosion(ExplosionSimple & newExplosion)
{
	currentExplosions.push_back(newExplosion);
}

void engine::addProjectile(projectile & newProjectile)
{
	currentProjectiles.push_back(newProjectile);
}

vector<ship> engine::getCurrentShips()
{
	return currentShips;
}

vector<ExplosionSimple> engine::getCurrentExplosions()
{
	return currentExplosions;
}

vector<projectile> engine::getCurrentProjectiles()
{
	return currentProjectiles;
}

sf::View * engine::getView()
{
	return view;
}

sf::View * engine::getHUD()
{
	return HUD;
}

ship * engine::getPlayer()
{
	return player;
}

void engine::GameLoop()
{
	while (GameWindow.isOpen())
	{
		// first, get the players actions
		getEvent();
		// then update the game objects
		update();
		// then draw the screen
		draw();
	}
}

void engine::getEvent()
{
	sf::Event evnt;

	while (GameWindow.pollEvent(evnt))
	{
		switch (evnt.type)
		{
		case sf::Event::Closed:
			GameWindow.close();
			break;

		case sf::Event::Resized:
			cout << "Window Height: " << evnt.size.height << endl;
			cout << "Window Width: " << evnt.size.width << endl;
			break;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		getPlayer()->getHull()->rotate((float)-0.03);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		getPlayer()->SpeedChange(1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		getPlayer()->SpeedChange(-1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		getPlayer()->getHull()->rotate((float) 0.03);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K))
	{
		getPlayer()->fireCannons('l', currentProjectiles);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L))
	{
		getPlayer()->fireCannons('r', currentProjectiles);
	}
}

void engine::update()
{
	getPlayer()->upDate();

	// now rotate the ships
	vector<ship> shipCopy = getCurrentShips();
	vector<projectile> projectilesCopy = getCurrentProjectiles();

	for (vector<ship>::iterator c = shipCopy.begin(); c != shipCopy.end();)
	{
		c->moveTowards(getPlayer(), projectilesCopy);

		if (getPlayer()->isInRange(&*c))
		{

			if (getPlayer()->shipCollision(&*c))
			{
				getPlayer()->getHull()->setOutlineColor(sf::Color::Red);
				getPlayer()->SpeedChange(-3);
				getPlayer()->setHP(getPlayer()->getHP() - 1);
			}
			else
			{
				getPlayer()->getHull()->setOutlineColor(sf::Color::White);

			}
		}

		if (c->getHP() <= 0)
		{
			addExplosion(ExplosionSimple(500, 50, sf::Vector2f(c->getHull()->getPosition().x - 15, c->getHull()->getPosition().y + 15)));
			addExplosion(ExplosionSimple(500, 15, sf::Vector2f(c->getHull()->getPosition().x, c->getHull()->getPosition().y)));
			addExplosion(ExplosionSimple(500, 30, sf::Vector2f(c->getHull()->getPosition().x - 50, c->getHull()->getPosition().y + 50)));
			addExplosion(ExplosionSimple(500, 40, sf::Vector2f(c->getHull()->getPosition().x + 40, c->getHull()->getPosition().y - 50)));
			addExplosion(ExplosionSimple(500, 25, sf::Vector2f(c->getHull()->getPosition().x - 50, c->getHull()->getPosition().y - 50)));
			addExplosion(ExplosionSimple(500, 25, sf::Vector2f(c->getHull()->getPosition().x + 10, c->getHull()->getPosition().y + 20)));
			c = shipCopy.erase(c);

		}
		else
		{
			++c;
		}
	}
	


	// updating the projectiles

	
	for (vector<projectile>::iterator c = projectilesCopy.begin(); c != projectilesCopy.end();)
	{
		c->update();

		//check to see if the cannonball has hit any ship
		for (vector<ship>::iterator s = shipCopy.begin(); s != shipCopy.end(); s++)
		{
			if (c->collisionShipTest(&*s) && (c->getID() != s->getID()))
			{
				s->setHP(s->getHP() - 5);
				c->setDone(true);
				addExplosion(ExplosionSimple(100, 6, c->getCannonBall()->getPosition()));

			}
		}

		// check to see if it hit the player
		if (c->collisionShipTest(getPlayer()) && (c->getID() != getPlayer()->getID()))
		{
			
			getPlayer()->setHP(getPlayer()->getHP() - 5);
			
			c->setDone(true);
			addExplosion(ExplosionSimple(100, 6, c->getCannonBall()->getPosition()));

		}

		// also see if the cannonball has passed it's maximum range
		if (c->passedRange() == true || c->getDone() == true)
		{
			c = projectilesCopy.erase(c);
		}
		else
		{
			++c;
		}
	}
	currentShips = shipCopy;
	currentProjectiles = projectilesCopy;

}

void engine::draw()
{

	GameWindow.clear(sf::Color::Cyan);
	getView()->setCenter(getPlayer()->getHull()->getPosition());

	GameWindow.setView(*getView());
	GameWindow.draw(*getPlayer()->getHull());

	//drawing the ships 

	vector<ship> shipCopy = getCurrentShips();
	vector<projectile> projectileCopy = getCurrentProjectiles();
	vector<ExplosionSimple> explosionsCopy = getCurrentExplosions();

	for (vector<ship>::iterator c = shipCopy.begin(); c != shipCopy.end(); c++)
	{
		GameWindow.draw(*c->getHull());
	}

	// drawing the cannonballs

	
	for (vector<projectile>::iterator c =projectileCopy.begin(); c != projectileCopy.end(); c++)
	{

		GameWindow.draw(*c->getCannonBall());
	}

	// drawing the explosions
	
	for (vector<ExplosionSimple>::iterator c = explosionsCopy.begin(); c != explosionsCopy.end();)
	{

		GameWindow.draw(*c->getRed());
		GameWindow.draw(*c->getYellow());
		GameWindow.draw(*c->getOrange());


		// see if the explosion is done and should be removed from the vector

		if (c->getTimer() > c->getTimeLimit())
		{
			c = explosionsCopy.erase(c);
		}
		else
		{
			++c;
		}
	}

	currentExplosions = explosionsCopy;
	currentProjectiles = projectileCopy;
	currentShips = shipCopy;


	sf::Time leftCannon = getPlayer()->getCannonsL().getElapsedTime();
	sf::Time rightCannon = getPlayer()->getCannonsR().getElapsedTime();
	//now we draw the hud
	GameWindow.setView(*getHUD());
	drawHUD(&GameWindow, leftCannon.asMilliseconds(), rightCannon.asMilliseconds(), getPlayer()->getHP());
	GameWindow.display();
}

void engine::drawHUD(sf::RenderWindow * display, float time1, float time2, int HP)
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
	backGround.setFillColor(sf::Color::Color(6, 6, 6));

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

void engine::setProjectile(projectile & newProjectile, int placement)
{
	currentProjectiles[placement] = newProjectile;
}


