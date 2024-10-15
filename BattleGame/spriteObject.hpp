#pragma once

#include <string>
#include <SFML/Graphics.hpp>

#include "gameObject.hpp"

class SpriteObject : public GameObject
{
private:
	std::string spriteFile;
	sf::Texture texture;
	sf::Sprite sprite;

public:
	SpriteObject( const std::string identifier, std::string spriteFile );
	SpriteObject( const SpriteObject& other );

	~SpriteObject();

public:
	void update() override;
	void render( sf::RenderWindow& window ) override;

	void setPostion( sf::Vector2f position );
	void setScale( sf::Vector2f scale );
	std::string getSpriteFile() const;
};