#include "button.hpp"
#include "utils.hpp"

Button::Button( const std::string& identifier, const GameObject* parent,
	const std::string& spriteFile,
	const int spriteSheetRows, const int spriteSheetCols, const int totalFrames,
	const sf::Vector2f position, const sf::Vector2f scale, const sf::Vector2f originFactor,
	sf::Vector2f colliderSizeFactor )
	: AnimationSpriteObject( identifier, parent, spriteFile, spriteSheetRows, spriteSheetCols, totalFrames, position, scale, originFactor, colliderSizeFactor ),
	text( nullptr )
{
}

Button::Button( const Button& other )
	: AnimationSpriteObject( other ), action( other.getButtonAction() )
{
}

Button::~Button()
{
}

std::function<void()> Button::getButtonAction() const
{
	return this->action;
}

void Button::update()
{
	SpriteObject::update();
}

void Button::handleEvent( const sf::Event& event, sf::RenderWindow& window )
{
	bool isMouseWithin = this->isCollidingWithPoint( sf::Mouse::getPosition( window ) );

	if ( event.type == sf::Event::MouseMoved ) {

		if ( this->textureRect.left == 0 && isMouseWithin ) {
			this->textureRect.left += this->textureRect.width; // Switch to hover sprite
		}
		else if ( this->textureRect.left == 0 + this->textureRect.width
			&& !isMouseWithin ) {
			this->textureRect.left = 0; // Switch back to normal sprite
		}

	}
	else if ( event.type == sf::Event::MouseButtonPressed &&
		event.mouseButton.button == sf::Mouse::Button::Left &&
		isMouseWithin ) {

		this->textureRect.left += this->textureRect.width; // Switch to pressed sprite

	}
	else if ( event.type == sf::Event::MouseButtonReleased &&
		event.mouseButton.button == sf::Mouse::Button::Left ) {

		if ( this->textureRect.left == 0 + 2 * this->textureRect.width &&
			!isMouseWithin ) {
			this->textureRect.left = 0; // Switch back to normal sprite
		}
		else if ( this->textureRect.left == 0 + 2 * this->textureRect.width &&
			isMouseWithin ) {
			this->textureRect.left = 0; // Switch back to normal sprite
			this->onClick();
		}

	}

	this->sprite.setTextureRect( this->textureRect );
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

void Button::setButtonAction( const std::function<void()>& action )
{
	this->action = action;
}

void Button::setText( TextObject* text )
{
	this->text = text;
}