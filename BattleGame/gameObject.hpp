#pragma once

#include <SFML/Graphics.hpp>

class GameObject
{
private:
	const std::string identifier;

public:
	GameObject( const std::string identifier );
	GameObject( const GameObject& other );
	
	virtual ~GameObject();

public:
	virtual void update() = 0;
	virtual void render( const sf::RenderWindow& window ) = 0;
	std::string getIdentifier() const;
};