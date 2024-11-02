#include "gameScene.hpp"

#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>
#include <sstream>
#include <string>

#include "utils.hpp"

GameScene::GameScene( const std::string& identifier )
	: Scene( identifier ), player( nullptr ), opponent( nullptr ),
	btnAttack( nullptr ), btnRecover( nullptr ), btnQuitGame( nullptr ),
	currentFightText( nullptr ), numLinesVisible( 4 ), battleCount( 1 ),
	charTurnState( CharacterTurn::None )
{
}

GameScene::~GameScene()
{
}

void GameScene::setupScene( const std::string& sceneConfigFilePath, SceneManager* sceneManager, sf::RenderWindow& window )
{
	Scene::setupScene( sceneConfigFilePath, sceneManager, window );


	// Btn implementation:
	this->btnAttack->setButtonAction( [ this ]() {

		if ( this->getCharTurnState() == CharacterTurn::PlayerTurn ) {

			this->playerAttack();

		}

		} );

	this->btnRecover->setButtonAction( [ this ]() {

		if ( this->getCharTurnState() == CharacterTurn::PlayerTurn ) {

			this->playerRecover();

		}

		} );

	this->btnQuitGame->setButtonAction( [ &window ]() {

		window.close();

		} );


	// Fight log setup
	this->currentFightText->setCharacterSize( 20 );
	for ( unsigned int i = 0; i < this->numLinesVisible; i++ ) {
		fightLog.push_back( "" );
	}

	std::ostringstream oss;
	oss << "Start of Battle " << battleCount << ": ";
	oss << this->player->getName() << "(You) " << "vs " << this->opponent->getName() << "(Enemy)";
	this->updateFightText( oss.str() );


	// Determine fight order
	int playerAgility = this->player->getAgility();
	int opponentAgility = this->opponent->getAgility();
	bool isPlayerFirst = playerAgility > opponentAgility ? true :
		( playerAgility < opponentAgility ? false : rand() % 2 /*if equal, rand decide*/ );

	charTurnState = isPlayerFirst ? CharacterTurn::PlayerTurn : CharacterTurn::OpponentTurn;
	this->updateFightText( charTurnState );
}

void GameScene::setupObject( const GameObject* parent, const nlohmann::json& objectData )
{
	std::string gameObjectType = objectData[ "type" ];

	GameObject* objToCreate = nullptr;

	if ( gameObjectType == "SpriteObject" ) {
		objToCreate = this->setupSpriteObject( parent, objectData );
	}
	else if ( gameObjectType == "Player" ) {
		objToCreate = this->setupPlayer( parent, objectData );
	}
	else if ( gameObjectType == "Opponent" ) {
		objToCreate = this->setupOpponent( parent, objectData );
	}
	else if ( gameObjectType == "GameObject" ) {
		objToCreate = this->setupGameObject( parent, objectData );
	}
	else if ( gameObjectType == "Button" ) {
		objToCreate = this->setupButton( parent, objectData );

		if ( objToCreate->getIdentifier() == "btnAttack" ) {
			this->btnAttack = dynamic_cast< Button* >( objToCreate );
		}
		else if ( objToCreate->getIdentifier() == "btnRecover" ) {
			this->btnRecover = dynamic_cast< Button* >( objToCreate );
		}
		else if ( objToCreate->getIdentifier() == "btnQuitGame" ) {
			this->btnQuitGame = dynamic_cast< Button* >( objToCreate );
		}
	}
	else if ( gameObjectType == "TextObject" ) {
		objToCreate = this->setupTextObject( parent, objectData );

		if ( objToCreate->getIdentifier() == "currentFightText" ) {
			this->currentFightText = dynamic_cast< TextObject* >( objToCreate );
		}
	}
	else if ( gameObjectType == "FPSCounter" ) {
		objToCreate = this->setupFPSCounter( parent, objectData );
	}
	else {
		Utils::logError( "Invalid type of object from file - check in json file!" );
		return;
	}

	for ( auto& childObjectData : objectData[ "children" ] ) {
		this->setupObject( objToCreate, childObjectData );
	}
}

