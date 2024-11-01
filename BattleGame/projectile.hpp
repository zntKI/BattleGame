#pragma once

#include "animationSpriteObject.hpp"

class GameScene;
class Character;

class Projectile : public AnimationSpriteObject
{
private:

	int damageAmount;
	sf::Vector2f moveVelocity;

	//GameScene& scene;
	Character& target;

public:
	Projectile( const std::string& identifier, const GameObject* parent,
		const std::string& spriteFile, const int spriteSheetRows, const int spriteSheetCols, const int totalFrames,
		const sf::Vector2f position, const sf::Vector2f scale, const sf::Vector2f originFactor,
		sf::Vector2f colliderSizeFactor,
		const int damageAmount, const sf::Vector2f moveVelocity, GameScene& scene );

	void update() override;
};