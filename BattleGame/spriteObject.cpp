#include "spriteObject.hpp"
#include "utils.hpp"

SpriteObject::SpriteObject( const std::string& identifier, const GameObject* parent,
	const std::string& spriteFile,
	const sf::Vector2f position, const sf::Vector2f scale, const sf::Vector2f originFactor )
	: SpriteObject( identifier, parent, spriteFile, position, scale )
{
	setupOrigin( originFactor ); // Should be before setting scale

	this->setScale( scale ); // Called first to correctly set the 'currentOriginCoor'
	this->sprite.setScale( this->scale ); // Called second to finalize sprite scaling
}

SpriteObject::SpriteObject( const std::string& identifier, const GameObject* parent,
	const std::string& spriteFile,
	const sf::Vector2f position, const sf::Vector2f scale )
	: GameObject( identifier, parent, position ), spriteFile( spriteFile ), scale( sf::Vector2f( 1.f, 1.f ) )
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
		this->currentOriginCoor = sf::Vector2f( originFactor.x * bounds.width, originFactor.y * bounds.height ); // Setup of 'currentOriginCoor' for following changes in 'setScale'
		this->sprite.setOrigin( this->currentOriginCoor ); // Setup of initial and final sprite origin that will not be modified any further
	}
	else {
		Utils::logError( "Invalid sprite originFactor values - should be between 0 and 1 (inclusive)!" );
	}
}

sf::Vector2f SpriteObject::getScale() const
{
	return this->scale;
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

void SpriteObject::update()
{
	this->sprite.setPosition( this->globalPosition );
	this->sprite.setScale( this->scale );
}

void SpriteObject::render( sf::RenderWindow& window )
{
	window.draw( this->sprite );
}

void SpriteObject::setScale( const sf::Vector2f& scale )
{
	this->scale = sf::Vector2f( this->scale.x * scale.x, this->scale.y * scale.y );
	this->currentOriginCoor = sf::Vector2f( this->currentOriginCoor.x * scale.x, this->currentOriginCoor.y * scale.y ); // Adjusted accordingly to the scale of the sprite

	for ( auto element = this->children.begin(); element != this->children.end(); element++ ) {

		// Check if the child is a SpriteObj in order to set its scale since only SpriteObjects have scale
		GameObject* childGameObject = element->second;
		SpriteObject* childSpriteObject = dynamic_cast< SpriteObject* >( childGameObject );

		if ( childSpriteObject != nullptr ) {
			childSpriteObject->setScale( scale );
		}

	}
}