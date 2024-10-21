#include "scene.hpp"

Scene::Scene( const std::string identifier )
	: identifier( identifier )
{
}

Scene::~Scene()
{
}

void Scene::addGameObject( GameObject& gameObject )
{
	gameObjects.push_back( &gameObject );
}

void Scene::handleEvent( const sf::Event& event, sf::RenderWindow& window )
{
	for ( unsigned int i = 0; i < gameObjects.size(); i++ ) {
		gameObjects[ i ]->handleEvent( event, window );
	}
}

void Scene::update()
{
	for ( unsigned int i = 0; i < gameObjects.size(); i++ ) {
		gameObjects[ i ]->update();
	}
}

void Scene::render( sf::RenderWindow& window )
{
	for ( unsigned int i = 0; i < gameObjects.size(); i++ ) {
		gameObjects[ i ]->render( window );
	}
}

std::string Scene::getIdentifier() const
{
	return this->identifier;
}
