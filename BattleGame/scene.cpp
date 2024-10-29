#include <fstream>
#include <nlohmann/json.hpp>

#include "scene.hpp"
#include "utils.hpp"
#include "spriteObject.hpp"
#include "button.hpp"

Scene::Scene( const std::string& identifier )
	: identifier( identifier )
{
}

Scene::~Scene()
{
	for ( auto obj : gameObjects ) {
		delete obj;
		Utils::logMessage( "Deleted!" );
	}
}

void Scene::setupScene( const std::string& sceneConfigFilePath )
{
	// Read that from file and cast it to json
	std::ifstream file( sceneConfigFilePath );
	if ( !file.fail() ) {

		nlohmann::json gameObjectsData = nlohmann::json::parse( file )[ this->identifier ][ "gameObjects" ];

		for ( auto& gameObjectData : gameObjectsData ) {
			this->setupObject( nullptr, gameObjectData );
		}

		file.close();

	}
}

GameObject* Scene::setupGameObject( const GameObject* parent, const nlohmann::json& gameObjectData )
{
	this->gameObjects.emplace_back( new GameObject(

		gameObjectData[ "identifier" ],
		parent,
		sf::Vector2f( gameObjectData[ "position" ][ "x" ],
			gameObjectData[ "position" ][ "y" ] )

	) );
	GameObject* obj = this->gameObjects.back();
	obj->finishInit();

	return obj;
}

SpriteObject* Scene::setupSpriteObject( const GameObject* parent, const nlohmann::json& spriteObjectData )
{
	this->gameObjects.emplace_back( new SpriteObject(

		spriteObjectData[ "identifier" ],
		parent,
		spriteObjectData[ "filePath" ],
		sf::Vector2f( spriteObjectData[ "position" ][ "x" ],
			spriteObjectData[ "position" ][ "y" ] ),
		sf::Vector2f( spriteObjectData[ "scale" ][ "x" ],
			spriteObjectData[ "scale" ][ "y" ] ),
		sf::Vector2f( spriteObjectData[ "originFactor" ][ "x" ],
			spriteObjectData[ "originFactor" ][ "y" ] )

	) );
	SpriteObject* sprite = dynamic_cast< SpriteObject* >( this->gameObjects.back() );
	sprite->finishInit();

	return sprite;
}

Button* Scene::setupButton( const GameObject* parent, const nlohmann::json& buttonData )
{
	this->gameObjects.emplace_back( new Button(

		buttonData[ "identifier" ],
		parent,
		buttonData[ "spriteSheetConfig" ][ "filePath" ],
		buttonData[ "spriteSheetConfig" ][ "spriteSheetRows" ],
		buttonData[ "spriteSheetConfig" ][ "spriteSheetCols" ],
		sf::Vector2f( buttonData[ "position" ][ "x" ],
			buttonData[ "position" ][ "y" ] ),
		sf::Vector2f( buttonData[ "scale" ][ "x" ],
			buttonData[ "scale" ][ "y" ] ),
		sf::Vector2f( buttonData[ "originFactor" ][ "x" ],
			buttonData[ "originFactor" ][ "y" ] )

	) );

	Button* btn = dynamic_cast< Button* >( this->gameObjects.back() );
	btn->finishInit();


	nlohmann::json textData = buttonData[ "text" ];
	this->gameObjects.emplace_back( new TextObject(

		textData[ "identifier" ],
		btn,
		textData[ "text" ],
		sf::Vector2f( textData[ "position" ][ "x" ],
			textData[ "position" ][ "y" ] ),
		sf::Vector2f( textData[ "originFactor" ][ "x" ],
			textData[ "originFactor" ][ "y" ] )

	) );

	TextObject* text = dynamic_cast< TextObject* >( this->gameObjects.back() );
	text->finishInit();

	btn->setText( text );

	return btn;
}

TextObject* Scene::setupTextObject( const GameObject* parent, const nlohmann::json& textObjectData )
{
	this->gameObjects.emplace_back( new TextObject(

		textObjectData[ "identifier" ],
		parent,
		textObjectData[ "text" ],
		sf::Vector2f( textObjectData[ "position" ][ "x" ],
			textObjectData[ "position" ][ "y" ] ),
		sf::Vector2f( textObjectData[ "originFactor" ][ "x" ],
			textObjectData[ "originFactor" ][ "y" ] )

	) );
	TextObject* text = dynamic_cast< TextObject* >( this->gameObjects.back() );
	text->finishInit();

	return text;
}

void Scene::addGameObject( GameObject& gameObject )
{
	gameObjects.push_back( &gameObject );
}

void Scene::handleEvent( const sf::Event& event, sf::RenderWindow& window )
{
	for ( unsigned int i = 0; i < gameObjects.size(); i++ ) {
		gameObjects[ i ]->handleEvent( event, window );
	}
}

void Scene::update()
{
	for ( unsigned int i = 0; i < gameObjects.size(); i++ ) {
		gameObjects[ i ]->update();
	}
}

void Scene::render( sf::RenderWindow& window )
{
	for ( unsigned int i = 0; i < gameObjects.size(); i++ ) {
		gameObjects[ i ]->render( window );
	}
}

std::string Scene::getIdentifier() const
{
	return this->identifier;
}
