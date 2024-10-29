#include "gameScene.hpp"

#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>

#include "utils.hpp"

GameScene::GameScene( const std::string& identifier )
	: Scene( identifier ), player( nullptr ), opponent( nullptr )
{
}

GameScene::~GameScene()
{
}

void GameScene::setupObject( const GameObject* parent, const nlohmann::json& objectData )
{
	std::string gameObjectType = objectData[ "type" ];

	GameObject* objToCreate = nullptr;

	if ( gameObjectType == "SpriteObject" ) {
		objToCreate = this->setupSpriteObject( parent, objectData );
	}
	else if ( gameObjectType == "Character" ) {
		
		objToCreate = this->setupCharacter( parent, objectData );

		if ( objToCreate->getIdentifier() == "player" ) {
			player = dynamic_cast< Character* >(objToCreate);
		}
		else {
			opponent = dynamic_cast< Character* >( objToCreate );
		}

	}
	else {
		Utils::logError( "Invalid type of object from file - check in json file!" );
		return;
	}

	for ( auto& childObjectData : objectData[ "children" ] ) {
		this->setupObject( objToCreate, childObjectData );
	}
}

Character* GameScene::setupCharacter( const GameObject* parent, const nlohmann::json& charactersData )
{
	nlohmann::json spriteSheetConfigData = charactersData[ "spriteSheetConfig" ]; // All possible sprites

	int randSpriteIndex = rand() % charactersData[ "spriteSheetConfig" ].size();
	nlohmann::json chosenSpriteSheetData = charactersData[ "spriteSheetConfig" ][ randSpriteIndex ]; // The chosen one

	// Emplace back with heap allocation
	this->gameObjects.emplace_back( new Character(

		// Character specific:
		charactersData[ "name" ][ rand() % charactersData[ "name" ].size() ],
		this->getRndValueForCharSetup( "health", charactersData ),
		this->getRndValueForCharSetup( "attackAmount", charactersData ),
		this->getRndValueForCharSetup( "defenseAmount", charactersData ),
		this->getRndValueForCharSetup( "agility", charactersData ),
		// Animation sprite specific:
		charactersData[ "identifier" ],
		parent,
		chosenSpriteSheetData[ "filePath" ],
		chosenSpriteSheetData[ "spriteSheetRows" ],
		chosenSpriteSheetData[ "spriteSheetCols" ],
		sf::Vector2f( charactersData[ "position" ][ "x" ],
			charactersData[ "position" ][ "y" ] ),
		sf::Vector2f( charactersData[ "scale" ][ "x" ],
			charactersData[ "scale" ][ "y" ] ),
		sf::Vector2f( charactersData[ "originFactor" ][ "x" ],
			charactersData[ "originFactor" ][ "y" ] )

	) );

	Character* character = dynamic_cast< Character* >( this->gameObjects.back() ); // Get the character that has just been emplaced back
	character->finishInit();

	return character;
}

int GameScene::getRndValueForCharSetup( const std::string& propertyName, const nlohmann::json& charactersData )
{
	int minValue = charactersData[ propertyName ][ "min" ];
	int maxValue = charactersData[ propertyName ][ "max" ];

	return minValue + ( rand() % ( ( maxValue + 1 ) - minValue ) );
}