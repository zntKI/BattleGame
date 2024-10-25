#pragma once

#include <functional>

#include "animationSpriteObject.hpp"

class Button : public AnimationSpriteObject
{
private:
	std::function<void()> action;

public:
	Button( const std::string& identifier, const std::string& spriteFile, const int spriteSheetRows, const int spriteSheetCols, const float frameSwitchTimeSec,
		const sf::Vector2f position, const sf::Vector2f scale, const sf::Vector2f originFactor );
	Button( const Button& other );

	~Button();

	std::function<void()> getButtonAction() const;

	void handleEvent( const sf::Event& event, sf::RenderWindow& window ) override;
	void onClick();

	void setButtonAction( const std::function<void()>& action );
};