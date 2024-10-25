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
	/// <param name="originFactor"> -> From 0 to 1 factor which will be then multiplied to the bounds of the text</param>
	TextObject( const std::string& identifier, const std::string& textStr,
		const sf::Vector2f position = sf::Vector2f( 0.f, 0.f ), const sf::Vector2f originFactor = sf::Vector2f( 0.f, 0.f ),
		sf::Font& font = Utils::getDefaultFont(), sf::Color color = sf::Color::Yellow, unsigned int characterSize = 30 );
	TextObject( const TextObject& other );

	virtual ~TextObject();

	sf::Font& getFont() const;
	sf::Text getText() const;
	sf::Color getTextColor() const;
	std::string getTextStr() const;
	unsigned int getCharacterSize() const;

	void update() override;
	void render( sf::RenderWindow& window ) override;
};