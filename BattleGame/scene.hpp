#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

#include "gameObject.hpp"
#include "button.hpp"

class Scene
{
protected:
	const std::string identifier;
	std::vector<GameObject*> gameObjects;

public:
	Scene( const std::string& identifier );
	virtual ~Scene();

public:
	virtual void setupScene( const std::string& sceneConfigFilePath );

	void addGameObject( GameObject& gameObject );

	void handleEvent( const sf::Event& event, sf::RenderWindow& window );
	void update();
	void render( sf::RenderWindow& window );

	std::string getIdentifier() const;

protected:
	virtual void setupObject( const GameObject* parent, const nlohmann::json& objectData ) = 0;

	virtual GameObject* setupGameObject( const GameObject* parent, const nlohmann::json& gameObjectData );
	virtual SpriteObject* setupSpriteObject( const GameObject* parent, const nlohmann::json& spriteObjectData );
	virtual Button* setupButton( const GameObject* parent, const nlohmann::json& buttonData );
	virtual TextObject* setupTextObject( const GameObject* parent, const nlohmann::json& textObjectData );
};