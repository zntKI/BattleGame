#include "opponent.hpp"
#include "utils.hpp"

#include "gameScene.hpp"

Opponent::Opponent(
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
	: Character( scene, name, health, attackAmount, defenseAmount, agility,
		idleAnimStartFrame, idleAnimNumFrames, idleAnimFrameSwitchTimeSec, attackAnimStartFrame, attackAnimNumFrames, attackAnimFrameSwitchTimeSec,
		hurtAnimStartFrame, hurtAnimNumFrames, hurtAnimFrameSwitchTimeSec, dieAnimStartFrame, dieAnimNumFrames, dieAnimFrameSwitchTimeSec,
		projectileLaunchFrame,
		projectileData,
		identifier, parent, spriteFile, spriteSheetRows, spriteSheetCols, totalFrames, position, scale, originFactor, colliderSizeFactor ),
	charTurn( scene->getCharTurnState() )
{
}

void Opponent::update()
{
	if ( this->charTurn == CharacterTurn::OpponentTurn ) {

		int rndAction = rand() % 3;
		switch ( rndAction ) {
		case 0: /*Attack*/

			this->attack();

			break;
		case 1: /*Recover*/

			this->recover();

			break;
		case 2: /*Do nothing*/

			this->doNothing();

			break;
		default:
			Utils::logError( "Incorrectly generated rnd number in Opponent's update()!" );
			break;
		}

	}

	AnimationSpriteObject::update();
}

void Opponent::doNothing()
{
	this->scene.appendToLastTextLog( "Did nothing" );
	this->scene.swapCharacterTurn( false, this );
}

void Opponent::nextFrame()
{
	Character::nextFrame();
}