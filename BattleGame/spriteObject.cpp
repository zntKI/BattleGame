#include "spriteObject.hpp"

SpriteObject::SpriteObject( const std::string identifier, std::string spriteFile )
	: GameObject( identifier ), spriteFile( spriteFile )
{
	this->texture.loadFromFile( this->spriteFile );
	this->sprite.setTexture( this->texture );
}

SpriteObject::SpriteObject( const SpriteObject& other )
	: GameObject( other ), spriteFile( other.getSpriteFile() )
{
	this->texture.loadFromFile( this->spriteFile );
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
