#include "character.hpp"

Character::Character(
	// Character specific:
	const std::string& name, const int health, const int attackAmount, const int defenseAmount, const int agility,
	// Animation sprite specific:
	const std::string& identifier, const GameObject* parent,
	const std::string& spriteFile, const int spriteSheetRows, const int spriteSheetCols,
	const sf::Vector2f position, const sf::Vector2f scale, const sf::Vector2f originFactor )
	: AnimationSpriteObject( identifier, parent, spriteFile, spriteSheetRows, spriteSheetCols, position, scale, originFactor ),
	name( name ), health( health ), attackAmount( attackAmount ), defenseAmount( defenseAmount ), agility( agility ),
	healthBar( nullptr ), healthBarFill( nullptr )
{
}

void Character::setHealthBar( SpriteObject* healthBar )
{
	this->healthBar = healthBar;
	this->addChild( healthBar );
}

void Character::setHealthBarFill( SpriteObject* healthBarFill )
{
	this->healthBarFill = healthBarFill;
	this->addChild( healthBarFill );
}