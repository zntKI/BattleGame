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
	for ( auto obj : gameObjects ) {
		delete obj;
		Utils::logMessage( "Deleted!" );
	}
}

void GameScene::setupScene( const std::string& sceneConfigFilePath )
{
	// Read that from file and cast it to json
	std::ifstream file( sceneConfigFilePath );
	if ( !file.fail() ) {

		nlohmann::json gameObjectsData = nlohmann::json::parse( file )[ "gameScene" ][ "gameObjects" ];

		for ( auto& gameObjectData : gameObjectsData ) {
			this->setupGameObject( gameObjectData );
		}

		file.close();

	}
}

void GameScene::setupGameObject( const nlohmann::json& gameObjectData )
{
	std::string gameObjectType = gameObjectData[ "type" ];

	if ( gameObjectType == "SpriteObject" ) {
		this->setupSpriteObject( gameObjectData );
	}
	else if ( gameObjectType == "Character" ) {
		this->setupCharacter( gameObjectData );
	}
}

void GameScene::setupSpriteObject( const nlohmann::json& bgData )
{
	this->gameObjects.emplace_back( new SpriteObject(

		bgData[ "identifier" ],
		bgData[ "filePath" ][ rand() % bgData[ "filePath" ].size() ],
		sf::Vector2f( bgData[ "position" ][ "x" ],
			bgData[ "position" ][ "y" ] ),
		sf::Vector2f( bgData[ "scale" ][ "x" ],
			bgData[ "scale" ][ "y" ] ),
		sf::Vector2f( bgData[ "originFactor" ][ "x" ],
			bgData[ "originFactor" ][ "y" ] )

	) );
}

void GameScene::setupCharacter( const nlohmann::json& charactersData )
{
	nlohmann::json characterSpriteData = charactersData[ "characterSprite" ];
	nlohmann::json spriteSheetConfigData = characterSpriteData[ "spriteSheetConfig" ]; // All possible sprites

	int randSpriteIndex = rand() % spriteSheetConfigData.size();
	nlohmann::json chosenSpriteSheetData = spriteSheetConfigData[ randSpriteIndex ]; // The chosen one

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
		chosenSpriteSheetData[ "filePath" ],
		chosenSpriteSheetData[ "spriteSheetRows" ],
		chosenSpriteSheetData[ "spriteSheetCols" ],
		sf::Vector2f( characterSpriteData[ "position" ][ "x" ],
			characterSpriteData[ "position" ][ "y" ] ),
		sf::Vector2f( characterSpriteData[ "scale" ][ "x" ],
			characterSpriteData[ "scale" ][ "y" ] ),
		sf::Vector2f( characterSpriteData[ "originFactor" ][ "x" ],
			characterSpriteData[ "originFactor" ][ "y" ] )

	) );

	nlohmann::json characterHealthBarData = charactersData[ "healthBar" ];
	nlohmann::json characterHealthBarFillData = charactersData[ "healthBarFill" ];

	Character* character = dynamic_cast< Character* >( this->gameObjects.back() ); // Get the character that has just been emplaced back

	this->gameObjects.emplace_back( new SpriteObject(

		characterHealthBarData[ "identifier" ],
		characterHealthBarData[ "filePath" ],
		character->getGlobalPosition() - sf::Vector2f( 0.f, character->getSpriteSize().y / 3.f ),
		sf::Vector2f( characterHealthBarData[ "scale" ][ "x" ],
			characterHealthBarData[ "scale" ][ "y" ] ),
		sf::Vector2f( characterHealthBarData[ "originFactor" ][ "x" ],
			characterHealthBarData[ "originFactor" ][ "y" ] )

	) );
	SpriteObject* healthBar = dynamic_cast< SpriteObject* >( this->gameObjects.back() );
	character->setHealthBar( healthBar );

	this->gameObjects.emplace_back( new SpriteObject(

		characterHealthBarFillData[ "identifier" ],
		characterHealthBarFillData[ "filePath" ],
		healthBar->getGlobalPosition()
			- sf::Vector2f( ( healthBar->getSpriteSize().x / 2.f ) * characterHealthBarFillData[ "position" ][ "faceMultiplier" ], 0.f),
		sf::Vector2f( characterHealthBarFillData[ "scale" ][ "x" ],
			characterHealthBarFillData[ "scale" ][ "y" ] ),
		sf::Vector2f( characterHealthBarFillData[ "originFactor" ][ "x" ],
			characterHealthBarFillData[ "originFactor" ][ "y" ] )

	) );
	character->setHealthBarFill( dynamic_cast< SpriteObject* >( this->gameObjects.back() ) );

	if ( charactersData[ "identifier" ] == "player" ) {
		player = character;
	}
	else {
		opponent = character;
	}
}

int GameScene::getRndValueForCharSetup( const std::string& propertyName, const nlohmann::json& charactersData )
{
	int minValue = charactersData[ propertyName ][ "min" ];
	int maxValue = charactersData[ propertyName ][ "max" ];

	return minValue + ( rand() % ( ( maxValue + 1 ) - minValue ) );
}