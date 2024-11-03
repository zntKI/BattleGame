#pragma once

#include "textObject.hpp"

class FightText : public TextObject
{
private:
	int numLinesVisible;
	std::vector<std::string> fightLog;

public:
	FightText( const std::string& identifier, const GameObject* parent,
		const std::string& textStr,
		const int numLinesVisible,
		const sf::Vector2f position = sf::Vector2f( 0.f, 0.f ), const sf::Vector2f originFactor = sf::Vector2f( 0.f, 0.f ),
		sf::Font& font = Utils::getDefaultFont(), sf::Color color = sf::Color::Yellow, unsigned int characterSize = 30 );

	void updateFightText( const std::string& textToAdd );
	void appendToLastTextLog( const std::string& textToAdd );
};