#include <iostream>

#include "utils.hpp"

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
			// Utils.LogError(...)
		}
		isFontLoaded = true;
	}

	return defaultFont;
}

void Utils::logMessage( const std::string& message )
{
	std::cout << ConsoleTextColor::Default << message << std::endl;
}

void Utils::logError( const std::string& errorMessage )
{
	std::cerr << ConsoleTextColor::Red << errorMessage << ConsoleTextColor::Default << std::endl;
}