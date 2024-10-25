#pragma once

#include "spriteObject.hpp"

class AnimationSpriteObject : public SpriteObject
{
protected:
	sf::IntRect textureRect;
	float frameSwitchTimeSec;

	sf::Clock clock;
	sf::Time elapsed;

public:
	/// <summary>
	/// ctor used by AnimationSprite class
	/// </summary>
	/// <param name="originFactor"> -> from 0 to 1 factor which will be then multiplied to the bounds of the sprite, if you want default value, pass (0.f, 0.f)</param>
	AnimationSpriteObject( const std::string& identifier, const std::string& spriteFile, const int spriteSheetRows, const int spriteSheetCols, const float frameSwitchTimeSec,
		const sf::Vector2f position, const sf::Vector2f scale, const sf::Vector2f originFactor );
protected:
	/// <summary>
	/// ctor used by BUTTON class
	/// </summary>
	/// <param name="originFactor"> -> from 0 to 1 factor which will be then multiplied to the bounds of the sprite, if you want default value, pass (0.f, 0.f)</param>
	AnimationSpriteObject( const std::string& identifier, const std::string& spriteFile, const int spriteSheetRows, const int spriteSheetCols,
		const sf::Vector2f position, const sf::Vector2f scale, const sf::Vector2f originFactor );

public:
	AnimationSpriteObject( const AnimationSpriteObject& other );
	
	~AnimationSpriteObject();

public:
	float getFrameSwitchTimeSec() const;

	void update() override;

private:
	void setTextureRect();
};

