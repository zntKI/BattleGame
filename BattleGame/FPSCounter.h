#pragma once

#include <SFML/Graphics.hpp>
#include "gameObject.hpp"

class FPSCounter : public GameObject
{
public:
	FPSCounter();
	~FPSCounter();
	void update( sf::Time elapsed );
};