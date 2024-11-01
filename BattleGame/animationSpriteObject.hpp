#pragma once

#include "spriteObject.hpp"

class AnimationSpriteObject : public SpriteObject
{
protected:
	sf::IntRect textureRect;

	int totalFrames;

	int startFrame;
	int currentFrame;
	int numOfFrames;
	float frameSwitchTimeSec;

	sf::Vector2i startFrameTextureRectCoor;

	sf::Clock clock;
	sf::Time elapsed;

public:
	/// <param name="originFactor"> -> from 0 to 1 factor which will be then multiplied to the bounds of the sprite, if you want default value, pass (0.f, 0.f)</param>
	AnimationSpriteObject( const std::string& identifier, const GameObject* parent,
		const std::string& spriteFile, const int spriteSheetRows, const int spriteSheetCols, const int totalFrames,
		const sf::Vector2f position, const sf::Vector2f scale, const sf::Vector2f originFactor,
		sf::Vector2f colliderSizeFactor );

	AnimationSpriteObject( const AnimationSpriteObject& other );
	~AnimationSpriteObject();

	/// <summary>
	/// override from SpriteObject<para/>
	/// also updates animations
	/// </summary>
	void update() override;
	
	/// <summary>
	/// sets animation cycle by adjusting the textureRect to the right starting position
	/// </summary>
	/// <param name="numOfFrames"> -> if '-1' - set to the end of the sprite sheet</param>
	void setCycle( int startFrame, int numOfFrames = -1, float frameSwitchTimeSec = 0.3f );

protected:
	/// <summary>
	/// increments frame and resets it back to start frame when done <para/>
	/// - looping by default (virtual to change behaviour if necessary)
	/// </summary>
	virtual void nextFrame();

	void setTextureRect();
};

