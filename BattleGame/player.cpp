#include "player.hpp"

Player::Player(
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
	: Character( scene, name, health, attackAmount, defenseAmount, agility,
		idleAnimStartFrame, idleAnimNumFrames, idleAnimFrameSwitchTimeSec, attackAnimStartFrame, attackAnimNumFrames, attackAnimFrameSwitchTimeSec,
		hurtAnimStartFrame, hurtAnimNumFrames, hurtAnimFrameSwitchTimeSec, dieAnimStartFrame, dieAnimNumFrames, dieAnimFrameSwitchTimeSec,
		projectileLaunchFrame,
		projectileData,
		identifier, parent, spriteFile, spriteSheetRows, spriteSheetCols, totalFrames, position, scale, originFactor )
{
}