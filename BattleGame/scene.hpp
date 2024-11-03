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

	SceneManager& sceneManager;

	const std::string sceneConfigFilePath;
	const std::string highScoresFilePath;

public:
	Scene( const std::string& identifier, SceneManager& sceneManager,
		const std::string& sceneConfigFilePath, const std::string& highScoresFilePath );
	virtual ~Scene();

public:
	/// <summary>
	/// reads config file and begins init of surface objs
	/// to be overriden in child classes for more specific func
	/// </summary>
	virtual void setupScene( sf::RenderWindow& window );
	void clear();
	virtual void reInitScene() = 0;

	void addGameObject( GameObject* gameObject );
	void addGameObject( GameObject& gameObject );

	virtual void handleEvent( const sf::Event& event, sf::RenderWindow& window );
	virtual void update();
	virtual void render( sf::RenderWindow& window );

	std::string getIdentifier() const;

protected:
	virtual void handleLateDestroy();
	virtual void destroyObj( const int objIndex );
	virtual void deleteObj( const GameObject* const obj );

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