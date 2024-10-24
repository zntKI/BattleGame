#include "spriteObject.hpp"
#include "utils.hpp"

SpriteObject::SpriteObject( const std::string& identifier, const std::string& spriteFile,
	const sf::Vector2f& position, const sf::Vector2f& scale, const sf::Vector2f& originFactor )
	: SpriteObject( identifier, spriteFile, position, scale )
{
	setupOrigin( originFactor );

	this->sprite.setScale( scale );
}

SpriteObject::SpriteObject( const std::string& identifier, const std::string& spriteFile,
	const sf::Vector2f& position, const sf::Vector2f& scale )
	: GameObject( identifier, position, scale ), spriteFile( spriteFile )
{
	if ( !this->texture.loadFromFile( this->spriteFile ) ) {
		Utils::logError( "Unable to load texture from file!" );
	}
	this->sprite.setTexture( this->texture );
}

SpriteObject::SpriteObject( const SpriteObject& other )
	: GameObject( other ), spriteFile( other.getSpriteFile() )
{
	if ( !this->texture.loadFromFile( this->spriteFile ) ) {
		Utils::logError( "Unable to load texture from file!" );
	}
	this->sprite.setTexture( this->texture );
}

SpriteObject::~SpriteObject()
{
}

void SpriteObject::setupOrigin( const sf::Vector2f& originFactor )
{
	if ( originFactor.x >= 0.f && originFactor.x <= 1.f
		&& originFactor.y >= 0.f && originFactor.y <= 1.f ) {
		auto bounds = this->sprite.getGlobalBounds();
		this->sprite.setOrigin( originFactor.x * bounds.width, originFactor.y * bounds.height );
	}
	else {
		Utils::logError( "Invalid sprite originFactor values - should be between 0 and 1 (inclusive)!" );
	}
}

void SpriteObject::update()
{
	this->sprite.setPosition( this->globalPosition );
	this->sprite.setScale( this->scale );
}

void SpriteObject::render( sf::RenderWindow& window )
{
	window.draw( this->sprite );
}

std::string SpriteObject::getSpriteFile() const
{
	return this->spriteFile;
}

sf::Vector2f SpriteObject::getSpriteSize() const
{
	auto bounds = this->sprite.getGlobalBounds();
	sf::Vector2f size( bounds.width, bounds.height );
	return size;
}