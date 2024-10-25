#include "button.hpp"
#include "utils.hpp"

Button::Button( const std::string& identifier, const std::string& spriteFile, const int spriteSheetRows, const int spriteSheetCols, const float frameSwitchTimeSec,
	const sf::Vector2f position, const sf::Vector2f scale, const sf::Vector2f originFactor )
	: AnimationSpriteObject( identifier, spriteFile, spriteSheetRows, spriteSheetCols, frameSwitchTimeSec, position, scale, originFactor )
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

void Button::handleEvent( const sf::Event& event, sf::RenderWindow& window )
{
	if ( event.type == sf::Event::MouseButtonPressed &&
		event.mouseButton.button == sf::Mouse::Button::Left ) {

		sf::Vector2i mousePos = sf::Mouse::getPosition( window );

		auto spriteBounds = this->sprite.getGlobalBounds();
		sf::Vector2f size( spriteBounds.width, spriteBounds.height );
		sf::Vector2f position = this->sprite.getPosition();

		if ( mousePos.x >= position.x - currentOriginCoor.x && mousePos.x <= ( position.x + size.x ) - currentOriginCoor.x &&
			mousePos.y >= position.y - currentOriginCoor.y && mousePos.y <= ( position.y + size.y ) - currentOriginCoor.y ) {
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

void Button::setButtonAction( const std::function<void()>& action )
{
	this->action = action;
}