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

public:
	GameScene( const std::string& identifier );

	~GameScene();

	void setupScene( const std::string& sceneConfigFilePath ) override;

private:
	void setupGameObject( const nlohmann::json& gameObjectData );

	void setupSpriteObject( const nlohmann::json& charactersData );
	void setupCharacter( const nlohmann::json& charactersData );
	/// <summary>
	/// get a random value from the values presented with the given property
	/// </summary>
	/// <returns>rnd value between the min and max properties</returns>
	int getRndValueForCharSetup( const std::string& propertyName, const nlohmann::json& charactersData );
};