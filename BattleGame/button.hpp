#pragma once

#include "textObject.hpp"

#include <functional>

class Button : public GameObject
{
private:
	sf::RectangleShape buttonShape;

	std::function<void()> action;

public:
	Button( const std::string& identifier, const sf::Vector2f& buttonSize = sf::Vector2f( 10.f, 10.f ), sf::Color buttonColor = sf::Color::White,
		const sf::Vector2f& position = sf::Vector2f( 0.f, 0.f ), const sf::Vector2f& scale = sf::Vector2f( 1.f, 1.f ) );
	Button( const Button& other );

	~Button();

	sf::RectangleShape getButtonShape() const;

	void handleEvent( const sf::Event& event, sf::RenderWindow& window ) override;
	void onClick();
	void update() override;
	void render( sf::RenderWindow& window ) override;

	void setButtonAction( const std::function<void()>& action );
};