#pragma once

#include "spriteObject.hpp"

class AnimationSpriteObject : public SpriteObject
{
	sf::IntRect textureRect;
	float frameSwitchTimeSec;

	sf::Clock clock;
	sf::Time elapsed;

public:
	/// <param name="originFactor"> -> from 0 to 1 factor which will be then multiplied to the bounds of the sprite, if you want default value, pass (0.f, 0.f)</param>
	AnimationSpriteObject( const std::string& identifier, const std::string& spriteFile, int spriteSheetRows, int spriteSheetCols, float frameSwitchTimeSec,
		const sf::Vector2f& position, const sf::Vector2f& scale, const sf::Vector2f& originFactor );
	AnimationSpriteObject( const AnimationSpriteObject& other );
	
	~AnimationSpriteObject();

public:
	float getFrameSwitchTimeSec() const;

	void update() override;

private:
	void setTextureRect();
};

