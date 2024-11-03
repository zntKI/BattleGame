#pragma once

#include "character.hpp"

class GameScene;
enum class CharacterTurn;

class Opponent : public Character
{
private:
	/// <summary>
	/// Taken from GameScene
	/// </summary>
	const CharacterTurn& charTurn;

public:
	Opponent(
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

	/// <summary>
	/// override to deal with AI mechanics
	/// </summary>
	void update() override;

	void doNothing();

private:
	void nextFrame() override;
};