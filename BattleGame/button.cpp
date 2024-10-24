#include "button.hpp"

Button::Button( const std::string& identifier, const sf::Vector2f& buttonSize, sf::Color buttonColor, const sf::Vector2f& position, const sf::Vector2f& scale )
	: GameObject( identifier, position, scale )
{
	this->buttonShape.setSize( buttonSize );
	this->buttonShape.setOrigin( this->buttonShape.getSize() / 2.f );
	this->buttonShape.setPosition( position );
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

void Button::handleEvent( const sf::Event& event, sf::RenderWindow& window )
{
	if ( event.type == sf::Event::MouseButtonPressed &&
		event.mouseButton.button == sf::Mouse::Button::Left ) {

		sf::Vector2i mousePos = sf::Mouse::getPosition( window );

		sf::Vector2f size = this->buttonShape.getSize();
		sf::Vector2f position = this->buttonShape.getPosition();
		sf::Vector2f origin = this->buttonShape.getOrigin();

		if ( mousePos.x >= position.x - origin.x && mousePos.x <= ( position.x + size.x ) - origin.x &&
			mousePos.y >= position.y - origin.y && mousePos.y <= ( position.y + size.y ) - origin.y ) {
			this->onClick();
		}
	}
}

void Button::onClick()
{
	if ( this->action ) {
		this->action();
	}
	else {
		Utils::logError( "Trying to use an unimplemented button!" );
	}
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

void Button::setButtonAction( const std::function<void()>& action )
{
	this->action = action;
}