Player* GameScene::setupPlayer( const GameObject* parent, const nlohmann::json& charactersData )
{
	nlohmann::json spriteSheetConfigData = charactersData[ "spriteSheetConfig" ]; // All possible sprites

	int randSpriteIndex = rand() % charactersData[ "spriteSheetConfig" ].size();
	nlohmann::json chosenSpriteSheetData = charactersData[ "spriteSheetConfig" ][ randSpriteIndex ]; // The chosen one

	nlohmann::json animData = chosenSpriteSheetData[ "animData" ];

	// Emplace back with heap allocation
	this->gameObjects.emplace_back( new Player(

		// Character specific:
		this,
		charactersData[ "name" ][ rand() % charactersData[ "name" ].size() ],
		this->getRndValueForCharSetup( "health", charactersData ),
		this->getRndValueForCharSetup( "attackAmount", charactersData ),
		this->getRndValueForCharSetup( "defenseAmount", charactersData ),
		this->getRndValueForCharSetup( "agility", charactersData ),
		animData[ "idleAnimData" ][ "startFrame" ],
		animData[ "idleAnimData" ][ "numFrames" ],
		animData[ "idleAnimData" ][ "frameSwitchTimeSec" ],
		animData[ "attackAnimData" ][ "startFrame" ],
		animData[ "attackAnimData" ][ "numFrames" ],
		animData[ "attackAnimData" ][ "frameSwitchTimeSec" ],
		animData[ "hurtAnimData" ][ "startFrame" ],
		animData[ "hurtAnimData" ][ "numFrames" ],
		animData[ "hurtAnimData" ][ "frameSwitchTimeSec" ],
		animData[ "dieAnimData" ][ "startFrame" ],
		animData[ "dieAnimData" ][ "numFrames" ],
		animData[ "dieAnimData" ][ "frameSwitchTimeSec" ],
		animData[ "attackAnimData" ][ "projectileLaunchFrame" ],
		chosenSpriteSheetData[ "projectile" ],
		// Animation sprite specific:
		charactersData[ "identifier" ],
		parent,
		chosenSpriteSheetData[ "filePath" ],
		chosenSpriteSheetData[ "spriteSheetRows" ],
		chosenSpriteSheetData[ "spriteSheetCols" ],
		chosenSpriteSheetData[ "totalFrames" ],
		sf::Vector2f( charactersData[ "position" ][ "x" ],
			charactersData[ "position" ][ "y" ] ),
		sf::Vector2f( charactersData[ "scale" ][ "x" ],
			charactersData[ "scale" ][ "y" ] ),
		sf::Vector2f( charactersData[ "originFactor" ][ "x" ],
			charactersData[ "originFactor" ][ "y" ] ),
		sf::Vector2f( chosenSpriteSheetData[ "colliderSizeFactor" ][ "x" ],
			chosenSpriteSheetData[ "colliderSizeFactor" ][ "y" ] )

	) );

	Player* player = dynamic_cast< Player* >( this->gameObjects.back() ); // Get the character that has just been emplaced back
	player->finishInit();

	SpriteObject* healthBar = dynamic_cast< SpriteObject* >( this->setupSpriteObject( player, charactersData[ "healthBar" ] ) );
	player->setHealthBar( healthBar );

	SpriteObject* healthBarFill = dynamic_cast< SpriteObject* >( this->setupSpriteObject( healthBar, charactersData[ "healthBarFill" ] ) );
	player->setHealthBarFill( healthBarFill );

	this->player = player;

	return player;
}

