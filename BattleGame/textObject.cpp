#include "textObject.hpp"

TextObject::TextObject( std::string identifier, std::string textStr,
	const sf::Vector2f& position, const sf::Vector2f& scale,
	sf::Font& font, sf::Color color, unsigned int characterSize )
	: GameObject( identifier, position, scale ), font( font ), textColor( color ), textStr( textStr ), characterSize( characterSize )
{
	text.setFont( this->font );
	text.setFillColor( this->textColor );
	text.setString( this->textStr );
	text.setCharacterSize( this->characterSize );

	text.setPosition( this->globalPosition );
	text.setScale( this->scale );
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
	this->text.setScale( this->scale );
}

void TextObject::render( sf::RenderWindow& window )
{
	window.draw( this->text );
}
