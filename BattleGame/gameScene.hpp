#pragma once

#include <nlohmann/json.hpp>

#include "scene.hpp"
#include "spriteObject.hpp"
#include "player.hpp"
#include "opponent.hpp"

enum class CharacterTurn
{
	None,
	PlayerTurn,
	OpponentTurn
};

class GameScene : public Scene
{
private:
	Player* player;
	Opponent* opponent;

	Button* btnAttack;
	Button* btnRecover;
	Button* btnQuitGame;

	CharacterTurn charTurnState;

	TextObject* currentFightText;
	std::vector<std::string> fightLog;

public:
	GameScene( const std::string& identifier );

	~GameScene();

	const CharacterTurn& getCharTurnState() const;

	/// <summary>
	/// override to finish setting up GameScene specific stuff
	/// </summary>
	void setupScene( const std::string& sceneConfigFilePath,
		SceneManager* sceneManager, sf::RenderWindow& window ) override;

	void update() override;

	void setCharacterTurn( CharacterTurn charTurn );

private:
	/// <summary>
	/// distributes objs to their specified method for constructing <para/>
	/// also does the same, recursively, for all their the children down the line
	/// </summary>
	void setupObject( const GameObject* parent, const nlohmann::json& objectData ) override;

	/// <summary>
	/// specified method for constructing the Player character
	/// </summary>
	/// <returns>memory address of the newly created obj to pass down to its children</returns>
	Player* setupPlayer( const GameObject* parent, const nlohmann::json& charactersData );
	/// <summary>
	/// specified method for constructing an Opponent character
	/// </summary>
	/// <returns>memory address of the newly created obj to pass down to its children</returns>
	Opponent* setupOpponent( const GameObject* parent, const nlohmann::json& charactersData );
	/// <summary>
	/// get a random value from the values presented with the given property
	/// </summary>
	/// <returns>rnd value between the min and max properties</returns>
	int getRndValueForCharSetup( const std::string& propertyName, const nlohmann::json& charactersData );

};