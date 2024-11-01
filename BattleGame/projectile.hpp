#pragma once

#include "animationSpriteObject.hpp"

class Projectile : public AnimationSpriteObject
{
public:
	Projectile( const std::string& identifier, const GameObject* parent,
		const std::string& spriteFile, const int spriteSheetRows, const int spriteSheetCols, const int totalFrames,
		const sf::Vector2f position, const sf::Vector2f scale, const sf::Vector2f originFactor );
};