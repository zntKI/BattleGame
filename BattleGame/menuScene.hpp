#pragma once

#include <nlohmann/json.hpp>

#include "scene.hpp"
#include "button.hpp"

class MenuScene : public Scene
{
private:
	// Title
	GameObject* titleContainer;

	// Buttons
	GameObject* btnContainer;

	Button* btnPlay;
	Button* btnErase;
	Button* btnQuit;

public:
	MenuScene( const std::string& identifier );

	~MenuScene();

private:
	void setupObject( const GameObject* parent, const nlohmann::json& gameObjectData ) override;

};