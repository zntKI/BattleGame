#pragma once

#include <string>
#include <SFML/Graphics.hpp>

#include "gameObject.hpp"

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
};