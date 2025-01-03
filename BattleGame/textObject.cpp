#include "textObject.hpp"

TextObject::TextObject( const std::string& identifier, const GameObject* parent,
	const std::string& textStr,
	const sf::Vector2f position, const sf::Vector2f originFactor,
	sf::Font& font, sf::Color color, unsigned int characterSize )
	: GameObject( identifier, parent, position ), font( font ), textColor( color ), textStr( textStr ), characterSize( characterSize )
{
	this->text.setFont( this->font );
	this->text.setFillColor( this->textColor );
	this->setText( this->textStr );
	this->text.setCharacterSize( this->characterSize );


	if ( originFactor.x >= 0.f && originFactor.x <= 1.f
		&& originFactor.y >= 0.f && originFactor.y <= 1.f ) {
		auto bounds = this->text.getGlobalBounds();
		this->text.setOrigin( originFactor.x * bounds.width, originFactor.y * bounds.height );
	}
	else {
		Utils::logError( "Invalid text originFactor values - should be between 0 and 1 (inclusive)!" );
	}
}

TextObject::TextObject( const TextObject& other )
	: GameObject( other ),
	font( other.getFont() ), textColor( other.getTextColor() ), text( other.getText() ), textStr( other.getTextStr() ), characterSize( other.getCharacterSize() )
{
}

TextObject::~TextObject()
{
}

sf::Font& TextObject::getFont() const
{
	return this->font;
}

sf::Text TextObject::getText() const
{
	return this->text;
}

sf::Color TextObject::getTextColor() const
{
	return this->textColor;
}

std::string TextObject::getTextStr() const
{
	return this->textStr;
}

unsigned int TextObject::getCharacterSize() const
{
	return this->characterSize;
}

void TextObject::update()
{
	this->text.setPosition( this->globalPosition );
}

void TextObject::render( sf::RenderWindow& window )
{
	window.draw( this->text );
}

void TextObject::setText( const std::string& textStr )
{
	this->text.setString( textStr );
}

void TextObject::setCharacterSize( unsigned int characterSize )
{
	this->characterSize = characterSize;
	this->text.setCharacterSize( this->characterSize );
}