#pragma once

#include <SFML/Graphics.hpp>

enum class ConsoleTextColor {
	Default, Red
};

std::ostream& operator<<( std::ostream& os, ConsoleTextColor color );

class Utils
{
public:
	static sf::Font& getDefaultFont();

	static void logMessage( const std::string& message );
	static void logError( const std::string& errorMessage );
};