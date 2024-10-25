#include "animationSpriteObject.hpp"

#include "utils.hpp"

AnimationSpriteObject::AnimationSpriteObject( const std::string& identifier,
	const std::string& spriteFile, const int spriteSheetRows, const int spriteSheetCols, const float frameSwitchTimeSec,
	const sf::Vector2f position, const sf::Vector2f scale, const sf::Vector2f originFactor )
	: SpriteObject( identifier, spriteFile, position, scale ), frameSwitchTimeSec( frameSwitchTimeSec )
{
	sf::Vector2u textureSize = this->texture.getSize();

	if ( textureSize.x % spriteSheetCols != 0 ||
		textureSize.y % spriteSheetRows != 0 ) {
		Utils::logError( "Invalid rows or cols for sprite sheet - a remainder present after dividing the sprite sheet!" );
	}
	else {
		this->textureRect.width = textureSize.x / spriteSheetCols;
		this->textureRect.height = textureSize.y / spriteSheetRows;

		this->sprite.setTextureRect( this->textureRect );

		setupOrigin( originFactor ); // Should be before setting scale

		this->setScale( scale ); // Called first to correctly set the 'currentOriginCoor'
		this->sprite.setScale( this->scale ); // Called second to finalize sprite scaling
	}
}

AnimationSpriteObject::AnimationSpriteObject( const std::string& identifier, const std::string& spriteFile,
	const int spriteSheetRows, const int spriteSheetCols,
	const sf::Vector2f position, const sf::Vector2f scale, const sf::Vector2f originFactor )
	: AnimationSpriteObject( identifier, spriteFile, spriteSheetRows, spriteSheetCols, -1.f, position, scale, originFactor )
{
}

AnimationSpriteObject::AnimationSpriteObject( const AnimationSpriteObject& other )
	: SpriteObject( other ), frameSwitchTimeSec( other.getFrameSwitchTimeSec() )
{
}

AnimationSpriteObject::~AnimationSpriteObject()
{
}

float AnimationSpriteObject::getFrameSwitchTimeSec() const
{
	return this->frameSwitchTimeSec;
}

void AnimationSpriteObject::update()
{
	this->elapsed = this->clock.getElapsedTime();

	if ( this->elapsed.asSeconds() >= this->frameSwitchTimeSec ) {
		setTextureRect();
		this->clock.restart();
	}

	SpriteObject::update();
}

void AnimationSpriteObject::setTextureRect()
{
	sf::Vector2u textureSize = this->texture.getSize();

	this->textureRect.left += this->textureRect.width;
	if ( this->textureRect.left >= textureSize.x ) {

		this->textureRect.left = 0;
		this->textureRect.top += this->textureRect.height;

		if ( this->textureRect.top >= textureSize.y ) {

			this->textureRect.top = 0;
		}
	}

	this->sprite.setTextureRect( this->textureRect );
}