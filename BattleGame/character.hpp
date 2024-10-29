#pragma once

#include <nlohmann/json.hpp>

#include "animationSpriteObject.hpp"

class Character : public AnimationSpriteObject
{
private:
	const std::string name;
	int health;

	int attackAmount;
	int defenseAmount;
	int agility;

	SpriteObject* healthBar;
	SpriteObject* healthBarFill;

public:
	Character(
		// Character specific:
		const std::string& name, const int health, const int attackAmount, const int defenseAmount, const int agility,
		// Animation sprite specific:
		const std::string& identifier, const GameObject* parent,
		const std::string& spriteFile, const int spriteSheetRows, const int spriteSheetCols,
		const sf::Vector2f position, const sf::Vector2f scale, const sf::Vector2f originFactor );

	void setHealthBar( SpriteObject* healthBar );
	void setHealthBarFill( SpriteObject* healthBarFill );
};