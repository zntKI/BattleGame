#pragma once

#include <string>
#include <SFML/Graphics.hpp>

#include "gameObject.hpp"

class SpriteObject : public GameObject
{
protected:
	sf::Vector2f scale;
	sf::Vector2f currentOriginCoor; // Used for accurate origin detection, since the origin you get from the sprite is the initial one that does not change with future scaling

	std::string spriteFile;
	sf::Texture texture;
	sf::Sprite sprite;

public:
	/// <summary>
	/// ctor for init of sprite objs - WITH the functionality of setting the origin of the obj
	/// </summary>
	/// <param name="originFactor"> -> from 0 to 1 factor which will be then multiplied to the bounds of the sprite, if you want default value, pass (0.f, 0.f)</param>
	/// <param name="scale"> -> if you want default value, pass (1.f, 1.f)</param>
	SpriteObject( const std::string& identifier, const std::string& spriteFile,
		const sf::Vector2f position, const sf::Vector2f scale, const sf::Vector2f originFactor );
	
protected:
	/// <summary>
	/// ctor for init of animation sprite objs - WITHOUT the functionality of setting the origin of the obj.<para/>
	/// instead, does it in the animation sprite obj ctor in order to do it correctly
	/// </summary>
	/// <param name="scale"> -> if you want default value, pass (1.f, 1.f)</param>
	SpriteObject( const std::string& identifier, const std::string& spriteFile,
		const sf::Vector2f position, const sf::Vector2f scale );

public:
	SpriteObject( const SpriteObject& other );

	~SpriteObject();

protected:
	/// <param name="originFactor"> -> from 0 to 1 factor which will be then multiplied to the bounds of the sprite</param>
	virtual void setupOrigin( const sf::Vector2f& originFactor );

public:
	sf::Vector2f getScale() const;
	std::string getSpriteFile() const;
	sf::Vector2f getSpriteSize() const;

	void update() override;
	void render( sf::RenderWindow& window ) override;

	virtual void setScale( const sf::Vector2f& scale );
};