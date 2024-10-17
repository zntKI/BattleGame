#include "spriteObject.hpp"
#include "utils.hpp"

SpriteObject::SpriteObject( const std::string& identifier, const std::string& spriteFile,
	const sf::Vector2f& position, const sf::Vector2f& scale,
	GameObject* const parent )
	: GameObject( identifier, position, scale, parent ), spriteFile( spriteFile )
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

void SpriteObject::render( sf::RenderWindow& window )
{
	window.draw( this->sprite );
}

std::string SpriteObject::getSpriteFile() const
{
	return this->spriteFile;
}
