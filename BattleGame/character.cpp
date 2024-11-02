#include "character.hpp"
#include "utils.hpp"
#include "gameScene.hpp"
#include "projectile.hpp"

#include <iostream>
#include <sstream>
#include <string>

Character::Character(
	// Character specific:
	GameScene* scene,
	const std::string& name, const int health, const int attackAmount, const int defenseAmount, const int agility,
	const int idleAnimStartFrame, const int idleAnimNumFrames, const float idleAnimFrameSwitchTimeSec,
	const int attackAnimStartFrame, const int attackAnimNumFrames, const float attackAnimFrameSwitchTimeSec,
	const int hurtAnimStartFrame, const int hurtAnimNumFrames, const float hurtAnimFrameSwitchTimeSec,
	const int dieAnimStartFrame, const int dieAnimNumFrames, const float dieAnimFrameSwitchTimeSec,
	const int projectileLaunchFrame,
	nlohmann::json projectileData,
	// Animation sprite specific:
	const std::string& identifier, const GameObject* parent,
	const std::string& spriteFile, const int spriteSheetRows, const int spriteSheetCols, const int totalFrames,
	const sf::Vector2f position, const sf::Vector2f scale, const sf::Vector2f originFactor,
	sf::Vector2f colliderSizeFactor )
	: AnimationSpriteObject( identifier, parent, spriteFile, spriteSheetRows, spriteSheetCols, totalFrames, position, scale, originFactor, colliderSizeFactor ),
	scene( *scene ),
	name( name ), health( health ), currentHealth( health ), attackAmount( attackAmount ), defenseAmount( defenseAmount ), agility( agility ),
	idleAnimData( idleAnimStartFrame, idleAnimNumFrames, idleAnimFrameSwitchTimeSec ), attackAnimData( attackAnimStartFrame, attackAnimNumFrames, attackAnimFrameSwitchTimeSec ),
	hurtAnimData( hurtAnimStartFrame, hurtAnimNumFrames, hurtAnimFrameSwitchTimeSec ), dieAnimData( dieAnimStartFrame, dieAnimNumFrames, dieAnimFrameSwitchTimeSec ),
	projectileLaunchFrame( projectileLaunchFrame ),
	projectileData( projectileData ),
	healthBar( nullptr ), healthBarFill( nullptr )
{
	this->setAnimState( CharacterAnimState::Idle );
}

const std::string& Character::getName() const
{
	return this->name;
}

int Character::getAgility() const
{
	return this->agility;
}

void Character::nextFrame()
{
	this->currentFrame++;
	if ( this->currentFrame >= this->startFrame + this->numOfFrames ) {

		if ( this->animState == CharacterAnimState::Attack ) {

			this->setAnimState( CharacterAnimState::Idle );
			return;

		}
		else if ( this->animState == CharacterAnimState::Hurt ) {

			this->setAnimState( CharacterAnimState::Idle );
			this->scene.swapCharacterTurn( true, this );

			return;

		}
		else if ( this->animState == CharacterAnimState::Die ) {

			this->currentFrame--;

			this->scene.finishBattle( this );

			return;

		}

		this->currentFrame = this->startFrame;
	}

	this->setTextureRect();

	if ( this->animState == CharacterAnimState::Attack &&
		this->currentFrame == this->projectileLaunchFrame ) { // Launch projectile

		this->createProjectile();

	}
}


void Character::createProjectile()
{
	Projectile* projectile = new Projectile(

		"projectile",
		this,
		projectileData[ "filePath" ],
		projectileData[ "spriteSheetRows" ],
		projectileData[ "spriteSheetCols" ],
		projectileData[ "totalFrames" ],
		sf::Vector2f( projectileData[ "position" ][ "x" ],
			projectileData[ "position" ][ "y" ] ),
		sf::Vector2f( projectileData[ "scale" ][ "x" ],
			projectileData[ "scale" ][ "y" ] ),
		sf::Vector2f( projectileData[ "originFactor" ][ "x" ],
			projectileData[ "originFactor" ][ "y" ] ),
		sf::Vector2f( projectileData[ "colliderSizeFactor" ][ "x" ],
			projectileData[ "colliderSizeFactor" ][ "y" ] ),
		this->attackAmount,
		sf::Vector2f( projectileData[ "moveVelocity" ][ "x" ],
			projectileData[ "moveVelocity" ][ "y" ] ),
		this->scene

	);
	projectile->finishInit();

	this->scene.addGameObject( projectile );
}

