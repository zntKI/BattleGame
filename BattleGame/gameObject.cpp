#include <iostream>

#include "gameObject.hpp"
#include "utils.hpp"

GameObject::GameObject( const std::string& identifier, const GameObject* parent,
	sf::Vector2f position )
	: identifier( identifier ), parent( const_cast< GameObject* >( parent ) ),
	active( true ),
	shouldLateDestroy( false ), shouldDestroy( false )
{
	if ( parent == nullptr ) {
		position = sf::Vector2f( position.x * Utils::getScreenWidth(), position.y * Utils::getScreenHeight() );

		this->globalPosition = position;
		this->localPosition = position;
	}
	else {
		this->localPosition = position;
	}
}

void GameObject::finishInit()
{
	if ( this->parent != nullptr ) {

		if ( this->parent->children.find( this->identifier ) == this->parent->children.end() ) {
			this->parent->children.emplace( this->identifier, this );

			this->globalPosition = this->parent->getGlobalPosition() + this->localPosition;
		}
		else {
			Utils::logError( "Trying to make a game object child of another when it already is!" );
		}

	}
}

GameObject::GameObject( const GameObject& other )
	: identifier( other.getIdentifier() ),
	globalPosition( other.getGlobalPosition() ), localPosition( other.getLocalPosition() ),
	parent( other.getParent() )
{
	// TODO: figure out what to do with children list
}

GameObject::~GameObject()
{
}

void GameObject::handleEvent( const sf::Event& event, sf::RenderWindow& window )
{
}

void GameObject::update()
{
}

void GameObject::render( sf::RenderWindow& window )
{
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
	return this->globalPosition;
}

GameObject* GameObject::getParent() const
{
	return this->parent;
}

void GameObject::setParent( GameObject* parent )
{
	this->parent = parent;
}

void GameObject::move( const sf::Vector2f& position )
{
	this->localPosition += position;
	this->globalPosition = this->parent != nullptr ? this->parent->getGlobalPosition() + this->localPosition : this->localPosition;

	for ( auto element = this->children.begin(); element != this->children.end(); element++ ) {
		element->second->move( sf::Vector2f( 0.f, 0.f ) /*0-vector because children should only change its global location according to their parent without accumulating their local position*/ );
	}
}

void GameObject::addChild( GameObject* child )
{
	// Check if child already has an active parent
	if ( child->getParent() != nullptr ) {
		child->detachFromParent();
	}

	if ( this->children.find( child->getIdentifier() ) == this->children.end() ) {
		this->children.emplace( child->getIdentifier(), child );
		child->setParent( this );

		// Sets local position of object after including it in the hierarchy
		child->setPosition( child->getGlobalPosition() - child->getParent()->getGlobalPosition() );
	}
	else {
		Utils::logError( "Trying to make a game object child of another when it already is!" );
	}
}

void GameObject::addChild( GameObject& child )
{
	this->addChild( &child );
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

	// Sets local position of object after taking it out of the hierarchy
	child->setPosition( child->getGlobalPosition() );

	size_t result = this->children.erase( childIdentifier );
	if ( result == 0 ) {
		Utils::logError( "Unable to 'erase' (remove) child from collection!" );
	}
}

void GameObject::attachToParent( GameObject* parent )
{
	parent->addChild( this );
}

void GameObject::attachToParent( GameObject& parent )
{
	this->attachToParent( &parent );
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

void GameObject::setPosition( sf::Vector2f position )
{
	this->localPosition = position;
}

void GameObject::setActive( bool isActive )
{
	this->active = isActive;
	for ( auto element = this->children.begin(); element != this->children.end(); element++ ) {

		element->second->setActive( isActive );

	}
}

bool GameObject::isActive()
{
	return this->active;
}

void GameObject::lateDestroy()
{
	this->shouldLateDestroy = true;

	if ( parent != nullptr && !parent->isLateDestroy() ) // Detatches only the parent from its parent since only that connection should be broken - other parent and its children will be deleted from memory
		this->detachFromParent();
	for ( auto element = this->children.begin(); element != this->children.end(); element++ ) {

		element->second->lateDestroy();

	}
}

bool GameObject::isLateDestroy() const
{
	return this->shouldLateDestroy;
}

void GameObject::destroy()
{
	this->shouldDestroy = true;

	if ( parent != nullptr && !parent->isDestroy() ) // Detatches only the parent from its parent since only that connection should be broken - other parent and its children will be deleted from memory
		this->detachFromParent();
	for ( auto element = this->children.begin(); element != this->children.end(); element++ ) {

		element->second->destroy();

	}
}

bool GameObject::isDestroy() const
{
	return this->shouldDestroy;
}