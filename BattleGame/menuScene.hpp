#pragma once

#include <nlohmann/json.hpp>

#include "scene.hpp"
#include "button.hpp"

class MenuScene : public Scene
{
private:

	Button* btnPlay;
	Button* btnErase;
	Button* btnQuit;

	TextObject* highScoresText;

public:
	MenuScene( const std::string& identifier, SceneManager& sceneManager,
		const std::string& sceneConfigFilePath, const std::string& highScoresFilePath );

	~MenuScene();

	void setupScene( sf::RenderWindow& window ) override;
	void reInitScene() override;

	void updateHighScoresText();

private:
	void setupObject( const GameObject* parent, const nlohmann::json& gameObjectData ) override;
};