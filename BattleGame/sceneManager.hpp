#pragma once

#include <map>
#include <stack>

#include "scene.hpp"

class SceneManager
{
private:
	std::map<std::string, Scene*> scenes;
	std::stack<Scene*> scenesStack;

public:
	SceneManager();
	~SceneManager();

public:
	void render( sf::RenderWindow& window ) const;
	void update();

	void addScene( Scene& scene );
	void stackScene( std::string sceneName );
	void popScene();
};