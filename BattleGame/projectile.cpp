#include "projectile.hpp"

#include "gameScene.hpp"
#include "character.hpp"

Projectile::Projectile( const std::string& identifier, const GameObject* parent,
	const std::string& spriteFile, const int spriteSheetRows, const int spriteSheetCols, const int totalFrames,
	const sf::Vector2f position, const sf::Vector2f scale, const sf::Vector2f originFactor,
	sf::Vector2f colliderSizeFactor,
	const int damageAmount, const sf::Vector2f moveVelocity, GameScene& scene )
	: AnimationSpriteObject( identifier, parent, spriteFile, spriteSheetRows, spriteSheetCols, totalFrames, position, scale, originFactor, colliderSizeFactor ),
	damageAmount( damageAmount ), moveVelocity( moveVelocity ), target( scene.getOtherCharacter( parent ) )
{
	this->setCycle( 0 );
}

void Projectile::update()
{
	this->move( moveVelocity );
	if ( this->target.isCollidingWithPoint( this->globalPosition ) ) {

		int damageDealt = this->target.takeDamage( this->damageAmount ); // Before destroying projectile to use parent-child relation
		Player* character = dynamic_cast< Player* > ( this->parent );
		if ( character != nullptr ) { // The character is a Player
			character->addDamageDealt( damageDealt );
		}

		this->destroy();

	}

	AnimationSpriteObject::update();
}