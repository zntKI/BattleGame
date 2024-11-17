#pragma once

#include <SFML/Graphics.hpp>

enum class ConsoleTextColor {
	Default, Red
};

std::ostream& operator<<( std::ostream& os, ConsoleTextColor color );

class Utils
{
public:
	static int SCREEN_WIDTH;
	static int SCREEN_HEIGHT;

	static sf::Font& getDefaultFont();

	static void setScreenDimensions( int width, int height );
	static int getScreenWidth();
	static int getScreenHeight();

	static void logMessage( const std::string& message );
	static void logError( const std::string& errorMessage );
};