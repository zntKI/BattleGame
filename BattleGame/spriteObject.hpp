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
	SpriteObject( const std::string& identifier, const std::string& spriteFile,
		const sf::Vector2f& position = sf::Vector2f( 0.f, 0.f ), const sf::Vector2f& scale = sf::Vector2f( 1.f, 1.f ),
		GameObject* const parent = nullptr );
	SpriteObject( const SpriteObject& other );

	~SpriteObject();

public:
	void render( sf::RenderWindow& window ) override;

	std::string getSpriteFile() const;
};