#include <iostream>

#include "gameObject.hpp"
#include "utils.hpp"

GameObject::GameObject( std::string identifier,
	const sf::Vector2f& position, const sf::Vector2f& scale,
	GameObject* const parent )
	: identifier( identifier ), globalPostion( position ), scale( scale ), parent( parent )
{
}

GameObject::GameObject( const GameObject& other )
	: identifier( other.getIdentifier() ),
	globalPostion( other.getGlobalPosition() ), localPosition( other.getLocalPosition() ), scale( other.getScale() ),
	parent( other.getParent() )
{
	// TODO: figure out what to do with children list
}

GameObject::~GameObject()
{
}

void GameObject::update()
{
}

void GameObject::render( sf::RenderWindow& window )
{
}

void GameObject::setScale( sf::Vector2f scale )
{
	this->scale = scale;
}

std::string GameObject::getIdentifier() const
{
	return this->identifier;
}

sf::Vector2f GameObject::getLocalPosition() const
{
	return this->localPosition;
}

sf::Vector2f GameObject::getGlobalPosition() const
{
	return this->globalPostion;
}

sf::Vector2f GameObject::getScale() const
{
	return this->scale;
}

GameObject* GameObject::getParent() const
{
	return this->parent;
}

void GameObject::setParent( GameObject* parent )
{
	this->parent = parent;
}

void GameObject::finishInit( const std::vector<GameObject*>& gameObjects )
{
	if ( gameObjects.size() == 0 || this->parent == nullptr ) {
		return;
	}

	if ( std::find( gameObjects.begin(), gameObjects.end(), this->parent ) == gameObjects.end() ) {
		Utils::logError( "Invalid parent memory address - no such GameObject exists in the Scene in this point of time!" );
	}
	else {
		// A way around the parent-child relation functionality so that it does not cause problems due to the child not being present in the parent's collection
		GameObject* parent = this->parent;
		this->parent = nullptr;

		this->attachToParent( *parent );
	}
}

void GameObject::setPosition( sf::Vector2f position )
{
	this->localPosition += position;
	this->globalPostion = this->parent != nullptr ? this->parent->getGlobalPosition() + this->localPosition : this->localPosition;
}

void GameObject::move( sf::Vector2f position )
{
	this->setPosition( position );

	for ( auto element = this->children.begin(); element != this->children.end(); element++ ) {
		element->second->move( sf::Vector2f( 0.f, 0.f ) /*0-vector because children should only change its global location according to their parent without accumulating their local position*/);
	}
}

void GameObject::addChild( GameObject& child )
{
	// Check if child already has an active parent
	if ( child.getParent() != nullptr ) {
		child.detachFromParent();
	}

	if ( this->children.find( child.getIdentifier() ) == this->children.end() ) {
		this->children.emplace( child.getIdentifier(), &child );
		child.setParent( this );

		// Resets global and local position of object after including it in the hierarchy
		child.setPosition( child.getGlobalPosition() - child.getParent()->getGlobalPosition() );
	}
	else {
		Utils::logError( "Trying to make a game object child of another when it already is!" );
	}
}

void GameObject::removeChild( const std::string childIdentifier )
{
	auto search = this->children.find( childIdentifier );
	if ( search == this->children.end() ) {
		Utils::logError( "Invalid game object identifier: Trying to remove a child that is not present in the parent's children!" );
		return;
	}

	GameObject* child = search->second;
	child->setParent( nullptr );

	// Resets global and local position of object after taking it out of the hierarchy
	child->setPosition( child->getGlobalPosition() );

	size_t result = this->children.erase( childIdentifier );
	if ( result == 0 ) {
		Utils::logError( "Unable to 'erase' (remove) child from collection!" );
	}
}

void GameObject::attachToParent( GameObject& parent )
{
	parent.addChild( *this );
}

void GameObject::detachFromParent()
{
	if ( this->parent == nullptr ) {
		Utils::logError( "Invalid operation: You try to detach a game object from its parent even though it doesn't have one!" );
	}
	else {
		this->parent->removeChild( this->getIdentifier() );
	}
}