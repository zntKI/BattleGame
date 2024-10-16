#pragma once

#include <SFML/Graphics.hpp>

class GameObject
{
protected:
	const std::string identifier;

	sf::Vector2f globalPostion;
	sf::Vector2f localPosition;
	sf::Vector2f scale;

	GameObject* parent;
	std::map<std::string, GameObject*> children;

public:
	GameObject( const std::string identifier,
		const sf::Vector2f position = sf::Vector2f( 0.f, 0.f ), const sf::Vector2f scale = sf::Vector2f( 1.f, 1.f ),
		GameObject* parent = nullptr );
	GameObject( const GameObject& other );

	virtual ~GameObject();

public:
	std::string getIdentifier() const;
	sf::Vector2f getLocalPosition() const;
	sf::Vector2f getGlobalPosition() const;
	sf::Vector2f getScale() const;
	GameObject* getParent() const;
	void setParent( GameObject* parent );

	void addChild( GameObject& child );
	void removeChild( const std::string childIdentifier );
	void attachToParent( GameObject& parent );
	void detachFromParent();

	virtual void update();
	virtual void render( sf::RenderWindow& window );

	virtual void resetPosition( sf::Vector2f position );
	virtual void setPostion( sf::Vector2f position );
	virtual void setScale( sf::Vector2f scale );
};