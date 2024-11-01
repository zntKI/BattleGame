#include "animationSpriteObject.hpp"

#include "utils.hpp"

AnimationSpriteObject::AnimationSpriteObject( const std::string& identifier, const GameObject* parent,
	const std::string& spriteFile, const int spriteSheetRows, const int spriteSheetCols, const int totalFrames,
	const sf::Vector2f position, const sf::Vector2f scale, const sf::Vector2f originFactor,
	sf::Vector2f colliderSizeFactor )
	: SpriteObject( identifier, parent, spriteFile, position, scale ),
	totalFrames( totalFrames ),
	startFrame( 0 ), currentFrame( 0 ), numOfFrames( 1 ), frameSwitchTimeSec( .3f ), startFrameTextureRectCoor( sf::Vector2i( 0, 0 ) )
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

		this->finishSetup( originFactor, colliderSizeFactor, scale );
	}
}

AnimationSpriteObject::AnimationSpriteObject( const AnimationSpriteObject& other )
	: SpriteObject( other ), totalFrames( other.totalFrames ), startFrame( 0 ), currentFrame( 0 ), numOfFrames( 1 ), frameSwitchTimeSec( .3f ), startFrameTextureRectCoor( sf::Vector2i( 0, 0 ) )
{
}

AnimationSpriteObject::~AnimationSpriteObject()
{
}

void AnimationSpriteObject::update()
{
	this->elapsed = this->clock.getElapsedTime();

	if ( this->elapsed.asSeconds() >= this->frameSwitchTimeSec ) {
		this->nextFrame();
		this->clock.restart();
	}

	SpriteObject::update();
}

void AnimationSpriteObject::nextFrame()
{
	this->currentFrame++;
	if ( this->currentFrame >= this->startFrame + this->numOfFrames ) {
		this->currentFrame = this->startFrame;
	}

	setTextureRect();
}

void AnimationSpriteObject::setTextureRect()
{
	if ( currentFrame == startFrame ) {
		this->textureRect.left = startFrameTextureRectCoor.x;
		this->textureRect.top = startFrameTextureRectCoor.y;
	}
	else {

		sf::Vector2u textureSize = this->texture.getSize();

		this->textureRect.left += this->textureRect.width;
		if ( this->textureRect.left >= textureSize.x ) {

			this->textureRect.left = 0;
			this->textureRect.top += this->textureRect.height;
		}

	}

	this->sprite.setTextureRect( this->textureRect );
}

void AnimationSpriteObject::setCycle( int startFrame, int numOfFrames, float frameSwitchTimeSec )
{
	if ( startFrame < 0 || startFrame > this->totalFrames - 1 ) {
		Utils::logError( "Invalid start frame index!" );
		return;
	}
	if ( frameSwitchTimeSec <= 0.f ) {
		Utils::logError( "Invalid frameSwitchTimeSec!" );
		return;
	}
	if ( numOfFrames == -1 || numOfFrames > totalFrames - startFrame ) {
		numOfFrames = totalFrames - startFrame;
	}

	this->startFrame = startFrame;
	this->currentFrame = startFrame;
	this->numOfFrames = numOfFrames;
	this->frameSwitchTimeSec = frameSwitchTimeSec;

	if ( startFrame == 0 ) {
		this->startFrameTextureRectCoor.x = this->startFrameTextureRectCoor.y = 0;
	}
	else {

		this->startFrameTextureRectCoor.x = this->startFrameTextureRectCoor.y = 0;

		sf::Vector2u textureSize = this->texture.getSize();

		int frameCounter = 0;
		while ( frameCounter < startFrame ) {

			this->startFrameTextureRectCoor.x += this->textureRect.width;
			if ( this->startFrameTextureRectCoor.x >= textureSize.x ) {

				this->startFrameTextureRectCoor.x = 0;
				this->startFrameTextureRectCoor.y += this->textureRect.height;
			}

			frameCounter++;

		}

	}

	setTextureRect();
	this->clock.restart();
}