#include <iostream>

#include "FPSCounter.hpp"

FPSCounter::FPSCounter()
{
	font.loadFromFile( "Assets/Roboto-Regular.ttf" );
	text.setFont( font );
	text.setString( "FPS: " );
	text.setCharacterSize( 24 );
	text.setFillColor( sf::Color::Green );
	text.setPosition( sf::Vector2f( 10, 0 ) );
}

FPSCounter::~FPSCounter()
{
}

void FPSCounter::update( sf::Time elapsed )
{
	float milliseconds = elapsed.asSeconds();
	float fps = 1.0f / ( milliseconds != 0 ? milliseconds : 0.1666f );
	text.setString( "FPS: " + std::to_string( fps ) );
}

void FPSCounter::render( sf::RenderWindow& window )
{
	window.draw( text );
}