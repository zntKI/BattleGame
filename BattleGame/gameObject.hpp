#pragma once

#include <SFML/Graphics.hpp>

class GameObject
{
private:
	sf::Font font;

protected:
	sf::Text text;

public:
	GameObject();
	~GameObject();
	void render( sf::RenderWindow& window, sf::Vector2f pos );
};