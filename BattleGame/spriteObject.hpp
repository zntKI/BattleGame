#pragma once

#include <string>
#include <SFML/Graphics.hpp>

#include "gameObject.hpp"

class SpriteObject : public GameObject
{
protected:
	sf::Vector2f scale;
	sf::Vector2f currentOriginCoor; // Used for accurate origin detection, since the origin you get from the sprite is the initial one that does not change with future scaling
	sf::Vector2f colliderSize;

	std::string spriteFile;
	sf::Texture texture;
	sf::Sprite sprite;

public:
	/// <summary>
	/// ctor for init of sprite objs - WITH the functionality of setting the origin of the obj
	/// </summary>
	/// <param name="originFactor"> -> from 0 to 1 factor which will be then multiplied to the bounds of the sprite, if you want default value, pass (0.f, 0.f)</param>
	/// <param name="scale"> -> if you want default value, pass (1.f, 1.f)</param>
	SpriteObject( const std::string& identifier, const GameObject* parent,
		const std::string& spriteFile,
		const sf::Vector2f position, const sf::Vector2f scale, const sf::Vector2f originFactor,
		sf::Vector2f colliderSizeFactor );

protected:
	/// <summary>
	/// ctor for init of animation sprite objs - WITHOUT the functionality of setting the origin of the obj.<para/>
	/// instead, does it in the animation sprite obj ctor in order to do it correctly
	/// </summary>
	/// <param name="scale"> -> if you want default value, pass (1.f, 1.f)</param>
	SpriteObject( const std::string& identifier, const GameObject* parent,
		const std::string& spriteFile,
		const sf::Vector2f position, const sf::Vector2f scale );

public:
	SpriteObject( const SpriteObject& other );

	~SpriteObject();

protected:
	virtual void finishSetup( const sf::Vector2f originFactor, const sf::Vector2f colliderSizeFactor,
		const sf::Vector2f scale );

	/// <param name="originFactor"> -> from 0 to 1 factor which will be then multiplied to the bounds of the sprite</param>
	virtual void setupOrigin( const sf::Vector2f originFactor );
	/// <param name="colliderSizeFactor"> -> from 0 to 1 factor which will be then multiplied to the sprite's size</param>
	virtual void setupColliderSize( const sf::Vector2f colliderSizeFactor );

public:
	sf::Vector2f getScale() const;
	std::string getSpriteFile() const;
	sf::Vector2f getSpriteSize() const;

	void update() override;
	void render( sf::RenderWindow& window ) override;

	// TODO: Maybe make template for different vector types
	bool isCollidingWithPoint( const sf::Vector2i position ) const;
	bool isCollidingWithPoint( const sf::Vector2f position ) const;

	virtual void setScale( const sf::Vector2f& scale );
};