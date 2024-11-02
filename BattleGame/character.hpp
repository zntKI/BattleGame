#pragma once

#include <nlohmann/json.hpp>

#include "animationSpriteObject.hpp"

class GameScene;

enum class CharacterAnimState
{
	Idle,
	Attack,
	Hurt,
	Die
};

/// <summary>
/// contains animation data for animation states
/// </summary>
struct AnimCycleData
{
private:
	const int startFrame;
	const int numFrames;
	float frameSwitchTimeSec;

public:
	AnimCycleData( const int startFrame, const int numFrames, const float frameSwitchTimeSec )
		: startFrame( startFrame ), numFrames( numFrames ), frameSwitchTimeSec( frameSwitchTimeSec )
	{
	}

	int getStartFrame() const {
		return this->startFrame;
	}
	int getNumFrames() const {
		return this->numFrames;
	}
	float getFrameSwitchTimeSec() const {
		return this->frameSwitchTimeSec;
	}
};

class Character : public AnimationSpriteObject
{
protected:
	const std::string name;
	int health;
	int currentHealth;

	int attackAmount;
	int defenseAmount;
	int agility;

	CharacterAnimState animState;
	AnimCycleData idleAnimData;
	AnimCycleData attackAnimData;
	AnimCycleData hurtAnimData;
	AnimCycleData dieAnimData;

	GameScene& scene;

	const int projectileLaunchFrame;
	nlohmann::json projectileData; // data stored for later initialization

	SpriteObject* healthBar;
	SpriteObject* healthBarFill;
	float fractionForOneHealthPoint; // the percentage one health point takes from the whole health bar fill

public:
	Character(
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

	const std::string& getName() const;
	int getAgility() const;

	/// <summary>
	/// sets anim state and also sets the animation cycle with the corresponding data
	/// </summary>
	void setAnimState( CharacterAnimState animState );

	void takeDamage( int damageAmount );

	void attack();
	void recover();

	void setHealthBar( SpriteObject* healthBar );
	void setHealthBarFill( SpriteObject* healthBarFill );

protected:
	/// <summary>
	/// override to detect the frame in which the projectile should be spawned <para/>
	/// also to alter animation cycle logic
	/// </summary>
	void nextFrame() override;

	/// <summary>
	/// creates projectile and adds it to scenes collection
	/// </summary>
	void createProjectile();

	void setHealthBarFillScale( bool shouldReduce, int numOfHealthPoints );
};