#include "button.hpp"
#include "utils.hpp"

Button::Button( const std::string& identifier, const std::string& spriteFile,
	const int spriteSheetRows, const int spriteSheetCols,
	const sf::Vector2f position, const sf::Vector2f scale, const sf::Vector2f originFactor )
	: AnimationSpriteObject( identifier, spriteFile, spriteSheetRows, spriteSheetCols, position, scale, originFactor )
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
	if ( event.type == sf::Event::MouseMoved ) {

		bool mouseWithin = isMouseWithin( window );
		if ( this->textureRect.left == 0 && mouseWithin ) {
			this->textureRect.left += this->textureRect.width; // Switch to hover sprite
		}
		else if ( this->textureRect.left == 0 + this->textureRect.width
			&& !mouseWithin ) {
			this->textureRect.left = 0; // Switch back to normal sprite
		}

	}
	else if ( event.type == sf::Event::MouseButtonPressed &&
		event.mouseButton.button == sf::Mouse::Button::Left &&
		isMouseWithin( window ) ) {

		this->textureRect.left += this->textureRect.width; // Switch to pressed sprite

	}
	else if ( event.type == sf::Event::MouseButtonReleased &&
		event.mouseButton.button == sf::Mouse::Button::Left ) {

		bool mouseWithin = isMouseWithin( window );
		if ( this->textureRect.left == 0 + 2 * this->textureRect.width &&
			!mouseWithin ) {
			this->textureRect.left = 0; // Switch back to normal sprite
		}
		else if ( this->textureRect.left == 0 + 2 * this->textureRect.width &&
			mouseWithin ) {
			this->textureRect.left = 0; // Switch back to normal sprite
			this->onClick();
		}

	}

	this->sprite.setTextureRect( this->textureRect );
}

bool Button::isMouseWithin( sf::RenderWindow& window ) const
{
	sf::Vector2i mousePos = sf::Mouse::getPosition( window );

	auto spriteBounds = this->sprite.getGlobalBounds();
	sf::Vector2f size( spriteBounds.width, spriteBounds.height );
	sf::Vector2f position = this->sprite.getPosition();

	return ( mousePos.x >= position.x - currentOriginCoor.x && mousePos.x <= ( position.x + size.x ) - currentOriginCoor.x ) &&
		( mousePos.y >= position.y - currentOriginCoor.y && mousePos.y <= ( position.y + size.y ) - currentOriginCoor.y );
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