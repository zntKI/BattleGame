#include "character.hpp"
#include "utils.hpp"
#include "gameScene.hpp"
#include "projectile.hpp"

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
	const sf::Vector2f position, const sf::Vector2f scale, const sf::Vector2f originFactor )
	: AnimationSpriteObject( identifier, parent, spriteFile, spriteSheetRows, spriteSheetCols, totalFrames, position, scale, originFactor ),
	scene( *scene ),
	name( name ), health( health ), attackAmount( attackAmount ), defenseAmount( defenseAmount ), agility( agility ),
	idleAnimData( idleAnimStartFrame, idleAnimNumFrames, idleAnimFrameSwitchTimeSec ), attackAnimData( attackAnimStartFrame, attackAnimNumFrames, attackAnimFrameSwitchTimeSec ),
	hurtAnimData( hurtAnimStartFrame, hurtAnimNumFrames, hurtAnimFrameSwitchTimeSec ), dieAnimData( dieAnimStartFrame, dieAnimNumFrames, dieAnimFrameSwitchTimeSec ),
	projectileLaunchFrame( projectileLaunchFrame ),
	projectileData( projectileData ),
	healthBar( nullptr ), healthBarFill( nullptr )
{
	this->setAnimState( CharacterAnimState::Idle );
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
			projectileData[ "originFactor" ][ "y" ] )

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

void Character::setHealthBar( SpriteObject* healthBar )
{
	this->healthBar = healthBar;
}

void Character::setHealthBarFill( SpriteObject* healthBarFill )
{
	this->healthBarFill = healthBarFill;
}