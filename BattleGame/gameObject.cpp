#include <iostream>

#include "gameObject.hpp"

GameObject::GameObject( const std::string identifier,
	const sf::Vector2f position, const sf::Vector2f scale,
	GameObject* parent )
	: identifier( identifier ), globalPostion( position ), scale( scale ), parent( parent )
{
}

GameObject::GameObject( const GameObject& other )
	: identifier( other.getIdentifier() )
{
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

void GameObject::resetPosition( sf::Vector2f position )
{
	this->localPosition = position;
	this->globalPostion = this->parent != nullptr ? this->parent->getGlobalPosition() + this->localPosition : this->localPosition;
}

void GameObject::setPostion( sf::Vector2f position )
{
	this->resetPosition( position );

	for ( auto element = this->children.begin(); element != this->children.end(); element++ ) {
		element->second->setPostion( position );
	}
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

void GameObject::addChild( GameObject& child )
{
	// Check if child already has an active parent
	if ( child.parent != nullptr ) {
		child.detachFromParent();
	}

	if ( this->children.find( child.getIdentifier() ) == this->children.end() ) {
		this->children.emplace( child.getIdentifier(), &child );
		child.parent = this;

		// Resets global and local position of object after including it in the hierarchy
		child.resetPosition( child.getGlobalPosition() - child.parent->getGlobalPosition() );
	}
	else {
		std::cout << "Trying to make a game object child of another when it already is!" << std::endl;
	}
}

void GameObject::removeChild( const std::string childIdentifier )
{
	auto search = this->children.find( childIdentifier );
	if ( search == this->children.end() ) {
		std::cout << "Invalid game object identifier: Trying to remove a child that is not present in the parent's children!" << std::endl;
		return;
	}

	GameObject* child = search->second;
	child->parent = nullptr;

	// Resets global and local position of object after taking it out of the hierarchy
	child->resetPosition( child->getGlobalPosition() );

	size_t result = this->children.erase( childIdentifier );
	if ( result == 0 ) {
		std::cout << "Unable to 'erase' (remove) child from collection!" << std::endl;
	}
}

void GameObject::attachToParent( GameObject& parent )
{
	parent.addChild( *this );
}

void GameObject::detachFromParent()
{
	if ( this->parent == nullptr ) {
		std::cout << "Invalid operation: You try to detach a game object from its parent even though it doesn't have one!" << std::endl;
	}
	else {
		this->parent->removeChild( this->getIdentifier() );
	}
}