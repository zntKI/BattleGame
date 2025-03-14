#pragma once

#include "character.hpp"

class GameScene;

class Player : public Character
{
private:
	int damageDealt; // Used for high score persistency

	bool shouldStopAnimAfterDeath;

public:
	Player(
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
		sf::Vector2f colliderSizeFactor );

	int getDamageDealt() const;
	void addDamageDealt( int damageDealt );

private:
	void update() override;
	void nextFrame() override;
};