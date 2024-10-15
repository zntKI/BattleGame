#pragma once

#include <SFML/Graphics.hpp>

class GameObject
{
protected:
	const std::string identifier;
	GameObject* parent;
	std::map<std::string, GameObject*> children;

public:
	GameObject( const std::string identifier, GameObject* parent = nullptr );
	GameObject( const GameObject& other );

	virtual ~GameObject();

public:
	std::string getIdentifier() const;

	void addChild( GameObject& child );
	void removeChild( const std::string childIdentifier );
	void attachToParent( GameObject& parent );
	void detachFromParent();

	virtual void update() = 0;
	virtual void render( sf::RenderWindow& window ) = 0;
};