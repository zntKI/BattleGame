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
	int numLinesVisible;
	std::vector<std::string> fightLog;
	int battleCount;

public:
	GameScene( const std::string& identifier );

	~GameScene();

	/// <summary>
	/// override to finish setting up GameScene specific stuff
	/// </summary>
	void setupScene( const std::string& sceneConfigFilePath,
		SceneManager* sceneManager, sf::RenderWindow& window ) override;

	const CharacterTurn& getCharTurnState() const;
	/// <summary>
	/// gets one of the characters - player or opponent, and returns the other <para/>
	/// used for projectile init
	/// </summary>
	Character& getOtherCharacter( const GameObject* const character ) const;

	void update() override;

	void updateFightText( const std::string& textToAdd );
	void updateFightText( CharacterTurn currentCharTurn );

	void appendToLastTextLog( const std::string& textToAdd );

	void playerAttack();
	void playerRecover();

	void finishBattle( const GameObject* const deadChar );

	void setCharacterTurn( CharacterTurn charTurn );
	/// <summary>
	/// swaps state between the two characters
	/// </summary>
	/// <param name="isCharToSwapTo"> -> true - swap to the state corresponding to the 'character' parameter; false - the opposite</param>
	/// <param name="character"> -> the given character</param>
	void swapCharacterTurn( bool isCharToSwapTo, const GameObject* const character );

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