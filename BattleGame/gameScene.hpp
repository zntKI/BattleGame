#pragma once

#include <nlohmann/json.hpp>

#include "scene.hpp"
#include "spriteObject.hpp"
#include "character.hpp"

class GameScene : public Scene
{
private:
	Character* player;
	Character* opponent;

	Button* btnAttack;
	Button* btnRecover;
	Button* btnQuitGame;

public:
	GameScene( const std::string& identifier );

	~GameScene();

	void setupScene( const std::string& sceneConfigFilePath,
		SceneManager* sceneManager, sf::RenderWindow& window ) override;

private:
	void setupObject( const GameObject* parent, const nlohmann::json& objectData ) override;

	Character* setupCharacter( const GameObject* parent, const nlohmann::json& charactersData );
	/// <summary>
	/// get a random value from the values presented with the given property
	/// </summary>
	/// <returns>rnd value between the min and max properties</returns>
	int getRndValueForCharSetup( const std::string& propertyName, const nlohmann::json& charactersData );
};