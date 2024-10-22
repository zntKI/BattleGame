#pragma once

#include "spriteObject.hpp"

class AnimationSpriteObject : public SpriteObject
{
	sf::IntRect textureRect;
	float frameSwitchTimeSec;

	sf::Clock clock;
	sf::Time elapsed;

public:
	// TODO: Make so the user passes total animation frames and then calculating the frame width and height instead of passing rows and cols separetely!
	// TODO: Add origin factor as it is with text objects!
	AnimationSpriteObject( const std::string& identifier, const std::string& spriteFile, int spriteSheetRows, int spriteSheetCols, float frameSwitchTimeSec,
		const sf::Vector2f& position = sf::Vector2f( 0.f, 0.f ), const sf::Vector2f& scale = sf::Vector2f( 1.f, 1.f ) );
	AnimationSpriteObject( const AnimationSpriteObject& other );
	
	~AnimationSpriteObject();

public:
	float getFrameSwitchTimeSec() const;

	void update() override;

private:
	void setTextureRect();
};

