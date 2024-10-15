#include <iostream>

#include "FPSCounter.h"

FPSCounter::FPSCounter() : GameObject()
{
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
