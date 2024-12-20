#pragma once

#include <map>
#include <stack>

#include "scene.hpp"

class SceneManager
{
private:
	std::map<std::string, Scene*> scenes;
	std::stack<Scene*> scenesStack;

	sf::RenderWindow& window;

public:
	SceneManager( sf::RenderWindow& window );
	~SceneManager();

public:
	void handleEvent( const sf::Event& event, sf::RenderWindow& window );
	void update();
	void render( sf::RenderWindow& window ) const;

	void addScene( Scene& scene );
	void stackScene( std::string sceneName );
	void popScene();
	void clearScenes();
};