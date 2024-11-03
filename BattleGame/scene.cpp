#include <fstream>
#include <nlohmann/json.hpp>

#include "scene.hpp"
#include "utils.hpp"
#include "spriteObject.hpp"
#include "button.hpp"

Scene::Scene( const std::string& identifier, SceneManager& sceneManager,
	const std::string& sceneConfigFilePath, const std::string& highScoresFilePath )
	: identifier( identifier ), sceneManager( sceneManager ),
	sceneConfigFilePath( sceneConfigFilePath ), highScoresFilePath( highScoresFilePath )
{
}

Scene::~Scene()
{
	this->clear();
}

void Scene::setupScene( sf::RenderWindow& window )
{
	// Read that from file and cast it to json
	std::ifstream file( this->sceneConfigFilePath );
	if ( !file.fail() ) {

		nlohmann::json gameObjectsData = nlohmann::json::parse( file )[ this->identifier ][ "gameObjects" ];

		for ( auto& gameObjectData : gameObjectsData ) {
			this->setupObject( nullptr, gameObjectData );
		}

		file.close();

	}
}

void Scene::clear()
{
	for ( auto obj : gameObjects ) {
		this->deleteObj( obj );
	}
	this->gameObjects.clear();
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
			spriteObjectData[ "originFactor" ][ "y" ] ),
		sf::Vector2f( spriteObjectData[ "colliderSizeFactor" ][ "x" ],
			spriteObjectData[ "colliderSizeFactor" ][ "y" ] )

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
		buttonData[ "spriteSheetConfig" ][ "totalFrames" ],
		sf::Vector2f( buttonData[ "position" ][ "x" ],
			buttonData[ "position" ][ "y" ] ),
		sf::Vector2f( buttonData[ "scale" ][ "x" ],
			buttonData[ "scale" ][ "y" ] ),
		sf::Vector2f( buttonData[ "originFactor" ][ "x" ],
			buttonData[ "originFactor" ][ "y" ] ),
		sf::Vector2f( buttonData[ "colliderSizeFactor" ][ "x" ],
			buttonData[ "colliderSizeFactor" ][ "y" ] )

	) );

	Button* btn = dynamic_cast< Button* >( this->gameObjects.back() );
	btn->finishInit();

	TextObject* text = dynamic_cast< TextObject* >( this->setupTextObject( btn, buttonData[ "text" ] ) );
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

FPSCounter* Scene::setupFPSCounter( const GameObject* parent, const nlohmann::json& fpsCounterData )
{
	this->gameObjects.emplace_back( new FPSCounter(

		fpsCounterData[ "identifier" ],
		parent,
		fpsCounterData[ "text" ],
		sf::Vector2f( fpsCounterData[ "position" ][ "x" ],
			fpsCounterData[ "position" ][ "y" ] ),
		sf::Vector2f( fpsCounterData[ "originFactor" ][ "x" ],
			fpsCounterData[ "originFactor" ][ "y" ] )

	) );
	FPSCounter* fpsCounter = dynamic_cast< FPSCounter* >( this->gameObjects.back() );
	fpsCounter->finishInit();

	return fpsCounter;
}

void Scene::addGameObject( GameObject* gameObject )
{
	gameObjects.push_back( gameObject );
}

void Scene::addGameObject( GameObject& gameObject )
{
	gameObjects.push_back( &gameObject );
}

void Scene::handleEvent( const sf::Event& event, sf::RenderWindow& window )
{
	for ( unsigned int i = 0; i < gameObjects.size(); i++ ) {

		if ( gameObjects[ i ]->isActive() ) {

			gameObjects[ i ]->handleEvent( event, window );

		}
	}
}

void Scene::update()
{
	for ( unsigned int i = 0; i < gameObjects.size(); i++ ) {

		if ( gameObjects[ i ]->isActive() ) {

			gameObjects[ i ]->update();
			if ( gameObjects[ i ]->isDestroy() ) {

				destroyObj( i ); // instant Destroy

			}

		}

	}
	this->handleLateDestroy();
}

void Scene::handleLateDestroy()
{
	for ( unsigned int i = 0; i < gameObjects.size(); i++ ) {
		if ( gameObjects[ i ]->isLateDestroy() ) {

			destroyObj( i ); // late Destroy

		}
	}
}

void Scene::destroyObj( const int objIndex )
{
	deleteObj( gameObjects[ objIndex ] );
	gameObjects.erase( gameObjects.begin() + ( objIndex ) );
}

void Scene::deleteObj( const GameObject* const obj )
{
	delete obj;
	Utils::logMessage( "Deleted!" );
}

void Scene::render( sf::RenderWindow& window )
{
	for ( unsigned int i = 0; i < gameObjects.size(); i++ ) {

		if ( gameObjects[ i ]->isActive() ) {

			gameObjects[ i ]->render( window );

		}

	}
}

std::string Scene::getIdentifier() const
{
	return this->identifier;
}
