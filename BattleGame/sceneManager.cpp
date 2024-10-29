#include "sceneManager.hpp"

SceneManager::SceneManager( const std::string& sceneConfigFilePath, sf::RenderWindow& window )
	: window( window ), sceneConfigFilePath( sceneConfigFilePath )
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::handleEvent( const sf::Event& event, sf::RenderWindow& window )
{
	if ( this->scenesStack.size() != 0 ) {
		this->scenesStack.top()->handleEvent( event, window );
	}
}

void SceneManager::update()
{
	if ( this->scenesStack.size() != 0 ) {
		this->scenesStack.top()->update();
	}
}

void SceneManager::render( sf::RenderWindow& window ) const
{
	if ( this->scenesStack.size() != 0 ) {
		this->scenesStack.top()->render( window );
	}
}

void SceneManager::addScene( Scene& scene )
{
	this->scenes.emplace( scene.getIdentifier(), &scene );
}

void SceneManager::stackScene( std::string sceneName )
{
	Scene* scene = scenes[ sceneName ];
	this->scenesStack.push( scene );
	scene->setupScene( sceneConfigFilePath, this, this->window );
}

void SceneManager::popScene()
{
	this->scenesStack.pop();
}

void SceneManager::clearScenes()
{
	while ( !this->scenesStack.empty() ) {
		this->popScene();
	}
	scenes.clear();
}