Opponent* GameScene::setupOpponent( const GameObject* parent, const nlohmann::json& charactersData )
{
	nlohmann::json spriteSheetConfigData = charactersData[ "spriteSheetConfig" ]; // All possible sprites

	int randSpriteIndex = rand() % charactersData[ "spriteSheetConfig" ].size();
	nlohmann::json chosenSpriteSheetData = charactersData[ "spriteSheetConfig" ][ randSpriteIndex ]; // The chosen one

	nlohmann::json animData = chosenSpriteSheetData[ "animData" ];

	// Emplace back with heap allocation
	this->gameObjects.emplace_back( new Opponent(

		// Character specific:
		this,
		charactersData[ "name" ][ rand() % charactersData[ "name" ].size() ],
		this->getRndValueForCharSetup( "health", charactersData ),
		this->getRndValueForCharSetup( "attackAmount", charactersData ),
		this->getRndValueForCharSetup( "defenseAmount", charactersData ),
		this->getRndValueForCharSetup( "agility", charactersData ),
		animData[ "idleAnimData" ][ "startFrame" ],
		animData[ "idleAnimData" ][ "numFrames" ],
		animData[ "idleAnimData" ][ "frameSwitchTimeSec" ],
		animData[ "attackAnimData" ][ "startFrame" ],
		animData[ "attackAnimData" ][ "numFrames" ],
		animData[ "attackAnimData" ][ "frameSwitchTimeSec" ],
		animData[ "hurtAnimData" ][ "startFrame" ],
		animData[ "hurtAnimData" ][ "numFrames" ],
		animData[ "hurtAnimData" ][ "frameSwitchTimeSec" ],
		animData[ "dieAnimData" ][ "startFrame" ],
		animData[ "dieAnimData" ][ "numFrames" ],
		animData[ "dieAnimData" ][ "frameSwitchTimeSec" ],
		animData[ "attackAnimData" ][ "projectileLaunchFrame" ],
		chosenSpriteSheetData[ "projectile" ],
		// Animation sprite specific:
		charactersData[ "identifier" ],
		parent,
		chosenSpriteSheetData[ "filePath" ],
		chosenSpriteSheetData[ "spriteSheetRows" ],
		chosenSpriteSheetData[ "spriteSheetCols" ],
		chosenSpriteSheetData[ "totalFrames" ],
		sf::Vector2f( charactersData[ "position" ][ "x" ],
			charactersData[ "position" ][ "y" ] ),
		sf::Vector2f( charactersData[ "scale" ][ "x" ],
			charactersData[ "scale" ][ "y" ] ),
		sf::Vector2f( charactersData[ "originFactor" ][ "x" ],
			charactersData[ "originFactor" ][ "y" ] ),
		sf::Vector2f( chosenSpriteSheetData[ "colliderSizeFactor" ][ "x" ],
			chosenSpriteSheetData[ "colliderSizeFactor" ][ "y" ] )

	) );

	Opponent* opponent = dynamic_cast< Opponent* >( this->gameObjects.back() ); // Get the character that has just been emplaced back
	opponent->finishInit();

	SpriteObject* healthBar = dynamic_cast< SpriteObject* >( this->setupSpriteObject( opponent, charactersData[ "healthBar" ] ) );
	opponent->setHealthBar( healthBar );

	SpriteObject* healthBarFill = dynamic_cast< SpriteObject* >( this->setupSpriteObject( healthBar, charactersData[ "healthBarFill" ] ) );
	opponent->setHealthBarFill( healthBarFill );

	this->opponent = opponent;

	return opponent;
}

int GameScene::getRndValueForCharSetup( const std::string& propertyName, const nlohmann::json& charactersData )
{
	int minValue = charactersData[ propertyName ][ "min" ];
	int maxValue = charactersData[ propertyName ][ "max" ];

	return minValue + ( rand() % ( ( maxValue + 1 ) - minValue ) );
}

void GameScene::update()
{
	Scene::update();
}

void GameScene::playerAttack()
{
	this->player->attack();
}

void GameScene::playerRecover()
{
	this->player->recover();
}

void GameScene::finishBattle( const GameObject* const deadChar )
{
	if ( deadChar == opponent ) {

		// Start new battle with new enemy

	}
	else {

		// Update high scores
		// Go back to main menu

	}
}

void GameScene::setCharacterTurn( CharacterTurn charTurn )
{
	this->charTurnState = charTurn;
}

void GameScene::swapCharacterTurn( bool isCharToSwapTo, const GameObject* const character )
{
	CharacterTurn turnToChangeTo = isCharToSwapTo ?
		( character == this->player ? CharacterTurn::PlayerTurn : CharacterTurn::OpponentTurn ) :
		( character == this->player ? CharacterTurn::OpponentTurn : CharacterTurn::PlayerTurn );
	this->setCharacterTurn( turnToChangeTo );

	this->updateFightText( turnToChangeTo );
}

void GameScene::updateFightText( const std::string& textToAdd )
{
	this->fightLog.push_back( textToAdd );

	std::string finalText;

	// Goes through the given number of lines and appends them to the visible text log
	for ( auto line = this->fightLog.end() - this->numLinesVisible; line < this->fightLog.end(); line++ ) {

		finalText += *line;
		if ( line < this->fightLog.end() - 1 ) {

			finalText += "\n";

		}

	}

	this->currentFightText->setText( finalText );
}

void GameScene::updateFightText( CharacterTurn currentCharTurn )
{
	std::ostringstream oss;
	oss << ( currentCharTurn == CharacterTurn::PlayerTurn
		? this->player->getName()
		: this->opponent->getName() )
		<< ( currentCharTurn == CharacterTurn::PlayerTurn
			? "(You): "
			: "(Enemy): " );

	this->updateFightText( oss.str() );
}

void GameScene::appendToLastTextLog( const std::string& textToAdd )
{
	std::string& lastTextLog = this->fightLog.back();
	lastTextLog += textToAdd;
}

const CharacterTurn& GameScene::getCharTurnState() const
{
	return this->charTurnState;
}

Character& GameScene::getOtherCharacter( const GameObject* const character ) const
{
	return character == this->player ? dynamic_cast< Character& >( *( this->opponent ) ) : dynamic_cast< Character& >( *( this->player ) );
}