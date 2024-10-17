#pragma once

#include <SFML/Graphics.hpp>

#include "gameObject.hpp"
#include "utils.hpp"

class TextObject : public GameObject
{
protected:
	sf::Font& font;
	sf::Text text;
	sf::Color textColor;
	std::string textStr;
	unsigned int characterSize;

public:
	TextObject( std::string identifier, std::string textStr,
		const sf::Vector2f& position = sf::Vector2f( 0.f, 0.f ), const sf::Vector2f& scale = sf::Vector2f( 1.f, 1.f ),
		GameObject* const parent = nullptr,
		sf::Font& font = Utils::getDefaultFont(), sf::Color color = sf::Color::Yellow, unsigned int characterSize = 30 );
	TextObject( const TextObject& other );

	virtual ~TextObject();

	sf::Font& getFont() const;
	sf::Text getText() const;
	sf::Color getTextColor() const;
	std::string getTextStr() const;
	unsigned int getCharacterSize() const;

	void render( sf::RenderWindow& window ) override;
};