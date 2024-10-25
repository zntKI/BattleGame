#pragma once

#include <SFML/Graphics.hpp>

#include "textObject.hpp"

class FPSCounter : public TextObject
{
private:
	sf::Clock clock;
	sf::Time elapsed;

public:
	FPSCounter( const std::string& identifier, const std::string& textStr,
		const sf::Vector2f position = sf::Vector2f( 0.f, 0.f ), const sf::Vector2f originFactor = sf::Vector2f( 0.f, 0.f ),
		sf::Font& font = Utils::getDefaultFont(), sf::Color color = sf::Color::Yellow, unsigned int characterSize = 30 );
	
	FPSCounter( const FPSCounter& ) = delete;
	FPSCounter& operator=( const FPSCounter& ) = delete;
	
	~FPSCounter();

public:
	void update() override;
	void update( sf::Time elapsed );
};