#pragma once

#include <SFML/Graphics.hpp>

#include "gameObject.hpp"
#include "utils.hpp"

class TextObject : public GameObject
{
private:
	sf::Font& font;
	sf::Text text;
	std::string textStr;

public:
	TextObject( const std::string identifier, std::string& textStr,
		const sf::Vector2f position = sf::Vector2f( 0.f, 0.f ), const sf::Vector2f scale = sf::Vector2f( 1.f, 1.f ),
		GameObject* parent = nullptr,
		sf::Font& font = Utils::getDefaultFont() );
	TextObject( const TextObject& other );

	virtual ~TextObject();

	sf::Font& getFont() const;
	sf::Text getText() const;
	std::string getTextStr() const;

	void render( sf::RenderWindow& window ) override;
};