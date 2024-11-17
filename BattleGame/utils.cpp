#include <iostream>

#include "utils.hpp"

int Utils::SCREEN_WIDTH = 0;
int Utils::SCREEN_HEIGHT = 0;

std::ostream& operator<<( std::ostream& os, ConsoleTextColor color )
{
	if ( color == ConsoleTextColor::Red ) {
		os << "\033[1;31m";
	}
	else {
		os << "\033[0m";
	}
	return os;
}

sf::Font& Utils::getDefaultFont()
{
	static sf::Font defaultFont;
	static bool isFontLoaded = false;

	if ( !isFontLoaded ) {
		if ( !defaultFont.loadFromFile( "Assets/Roboto-Regular.ttf" ) ) {
			Utils::logError( "Unable to load font from file!" );
		}
		isFontLoaded = true;
	}

	return defaultFont;
}

void Utils::setScreenDimensions( int width, int height )
{
	static bool isSet = false;
	if ( !isSet )
	{
		SCREEN_WIDTH = width;
		SCREEN_HEIGHT = height;
		isSet = true;
	}
	else
	{
		Utils::logError( "Screen dimensions have already been set!" );
	}
}

int Utils::getScreenWidth()
{
	return Utils::SCREEN_WIDTH;
}

int Utils::getScreenHeight()
{
	return Utils::SCREEN_HEIGHT;
}

void Utils::logMessage( const std::string& message )
{
	std::cout << ConsoleTextColor::Default << message << std::endl;
}

void Utils::logError( const std::string& errorMessage )
{
	std::cerr << ConsoleTextColor::Red << errorMessage << ConsoleTextColor::Default << std::endl;
}