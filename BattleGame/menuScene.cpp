#include <nlohmann/json.hpp>

#include "menuScene.hpp"

MenuScene::MenuScene( const std::string& identifier )
	: Scene( identifier ),
	titleContainer( nullptr ),
	btnContainer( nullptr ),
	btnPlay( nullptr ), btnErase( nullptr ), btnQuit( nullptr )
{
}

MenuScene::~MenuScene()
{
}

void MenuScene::setupObject( const GameObject* parent, const nlohmann::json& objectData )
{
	std::string gameObjectType = objectData[ "type" ];

	GameObject* objToCreate = nullptr;

	if ( gameObjectType == "GameObject" ) {

		objToCreate = this->setupGameObject( parent, objectData );

		if ( objToCreate->getIdentifier() == "titleContainer" ) {
			this->titleContainer = objToCreate;
		}
		else if ( objToCreate->getIdentifier() == "btnContainer" ) {
			this->btnContainer = objToCreate;
		}

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
	}
	else {
		Utils::logError( "Invalid type of object from file - check in json file!" );
		return;
	}

	for ( auto& childObjectData : objectData[ "children" ] ) {
		this->setupObject( objToCreate, childObjectData );
	}
}