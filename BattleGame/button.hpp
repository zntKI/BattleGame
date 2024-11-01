#pragma once

#include <functional>

#include "animationSpriteObject.hpp"
#include "textObject.hpp"

class Button : public AnimationSpriteObject
{
private:
	std::function<void()> action;

	TextObject* text;

public:
	Button( const std::string& identifier, const GameObject* parent,
		const std::string& spriteFile,
		const int spriteSheetRows, const int spriteSheetCols, const int totalFrames,
		const sf::Vector2f position, const sf::Vector2f scale, const sf::Vector2f originFactor,
		sf::Vector2f colliderSizeFactor );
	Button( const Button& other );

	~Button();

	std::function<void()> getButtonAction() const;

	void update() override;
	void handleEvent( const sf::Event& event, sf::RenderWindow& window ) override;
	void onClick();

	void setButtonAction( const std::function<void()>& action );

	void setText( TextObject* text );
};