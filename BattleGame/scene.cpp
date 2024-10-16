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
	// Finish initialization
	gameObject.finishInit( gameObjects );

	gameObjects.push_back( &gameObject );
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
