#pragma once

#include "spriteObject.hpp"

class AnimationSpriteObject : public SpriteObject
{
protected:
	sf::IntRect textureRect;

	sf::Clock clock;
	sf::Time elapsed;

public:
	/// <param name="originFactor"> -> from 0 to 1 factor which will be then multiplied to the bounds of the sprite, if you want default value, pass (0.f, 0.f)</param>
	AnimationSpriteObject( const std::string& identifier, const GameObject* parent,
		const std::string& spriteFile, const int spriteSheetRows, const int spriteSheetCols,
		const sf::Vector2f position, const sf::Vector2f scale, const sf::Vector2f originFactor );

	AnimationSpriteObject( const AnimationSpriteObject& other );
	~AnimationSpriteObject();


	void update() override;

private:
	void setTextureRect();
};

