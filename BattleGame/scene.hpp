#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

#include "gameObject.hpp"
#include "button.hpp"
#include "FPSCounter.hpp"

class SceneManager;

class Scene
{
protected:
	const std::string identifier;
	std::vector<GameObject*> gameObjects;

public:
	Scene( const std::string& identifier );
	virtual ~Scene();

public:
	/// <summary>
	/// reads config file and begins init of surface objs
	/// to be overriden in child classes for more specific func
	/// </summary>
	virtual void setupScene( const std::string& sceneConfigFilePath,
		SceneManager* sceneManager, sf::RenderWindow& window );

	void addGameObject( GameObject* gameObject );
	void addGameObject( GameObject& gameObject );

	virtual void handleEvent( const sf::Event& event, sf::RenderWindow& window );
	virtual void update();
	virtual void render( sf::RenderWindow& window );

	std::string getIdentifier() const;

protected:
	/// <summary>
	/// pure virtual method to be overriden in child classes with its corresponding behaviour
	/// </summary>
	virtual void setupObject( const GameObject* parent, const nlohmann::json& objectData ) = 0;

	virtual GameObject* setupGameObject( const GameObject* parent, const nlohmann::json& gameObjectData );
	virtual SpriteObject* setupSpriteObject( const GameObject* parent, const nlohmann::json& spriteObjectData );
	virtual Button* setupButton( const GameObject* parent, const nlohmann::json& buttonData );
	virtual TextObject* setupTextObject( const GameObject* parent, const nlohmann::json& textObjectData );
	virtual FPSCounter* setupFPSCounter( const GameObject* parent, const nlohmann::json& fpsCounterData );
};