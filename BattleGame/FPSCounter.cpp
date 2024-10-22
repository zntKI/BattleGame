#include <iostream>

#include "FPSCounter.hpp"

FPSCounter::FPSCounter( std::string identifier, std::string textStr,
	const sf::Vector2f& position, const sf::Vector2f& originFactor, const sf::Vector2f& scale,
	sf::Font& font, sf::Color color, unsigned int characterSize )
	: TextObject( identifier, textStr, position, originFactor, scale, font, color, characterSize )
{
	this->elapsed = clock.getElapsedTime();
}

FPSCounter::~FPSCounter()
{
}

void FPSCounter::update()
{
	update( elapsed );

	elapsed = clock.getElapsedTime();
	clock.restart();
}

void FPSCounter::update( sf::Time elapsed )
{
	float milliseconds = elapsed.asSeconds();
	float fps = 1.0f / ( milliseconds != 0 ? milliseconds : 0.1666f );
	text.setString( "FPS: " + std::to_string( fps ) );
}