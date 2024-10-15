#include <iostream>

#include "gameObject.hpp"

GameObject::GameObject( const std::string identifier, GameObject* parent )
	: identifier( identifier ), parent( parent )
{
}

GameObject::GameObject( const GameObject& other )
	: identifier( other.getIdentifier() )
{
}

GameObject::~GameObject()
{
}

std::string GameObject::getIdentifier() const
{
	return this->identifier;
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