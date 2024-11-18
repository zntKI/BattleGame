#include "gameScene.hpp"
#include "sceneManager.hpp"

#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <filesystem>

#include "utils.hpp"

GameScene::GameScene( const std::string& identifier, SceneManager& sceneManager,
	const std::string& sceneConfigFilePath, const std::string& highScoresFilePath )
	: Scene( identifier, sceneManager, sceneConfigFilePath, highScoresFilePath ), player( nullptr ), opponent( nullptr ),
	btnAttack( nullptr ), btnRecover( nullptr ), btnContinueGame( nullptr ), btnQuitGame( nullptr ),
	currentFightText( nullptr ), battleCount( 0 ), accumulativeDamage(0), numOfHighScores( 5 ),
	charTurnState( CharacterTurn::None )
{
}

GameScene::~GameScene()
{
}

void GameScene::setupScene( sf::RenderWindow& window )
{
	Scene::setupScene( window );


	// Btn implementation:
	this->btnAttack->setButtonAction( [ this ]()
		{
			if ( this->getCharTurnState() == CharacterTurn::PlayerTurn )
			this->playerAttack();
		} );

	this->btnRecover->setButtonAction( [ this ]()
		{
			if ( this->getCharTurnState() == CharacterTurn::PlayerTurn )
			this->playerRecover();
		} );

	this->btnContinueGame->setButtonAction( [ this ]()
		{
			this->startNewBattle();
		} );

	// Reset vars:
	battleCount = 0;
	accumulativeDamage = 0;


	// Sets up battle
	this->setupBattle();
}

void GameScene::reInitScene()
{
	// Only if necessary - look at gameMenu.cpp
}

