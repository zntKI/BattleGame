#include "fightText.hpp"

FightText::FightText( const std::string& identifier, const GameObject* parent,
	const std::string& textStr,
	const int numLinesVisible,
	const sf::Vector2f position, const sf::Vector2f originFactor,
	sf::Font& font, sf::Color color, unsigned int characterSize )
	: TextObject( identifier, parent, textStr, position, originFactor, font, color, characterSize ),
	numLinesVisible( numLinesVisible )
{
	this->text.setCharacterSize( 20 );
	for ( unsigned int i = 0; i < this->numLinesVisible; i++ ) {
		fightLog.push_back( "" );
	}
}

void FightText::updateFightText( const std::string& textToAdd )
{
	this->fightLog.push_back( textToAdd );

	std::string finalText;

	// Goes through the given number of lines and appends them to the visible text log
	for ( auto line = this->fightLog.end() - this->numLinesVisible; line < this->fightLog.end(); line++ ) {

		finalText += *line;
		if ( line < this->fightLog.end() - 1 ) {

			finalText += "\n";

		}

	}

	this->setText( finalText );
}

void FightText::appendToLastTextLog( const std::string& textToAdd )
{
	if ( this->fightLog.empty() ) {
		Utils::logError( "Invalid operation: trying to access last fight log while none exist yet!" );
		return;
	}

	std::string& lastTextLog = this->fightLog.back();
	lastTextLog += textToAdd;
}