void Character::setAnimState( CharacterAnimState animState )
{
	this->animState = animState;

	switch ( animState ) {
	case CharacterAnimState::Idle:
		this->setCycle( idleAnimData.getStartFrame(), idleAnimData.getNumFrames(), idleAnimData.getFrameSwitchTimeSec() );
		break;
	case CharacterAnimState::Attack:
		this->setCycle( attackAnimData.getStartFrame(), attackAnimData.getNumFrames(), attackAnimData.getFrameSwitchTimeSec() );
		break;
	case CharacterAnimState::Hurt:
		this->setCycle( hurtAnimData.getStartFrame(), hurtAnimData.getNumFrames(), hurtAnimData.getFrameSwitchTimeSec() );
		break;
	case CharacterAnimState::Die:
		this->setCycle( dieAnimData.getStartFrame(), dieAnimData.getNumFrames(), dieAnimData.getFrameSwitchTimeSec() );
		break;
	default:
		Utils::logError( "Incorrect CharacterAnimState enum value!" );
		break;
	}
}

void Character::takeDamage( int damageAmount )
{
	damageAmount -= this->defenseAmount;
	if ( damageAmount < 0 ) {
		damageAmount = 0;
	}

	int healthAfterDamage = this->currentHealth - damageAmount;
	if ( healthAfterDamage <= 0 ) { // Dead

		damageAmount = this->currentHealth;
		this->currentHealth = 0.f;

		this->setAnimState( CharacterAnimState::Die );

	}
	else { // Hurt

		this->setAnimState( CharacterAnimState::Hurt );
		if ( healthAfterDamage == this->currentHealth ) {

			defenseAmount -= rand() % defenseAmount;

		}

		this->currentHealth = healthAfterDamage;

	}

	this->setHealthBarFillScale( true, damageAmount );


	// Send to scene to log
	std::ostringstream oss;
	oss << this->name
		<< ( dynamic_cast< Opponent* >( this ) != nullptr ? "(Enemy) " : "(Player) " )
		<< "for " << damageAmount;
	this->scene.appendToLastTextLog( oss.str() );
}

void Character::attack()
{
	this->setAnimState( CharacterAnimState::Attack );
	this->scene.setCharacterTurn( CharacterTurn::None );

	// Send to scene to log
	this->scene.appendToLastTextLog( "Attacked and damaged " );
}

void Character::recover()
{
	int healAmount = 1 + ( rand() % this->defenseAmount );
	int healthAfterHealing = this->currentHealth + healAmount;
	if ( healthAfterHealing > this->health ) {

		healAmount = this->health - this->currentHealth;
		this->currentHealth = this->health;

	}
	else {

		this->currentHealth = healthAfterHealing;

	}

	this->setHealthBarFillScale( false, healAmount );


	// Send to scene to log
	std::ostringstream oss;
	oss << "Recovered by " << healAmount;
	this->scene.appendToLastTextLog( oss.str() );


	this->scene.swapCharacterTurn( false, this );
}

void Character::setHealthBarFillScale( bool shouldReduce, int numOfHealthPoints )
{
	float currentScaleX = this->healthBarFill->getScale().x;
	float resultScaleX = currentScaleX + ( numOfHealthPoints * fractionForOneHealthPoint ) * ( shouldReduce ? -1.f : 1.f );
	healthBarFill->setScale( sf::Vector2f( resultScaleX / currentScaleX, 1.f ) );
}

void Character::setHealthBar( SpriteObject* healthBar )
{
	this->healthBar = healthBar;
}

void Character::setHealthBarFill( SpriteObject* healthBarFill )
{
	this->healthBarFill = healthBarFill;

	float spriteSizeX = this->healthBarFill->getSpriteSize().x;
	this->fractionForOneHealthPoint = ( spriteSizeX / this->health * 1.f ) / spriteSizeX;
}