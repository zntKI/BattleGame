#include "spriteObject.hpp"

SpriteObject::SpriteObject( const std::string identifier, std::string spriteFile )
	: GameObject(identifier), spriteFile(spriteFile)
{
	this->texture.loadFromFile( this->spriteFile );
	this->sprite.setTexture( this->texture );
}

SpriteObject::SpriteObject( const SpriteObject& other )
	: GameObject(other.getIdentifier()), spriteFile(other.getSpriteFile())
{
	this->texture.loadFromFile( this->spriteFile );
	this->sprite.setTexture( this->texture );
}

SpriteObject::~SpriteObject()
{
}

void SpriteObject::update()
{
}

void SpriteObject::render( sf::RenderWindow& window )
{
	window.draw( this->sprite );
	
	// This way it won't work:
	/*for ( auto element = this->children.begin(); element != this->children.end(); element++ ) {
		element->second->render( window );
	}*/
	// TODO: figure smth out
}

void SpriteObject::setPostion( sf::Vector2f position )
{
	this->sprite.setPosition( position );
	// TODO: Figure out a way to make all children change pos accordingly
}

void SpriteObject::setScale( sf::Vector2f scale )
{
	this->sprite.setScale( scale );
}

std::string SpriteObject::getSpriteFile() const
{
	return this->spriteFile;
}
