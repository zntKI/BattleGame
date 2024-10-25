#pragma once

#include <string>
#include <SFML/Graphics.hpp>

#include "gameObject.hpp";

class Scene
{
private:
	const std::string identifier;
	std::vector<GameObject*> gameObjects;

public:
	Scene( const std::string& identifier );
	~Scene();

public:
	void addGameObject( GameObject& gameObject );

	void handleEvent( const sf::Event& event, sf::RenderWindow& window );
	void update();
	void render( sf::RenderWindow& window );

	std::string getIdentifier() const;
};