#include "button.hpp"

Button::Button( std::string identifier, const sf::Vector2f& buttonSize, sf::Color buttonColor, const sf::Vector2f& position, const sf::Vector2f& scale )
	: GameObject( identifier, position, scale )
{
	this->buttonShape.setPosition( position );
	this->buttonShape.setSize( buttonSize );
	this->buttonShape.setFillColor( buttonColor );
}

Button::Button( const Button& other )
	: GameObject( other ), buttonShape( other.getButtonShape() )
{
}

Button::~Button()
{
}

sf::RectangleShape Button::getButtonShape() const
{
	return this->buttonShape;
}

void Button::update()
{
	this->buttonShape.setPosition( this->globalPosition );
	this->buttonShape.setScale( this->scale );
}

void Button::render( sf::RenderWindow& window )
{
	window.draw( this->buttonShape );
}
