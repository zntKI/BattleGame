#include <nlohmann/json.hpp>

#include <fstream>
#include <sstream>

#include "menuScene.hpp"
#include "sceneManager.hpp"

MenuScene::MenuScene( const std::string& identifier, SceneManager& sceneManager,
	const std::string& sceneConfigFilePath, const std::string& highScoresFilePath )
	: Scene( identifier, sceneManager, sceneConfigFilePath, highScoresFilePath ),
	btnPlay( nullptr ), btnErase( nullptr ), btnQuit( nullptr ),
	highScoresText( nullptr )
{
}

MenuScene::~MenuScene()
{
}

void MenuScene::setupScene( sf::RenderWindow& window )
{
	Scene::setupScene( window );

	this->btnPlay->setButtonAction( [ this ]() {

		this->sceneManager.stackScene( "gameScene" );

		} );

	this->btnErase->setButtonAction( [ this ]() {

		std::ofstream highScoresFile( this->highScoresFilePath, std::ios::trunc );
	highScoresFile.close();

	this->updateHighScoresText();

		} );

	this->btnQuit->setButtonAction( [ &window ]() {

		window.close();

		} );

	this->updateHighScoresText();
}

void MenuScene::reInitScene()
{
	this->updateHighScoresText();
}

void MenuScene::updateHighScoresText()
{
	std::ifstream highScoresFile( this->highScoresFilePath );
	if ( !highScoresFile.fail() ) {

		std::stringstream buffer;
		buffer << highScoresFile.rdbuf();  // Read the file content into the buffer
		highScoresText->setText( buffer.str() );

		highScoresFile.close();

	}
}

void MenuScene::setupObject( const GameObject* parent, const nlohmann::json& objectData )
{
	std::string gameObjectType = objectData[ "type" ];

	GameObject* objToCreate = nullptr;

	if ( gameObjectType == "GameObject" ) {
		objToCreate = this->setupGameObject( parent, objectData );
	}
	else if ( gameObjectType == "Button" ) {

		objToCreate = this->setupButton( parent, objectData );

		if ( objToCreate->getIdentifier() == "btnPlay" ) {
			this->btnPlay = dynamic_cast< Button* >( objToCreate );
		}
		else if ( objToCreate->getIdentifier() == "btnErase" ) {
			this->btnErase = dynamic_cast< Button* >( objToCreate );
		}
		else if ( objToCreate->getIdentifier() == "btnQuit" ) {
			this->btnQuit = dynamic_cast< Button* >( objToCreate );
		}

	}
	else if ( gameObjectType == "SpriteObject" ) {
		objToCreate = this->setupSpriteObject( parent, objectData );
	}
	else if ( gameObjectType == "TextObject" ) {
		objToCreate = this->setupTextObject( parent, objectData );

		if ( objToCreate->getIdentifier() == "highScoresText" ) {
			this->highScoresText = dynamic_cast< TextObject* >( objToCreate );
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