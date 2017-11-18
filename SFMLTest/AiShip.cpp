#pragma once
#include "AiShip.h"
using namespace std;
Ai::Ai(float width, float length, sf::Texture & shipTexture, int x, int y) : ship(width, length, shipTexture, x, y, 0, 5)
{

}

void Ai::upDate(int rotation)
{
	
	rotate(rotation);
	//timer++;
	ship::upDate();
}
