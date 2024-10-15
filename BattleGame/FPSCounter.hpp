#pragma once

#include <SFML/Graphics.hpp>

class FPSCounter
{
private:
	sf::Font font;
	sf::Text text;

public:
	FPSCounter();
	~FPSCounter();

public:
	void update( sf::Time elapsed );
	void render( sf::RenderWindow& window );
};