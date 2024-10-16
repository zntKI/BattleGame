#include "textObject.hpp"

TextObject::TextObject( const std::string identifier, std::string& textStr,
	const sf::Vector2f position, const sf::Vector2f scale, GameObject* parent,
	sf::Font& font )
	: GameObject( identifier, position, scale, parent ), font( font ), textStr( textStr )
{
}

TextObject::TextObject( const TextObject& other )
	: GameObject( other ),
	font( other.getFont() ), text( other.getText() ), textStr( this->getTextStr() )
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

std::string TextObject::getTextStr() const
{
	return this->textStr;
}

void TextObject::render( sf::RenderWindow& window )
{
	window.draw( this->text );
}
