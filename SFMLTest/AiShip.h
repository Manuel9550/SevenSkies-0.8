#pragma once
#include "ship.h"

class Ai : public ship
{
public:
	Ai (float width, float length, sf::Texture & shipTexture, int x, int y);
	void upDate(int rotation);






};