void GameScene::setupObject( const GameObject* parent, const nlohmann::json& objectData )
{
	std::string gameObjectType = objectData[ "type" ];

	GameObject* objToCreate = nullptr;

	if ( gameObjectType == "SpriteObject" )
	{
		objToCreate = this->setupSpriteObject( parent, objectData );
	}
	else if ( gameObjectType == "Player" )
	{
		objToCreate = this->setupPlayer( parent, objectData );
	}
	else if ( gameObjectType == "Opponent" )
	{
		objToCreate = this->setupOpponent( parent, objectData );
	}
	else if ( gameObjectType == "GameObject" )
	{
		objToCreate = this->setupGameObject( parent, objectData );
	}
	else if ( gameObjectType == "Button" )
	{
		objToCreate = this->setupButton( parent, objectData );

		if ( objToCreate->getIdentifier() == "btnAttack" )
		{
			this->btnAttack = dynamic_cast< Button* >( objToCreate );
		}
		else if ( objToCreate->getIdentifier() == "btnRecover" )
		{
			this->btnRecover = dynamic_cast< Button* >( objToCreate );
		}
		else if ( objToCreate->getIdentifier() == "btnContinueGame" )
		{
			this->btnContinueGame = dynamic_cast< Button* >( objToCreate );
		}
		else if ( objToCreate->getIdentifier() == "btnQuitGame" )
		{
			this->btnQuitGame = dynamic_cast< Button* >( objToCreate );
		}
	}
	else if ( gameObjectType == "TextObject" )
	{
		objToCreate = this->setupTextObject( parent, objectData );
	}
	else if ( gameObjectType == "FightText" )
	{
		objToCreate = this->setupFightText( parent, objectData );

		this->currentFightText = dynamic_cast< FightText* >( objToCreate );
	}
	else if ( gameObjectType == "FPSCounter" )
	{
		objToCreate = this->setupFPSCounter( parent, objectData );
	}
	else
	{
		Utils::logError( "Invalid type of object from file - check in json file!" );
		return;
	}

	for ( auto& childObjectData : objectData[ "children" ] )
	{
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

FightText* GameScene::setupFightText( const GameObject* parent, const nlohmann::json& textObjectData )
{
	this->gameObjects.emplace_back( new FightText(

		textObjectData[ "identifier" ],
		parent,
		textObjectData[ "text" ],
		textObjectData[ "numLinesVisible" ],
		sf::Vector2f( textObjectData[ "position" ][ "x" ],
			textObjectData[ "position" ][ "y" ] ),
		sf::Vector2f( textObjectData[ "originFactor" ][ "x" ],
			textObjectData[ "originFactor" ][ "y" ] )

	) );
	FightText* text = dynamic_cast< FightText* >( this->gameObjects.back() );
	text->finishInit();

	return text;
}

void GameScene::playerAttack()
{
	this->player->attack();
}

void GameScene::playerRecover()
{
	this->player->recover();
}

void GameScene::startNewBattle()
{
	// Start new battle with new enemy
	std::ifstream file( this->sceneConfigFilePath );
	if ( !file.fail() )
	{
		nlohmann::json gameObjectsData = nlohmann::json::parse( file )[ this->identifier ][ "gameObjects" ];

		for ( auto& gameObjectData : gameObjectsData )
		{
			if ( gameObjectData[ "type" ] == "Opponent" )
			{
				this->setupObject( nullptr, gameObjectData );
			}
		}

		file.close();
	}

	// Sets up battle
	this->setupBattle();
}

void GameScene::setupBattle()
{
	this->btnAttack->setActive( true );
	this->btnRecover->setActive( true );

	this->btnContinueGame->setActive( false );
	this->btnQuitGame->setButtonAction( [ this ]()
		{
			this->updateHighScores();
			this->sceneManager.popScene();
		} );

	this->battleCount++;

	// Fight log setup
	std::ostringstream oss;
	oss << "Start of Battle " << battleCount << ": ";
	oss << this->player->getName() << "(You) " << "vs " << this->opponent->getName() << "(Enemy)";
	this->currentFightText->updateFightText( oss.str() );


	// Determine fight order
	int playerAgility = this->player->getAgility();
	int opponentAgility = this->opponent->getAgility();
	bool isPlayerFirst = playerAgility > opponentAgility ? true :
		( playerAgility < opponentAgility ? false : rand() % 2 /*if equal, rand decide*/ );

	charTurnState = isPlayerFirst ? CharacterTurn::PlayerTurn : CharacterTurn::OpponentTurn;
	this->updateFightText( charTurnState );
}

void GameScene::finishBattle( const GameObject* const deadChar )
{
	std::ostringstream oss;
	oss << "End of Battle " << battleCount << ": ";

	if ( deadChar == opponent )
	{
		oss << "Winner - " << this->player->getName() << "(You)";
		this->currentFightText->updateFightText( oss.str() );

		this->btnContinueGame->setActive( true );

		accumulativeDamage = this->player->getDamageDealt(); // Increased only after end of fight so that if the player decides to quit mid-game, their score from the previous battle is persisted - without taking into account the result from the current one
	}
	else
	{
		oss << "Winner - " << this->opponent->getName() << "(Enemy)";
		this->currentFightText->updateFightText( oss.str() );
		
		oss.str("");
		oss << "Score: " << this->player->getDamageDealt();
		this->currentFightText->updateFightText( oss.str() );
	}

	this->btnAttack->setActive( false );
	this->btnRecover->setActive( false );
}

void GameScene::updateHighScores()
{
	// Update high scores - char name + the sum of dealt damage

	// TODO: figure out how to deal with the exe path:
	/*	std::filesystem::path exePath = std::filesystem::current_path();
	std::filesystem::path filePath = exePath / "example.txt";*/

	std::fstream highScoreFile( this->highScoresFilePath, std::ios::in | std::ios::app );
	if ( !highScoreFile.fail() )
	{
		std::vector<HighScore> presentHighScores;

		// Read all the highscores:
		std::string line;
		while ( std::getline( highScoreFile, line ) )
		{
			size_t index = line.find( ' ' );
			if ( index == std::string::npos )
			{
				Utils::logError( "Invalid data: Highscore is not in the right format!" );
				highScoreFile.close();
				return;
			}

			presentHighScores.push_back( { line.substr( 0, index ), std::stoi( line.substr( index + 1 ) ) } );
		}

		HighScore highScoreToAdd = { this->player->getName(), this->accumulativeDamage };

		if ( presentHighScores.empty() ) // If there are not yet any highscores aka file just created
		{
			// Add the current highscore
			highScoreFile.close();
			highScoreFile.open( this->highScoresFilePath, std::fstream::out | std::fstream::app );

			highScoreFile << highScoreToAdd.name << " " << std::to_string( highScoreToAdd.score ) << "\n";
		}
		else
		{
			int indexToInsertAt = -1;

			for ( int i = presentHighScores.size() - 1; i >= 0; i-- )
			{
				HighScore currHighScore = presentHighScores[ i ];

				if ( highScoreToAdd.score < currHighScore.score )
				{
					indexToInsertAt = i + 1;
					break;
				}
			}

			if ( indexToInsertAt == -1 ) // If it wasn't set, it means the the given highscore is the highest so far and should be inserted on top
			{
				indexToInsertAt = 0;
			}

			presentHighScores.insert( presentHighScores.begin() + indexToInsertAt, highScoreToAdd );

			// Close and reopen to trunc all data so that it can be writen again later
			highScoreFile.close();
			highScoreFile.open( this->highScoresFilePath, std::fstream::out | std::fstream::trunc );

			unsigned int amountOfHighscores = presentHighScores.size() < this->numOfHighScores ? presentHighScores.size() : this->numOfHighScores;
			for ( unsigned int i = 0; i < amountOfHighscores; i++ )
			{
				highScoreFile << presentHighScores[ i ].name << " " << presentHighScores[ i ].score << "\n";
			}
		}

		highScoreFile.close();
	}
}

void GameScene::addSessionToContinue()
{
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

void GameScene::updateFightText( CharacterTurn currentCharTurn )
{
	std::ostringstream oss;
	oss << ( currentCharTurn == CharacterTurn::PlayerTurn
		? this->player->getName()
		: this->opponent->getName() )
		<< ( currentCharTurn == CharacterTurn::PlayerTurn
			? "(You): "
			: "(Enemy): " );

	this->currentFightText->updateFightText( oss.str() );
}

void GameScene::appendToLastTextLog( const std::string& textToAdd )
{
	this->currentFightText->appendToLastTextLog( textToAdd );
}

const CharacterTurn& GameScene::getCharTurnState() const
{
	return this->charTurnState;
}

Character& GameScene::getOtherCharacter( const GameObject* const character ) const
{
	return character == this->player ? dynamic_cast< Character& >( *( this->opponent ) ) : dynamic_cast< Character& >( *( this->player ) );
}